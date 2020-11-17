# Copyright (c) 2020, Intel Corporation
# SPDX-FileCopyrightText: 2019-2020 Intel Corporation
#
# SPDX-License-Identifier: MIT

import argparse
import glob
import os
import os.path
import shutil
import subprocess
from distutils.dir_util import copy_tree as copy_tree_update
from functools import wraps
from os.path import join

sphinx_build = 'sphinx-build'
source_dir = 'source'
build_dir = 'build'
doxygen_dir = 'doxygen'
doxygen_xml = join(doxygen_dir, 'xml', 'index.xml')

indent = 0


def action(func):
    @wraps(func)
    def wrapped(*args, **kwargs):
        global indent
        log(
            '%s: %s'
            % (
                args[1] if len(args) > 1 and args[1] else wrapped.__name__,
                args[0],
            )
        )
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
    print(indent * ' ' + ' '.join(map(str, args)), flush=True, **kwargs)


def shell(c):
    log(c)
    if cl_args.dry_run:
        return
    subprocess.check_call(c, shell=True)


def rm(dir):
    log('rm -rf', dir)
    if cl_args.dry_run:
        return
    shutil.rmtree(dir, ignore_errors=True)


def copytree(src, dst, dirs_exist_ok=False):
    log('cp -r', src, dst)
    if cl_args.dry_run:
        return
    # dirs_exist_ok needs python 3.8 or later, use copy_tree_update
    # for now
    if dirs_exist_ok:
        copy_tree_update(src, dst)
    else:
        shutil.copytree(src, dst)


def copy(src, dst):
    log('cp', src, dst)
    if cl_args.dry_run:
        return
    shutil.copy(src, dst)


def makedirs(path):
    log('mkdir -p', path)
    if cl_args.dry_run:
        return
    os.makedirs(path)


def sphinx(root, target):
    if not cl_args.verbose:
        os.environ['LATEXMKOPTS'] = '--silent'
        os.environ['LATEXOPTS'] = '-interaction=nonstopmode -halt-on-error'
    sphinx_args = '-N -j auto'
    if not cl_args.verbose:
        sphinx_args += ' -q'
    if cl_args.a:
        sphinx_args += ' -a'
    if cl_args.n:
        sphinx_args += ' -n'
    if cl_args.W:
        sphinx_args += ' -W'
    shell(
        '%s -M %s %s %s %s'
        % (
            sphinx_build,
            target,
            join(root, source_dir),
            join(root, build_dir),
            sphinx_args,
        )
    )


def get_env(var):
    return os.environ[var] if var in os.environ else ''


def root_only(root):
    if root != '.':
        exit('Error: Only works from root')


@action
def dockerbuild(root, target=None):
    root_only(root)
    copy('requirements.txt', 'docker')
    copy('ubuntu-packages.txt', 'docker')
    copy('scripts/install.sh', 'docker')
    shell(
        'docker build'
        ' --build-arg http_proxy=%s'
        ' --build-arg https_proxy=%s'
        ' --build-arg no_proxy=%s'
        ' --tag rscohn2/oneapi-spec docker'
        % (get_env('http_proxy'), get_env('https_proxy'), get_env('no_proxy'))
    )


@action
def dockerpush(root, target=None):
    shell('docker push rscohn2/oneapi-spec')


@action
def dockerrun(root, target=None):
    root_only(root)
    shell(
        'docker run --rm -it'
        ' -e http_proxy=%s'
        ' -e https_proxy=%s'
        ' -e no_proxy=%s'
        ' --user %s:%s'
        ' --volume=%s:/build'
        ' --workdir=/build'
        ' rscohn2/oneapi-spec'
        % (
            get_env('http_proxy'),
            get_env('https_proxy'),
            get_env('no_proxy'),
            os.getuid(),
            os.getgid(),
            os.getcwd(),
        )
    )


@action
def clean(root, target=None):
    apply_dirs(root, 'clean')
    sphinx(root, 'clean')


def command(root, target):
    commands[target](root, target)


def apply_dirs(root, target):
    elements = join(root, 'source', 'elements')
    if os.path.exists(elements):
        for dir in dirs:
            command(join(elements, dir), target)


def up_to_date(target, deps):
    if not os.path.exists(target):
        return False
    for dep in deps:
        if os.path.getmtime(target) < os.path.getmtime(dep):
            return False
    return True


def doxygen_files(root):
    return [join(root, 'Doxyfile')] + glob.glob(
        join(root, 'include', '**'), recursive=True
    )


def doxygen(root, target=None):
    with cd(root):
        doxyfile = 'Doxyfile'
        if not os.path.exists(doxyfile) or up_to_date(
            join(root, doxygen_xml), doxygen_files(root)
        ):
            return
        shell('doxygen %s' % doxyfile)


@action
def prep(root='.', target=None):
    apply_dirs(root, 'prep')
    doxygen(root)


@action
def build(root, target):
    prep(root)
    sphinx(root, target)


def remove_elements(l, elements):
    for e in elements:
        if e in l:
            l.remove(e)
    return l


@action
def sort_words(root, target=None):
    with open(join('source', 'spelling_wordlist.txt')) as fin:
        lines = fin.readlines()
    with open(join('source', 'spelling_wordlist.txt'), 'w') as fout:
        for l in sorted(list(set(lines))):
            fout.write(l)


commands = {
    'clean': clean,
    'dockerbuild': dockerbuild,
    'dockerpush': dockerpush,
    'dockerrun': dockerrun,
    'html': build,
    'latexpdf': build,
    'spelling': build,
    'singlehtml': build,
    'prep': prep,
    'sort-words': sort_words,
}

dirs = [
    'oneCCL',
    'oneDAL',
    'oneMKL',
    'oneTBB',
    'oneVPL',
    'dpcpp',
    'l0',
    'oneDPL',
    'oneDNN',
]


def main():
    global cl_args
    parser = argparse.ArgumentParser(description='Build oneapi spec.')
    parser.add_argument(
        'action', choices=commands.keys(), default='html', nargs='?'
    )
    parser.add_argument('root', nargs='?', default='.')
    parser.add_argument('--branch')
    parser.add_argument('--verbose', action='store_true')
    parser.add_argument('--dry-run', action='store_true')
    parser.add_argument('-W', action='store_true')
    parser.add_argument(
        '-a', action='store_true', help='sphinx -a (build all files)'
    )
    parser.add_argument(
        '-n', action='store_true', help='sphinx -n (nitpicky mode)'
    )
    cl_args = parser.parse_args()

    commands[cl_args.action](cl_args.root, cl_args.action)


main()
