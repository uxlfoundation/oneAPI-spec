import argparse
import glob
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

def shell(c):
    print(c)
    if dry_run:
        return
    subprocess.check_output(c, shell=True)

def rm(dir):
    print('Removing:', dir)
    if dry_run:
        return
    shutil.rmtree(dir, ignore_errors=True)
    
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
