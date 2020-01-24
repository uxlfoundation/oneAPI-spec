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

def shell(c):
    print(c)
    subprocess.check_output(c, shell=True)

def rm(dir):
    print('Removing:', dir)
    shutil.rmtree(dir, ignore_errors=True)
    
def sphinx(target):
    shell('%s -M %s %s %s %s' % (sphinx_build, target, source_dir, build_dir, sphinx_opts))
    
def clean():
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
    
def prep():
    doxygen()
    
def build(target):
    prep()
    sphinx(target)

def main():
    parser = argparse.ArgumentParser(description='Build a document.')
    parser.add_argument('action',choices=['clean',
                                          'prep',
                                          'html',
                                          'latexpdf'])
    args = parser.parse_args()

    if args.action == 'clean':
        clean()
    elif args.action == 'prep':
        prep()
    else:
        build(args.action)

main()
