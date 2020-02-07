import sys
if sys.version_info[0] < 3:
    exit('Python 3 is required')
    
import argparse
from functools import wraps
import glob
import os
import os.path
from os.path import join
import platform
import shutil
from string import Template
import stat
import string
import subprocess
import tarfile
import venv

sys.path.insert(0, os.path.abspath(join('source','conf')))
import common_conf

args = None

        
sphinx_opts    = '-q'
sphinx_build   = 'sphinx-build'
source_dir     = 'source'
build_dir      = 'build'
doxygen_dir    = 'doxygen'
doxygen_xml    = join(doxygen_dir,'xml','index.xml')

indent = 0

def action(func):
    @wraps(func)
    def wrapped(*args, **kwargs):
        global indent
        log('%s: %s' % (args[1] if len(args) > 1 and args[1] else wrapped.__name__, args[0]))
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
    if args.dry_run:
        return
    subprocess.check_call(c, shell=True)

def rm(dir):
    log('rm -rf', dir)
    if args.dry_run:
        return
    shutil.rmtree(dir, ignore_errors=True)
    
def copytree(src, dst):
    log('cp -r', src, dst)
    if args.dry_run:
        return
    shutil.copytree(src, dst)
    
def copy(src, dst):
    log('cp', src, dst)
    if args.dry_run:
        return
    shutil.copy(src, dst)
    
def makedirs(path):
    log('mkdir -p', path)
    if args.dry_run:
        return
    os.makedirs(path)

def sphinx(root, target):
    shell('%s -M %s %s %s %s' % (sphinx_build,
                                 target,
                                 join(root,source_dir),
                                 join(root,build_dir),
                                 sphinx_opts))

def get_env(var):
    return os.environ[var] if var in os.environ else ''
    
def root_only(root):
    if root != '.':
        exit('Error: Only works from root')

@action
def dockerbuild(root, target=None):
    root_only(root)
    copy('requirements.txt', 'docker')
    copy('scripts/install.sh', 'docker')
    shell('docker build'
          ' --build-arg http_proxy=%s'
          ' --build-arg https_proxy=%s'
          ' --build-arg no_proxy=%s'
          ' --tag rscohn2/oneapi-spec docker'
          % (get_env('http_proxy'), get_env('https_proxy'), get_env('no_proxy')))

@action
def dockerpush(root, target=None):
    shell('docker push rscohn2/oneapi-spec')

@action
def dockerrun(root, target=None):
    root_only(root)
    shell('docker run --rm -it'
          ' --user %s:%s'
          ' --volume=%s:/build'
          ' --workdir=/build'
          ' rscohn2/oneapi-spec'
          % (os.getuid(), os.getgid(), os.getcwd()))

@action
def clean(root, target=None):
    apply_dirs(root, 'clean')
    sphinx(root, 'clean')

def command(root, target):
    commands[target](root, target)

def apply_dirs(root, target):
    elements = join(root,'source','elements')
    if os.path.exists(elements):
        for dir in dirs:
            command(join(elements,dir), target)

def up_to_date(target, deps):
    if not os.path.exists(target):
        return False
    for dep in deps:
        if os.path.getmtime(target) < os.path.getmtime(dep):
            return False
    return True

def doxygen_files(root):
    return [join(root,'Doxyfile')] + glob.glob(join(root,'include','**'), recursive=True)

def doxygen(root, target=None):
    with cd(root):
        doxyfile = 'Doxyfile'
        if (not os.path.exists(doxyfile) or
            up_to_date(join(root, doxygen_xml), doxygen_files(root))):
            return
        shell('doxygen %s' % doxyfile)
    
@action
def prep(root, target=None):
    apply_dirs(root, 'prep')
    doxygen(root)
    
@action
def build(root, target):
    prep(root)
    sphinx(root, target)

@action
def ci_publish(root, target=None):
    root_only(root)
    if not args.branch:
        exit('Error: --branch <branchname> is required')
    shell('aws s3 sync --only-show-errors --delete site s3://%s/exclude/ci/branches/%s' % (staging_host, args.branch))
    log('published at http://staging.spec.oneapi.com.s3-website-us-west-2.amazonaws.com/exclude/ci/branches/%s/'
          % (args.branch))
    
