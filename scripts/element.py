import argparse
from functools import wraps
import glob
import os
from os.path import exists
from os.path import getmtime
from os.path import join
import shutil
import subprocess

sphinx_opts    = ''
sphinx_build   = 'sphinx-build'
source_dir     = 'source'
build_dir      = 'build'
doxygen_dir    = 'doxygen'
doxygen_xml    = join(doxygen_dir,'xml','index.xml')

dry_run = False

indent = 0

def action(func):
    @wraps(func)
    def wrapped(*args, **kwargs):
        global indent
        log(args[0])
        indent += 2
        x = func(*args, **kwargs)
        indent -= 2
        return x
    return wrapped

class cd:
    """Context manager for changing the current working directory"""
    def __init__(self, newPath):
        self.newPath = os.path.expanduser(newPath)

    def __enter__(self):
        self.savedPath = os.getcwd()
        log('cd ' + self.newPath)
        os.chdir(self.newPath)

    def __exit__(self, etype, value, traceback):
        os.chdir(self.savedPath)

def log(*args, **kwargs):
    print(indent * ' ' + ' '.join(map(str,args)), **kwargs)
    
def shell(c):
    log(c)
    if dry_run:
        return
    subprocess.check_output(c, shell=True)

def rm(dir):
    log('rm -rf', dir)
    if dry_run:
        return
    shutil.rmtree(dir, ignore_errors=True)
    
def copytree(src, dst):
    log('cp -r', src, dst)
    if dry_run:
        return
    shutil.copytree(src, dst)
    
def copy(src, dst):
    log('cp', src, dst)
    if dry_run:
        return
    shutil.copy(src, dst)
    
def makedirs(path):
    log('mkdir -p', path)
    if dry_run:
        return
    os.makedirs(path)
    
def sphinx(target):
    shell('%s -M %s %s %s %s' % (sphinx_build, target, source_dir, build_dir, sphinx_opts))
    
def clean(target):
    rm(doxygen_dir)
    sphinx('clean')

def up_to_date(target, deps):
    if not exists(target):
        return False
    for dep in deps:
        if getmtime(target) < getmtime(dep):
            return False
    return True
            
def doxygen_files():
    return ['Doxyfile'] + glob.glob('include/**', recursive=True)

def doxygen():
    if (not exists('Doxyfile') or
        up_to_date(doxygen_xml, doxygen_files())):
        return
    shell('doxygen Doxyfile')
    
@action
def prep(target):
    doxygen()
    
def build(target):
    prep(target)
    sphinx(target)

commands = {'clean': clean,
            'html': build,
            'latexpdf': build,
            'prep': prep}

def command(target):
    commands[target](target)

def main():
    parser = argparse.ArgumentParser(description='Build a document.')
    parser.add_argument('action',choices=commands.keys())
    args = parser.parse_args()

    command(args.action)

if __name__ == "__main__":
    main()