@action
def prod_publish(root, target=None):
    # sync staging to prod
    shell("aws s3 sync --only-show-errors --delete s3://%s/ s3://spec.oneapi.com/ --exclude 'exclude/*'" % (staging_host))
    log('published at http://spec.oneapi.com/')
    
@action
def stage_publish(root, target=None):
    root_only(root)
    local_top = 'site'
    local_versions = join(local_top, 'versions')
    local_versions_x = join(local_versions, common_conf.oneapi_spec_version)
    local_versions_latest = join(local_versions, 'latest')
    s3_top = 's3://%s' % (staging_host)
    s3_versions = '%s/versions' % s3_top
    s3_versions_x = '%s/%s' % (s3_versions,common_conf.oneapi_spec_version)
    s3_versions_latest = '%s/latest' % s3_versions

    # Sync everything but versions
    # Do not use --delete, it will delete old versions
    #  even with the --exclude
    shell(('aws s3 sync --only-show-errors'
           ' --exclude \'versions/*\''
           ' %s %s')
          % (local_top, s3_top))
    # Sync the newly created version directory
    shell(('aws s3 sync --only-show-errors --delete'
           ' %s %s')
          % (local_versions_x, s3_versions_x))
    shell(('aws s3 sync --only-show-errors --delete'
           ' %s %s')
          % (local_versions_latest, s3_versions_latest))

    log('published at http://staging.spec.oneapi.com.s3-website-us-west-2.amazonaws.com/')

    
@action
def spec_venv(root, target=None):
    root_only(root)
    venv.create('spec-venv', with_pip=True, clear=True)
    pip = 'spec-venv\Scripts\pip' if platform.system() == 'Windows' else 'spec-venv/bin/pip'
    shell('%s install -r requirements.txt' % pip)
    
@action
def clones(root, target=None):
    root_only(root)
    # defer loading this so script can be invoked without installing packages
    from git import Repo
    for repo_base in repos:
        dir = join('repos',repo_base)
        if os.path.exists(dir):
            continue
        uri = ('https://gitlab.devtools.intel.com/DeveloperProducts/'
               'Analyzers/Toolkits/oneAPISpecifications/%s.git' % repo_base)
        log('clone:', uri)
        if not args.dry_run:
            Repo.clone_from(uri, dir, multi_options=['--depth','1'])
    
@action
def site(root, target=None):
    root_only(root)
    # Build the docs
    prep()
    sphinx('html')
    sphinx('latexpdf')

    # Build the site. It will have everything but the older versions
    site = 'site'
    versions = join(site,'versions')
    versions_x = join(versions, common_conf.oneapi_spec_version)
    pdf = join('build','latex','oneAPI-spec.pdf')
    html = join('build','html')
    rm(site)
    copytree('site-root','site')
    makedirs(versions)
    copytree(html, versions_x)
    copy(pdf, versions_x)
    for t in tarballs:
        tf = join('repos','oneapi-spec-tarballs','tarballs','%s.tgz' % t)
        log('cd',versions_x,'&& tar zxf',tf)
        if not args.dry_run:
            with tarfile.open(tf) as tar:
                tar.extractall(versions_x)
    copytree(versions_x, join(versions, 'latest'))

@action
def ci(root, target=None):
    root_only(root)
    clones()
    site()
    if args.branch == 'publish':
        stage_publish()
    else:
        ci_publish()
    
staging_host = 'staging.spec.oneapi.com'

commands = {'ci': ci,
            'ci-publish': ci_publish,
            'clean': clean,
            'clones': clones,
            'dockerbuild': dockerbuild,
            'dockerpush': dockerpush,
            'dockerrun': dockerrun,
            'html': build,
            'latexpdf': build,
            'prep': prep,
            'prod-publish': prod_publish,
            'site': site,
            'spec-venv': spec_venv,
            'stage-publish': stage_publish}
    
dirs = ['oneCCL',
        'oneDAL',
        'oneMKL',
        'oneTBB',
        'oneVPL',
        'dpcpp',
        'oneDPL',
        'oneDNN']

tarballs = ['oneMKL',
            'oneL0',
            'oneDAL']

repos = ['onetbb-spec',
         'oneapi-spec-tarballs']


def main():
    global args
    parser = argparse.ArgumentParser(description='Build oneapi spec.')
    parser.add_argument('action',choices=commands.keys())
    parser.add_argument('root', nargs='?', default='.')
    parser.add_argument('--branch')
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()

    commands[args.action](args.root, args.action)

main()
