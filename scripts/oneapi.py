import sys
if sys.version_info[0] < 3:
    exit('Python 3 is required')
    
import argparse
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

from element import shell,sphinx
import element

sys.path.insert(0, os.path.abspath(join('source','conf')))
import common_conf

args = None

        
def get_env(var):
    return os.environ[var] if var in os.environ else ''
    
@element.action
def dockerbuild(target=None):
    element.copy('requirements.txt', 'docker')
    element.copy('scripts/install.sh', 'docker')
    element.shell('docker build'
                  ' --build-arg http_proxy=%s'
                  ' --build-arg https_proxy=%s'
                  ' --build-arg no_proxy=%s'
                  ' --tag rscohn2/oneapi-spec docker'
                  % (get_env('http_proxy'), get_env('https_proxy'), get_env('no_proxy')))

@element.action
def dockerpush(target=None):
    element.shell('docker push rscohn2/oneapi-spec')

@element.action
def dockerrun(target=None):
    element.shell('docker run --rm -it'
                  ' --user %s:%s'
                  ' --volume=%s:/build'
                  ' --workdir=/build'
                  ' rscohn2/oneapi-spec'
                  % (os.getuid(), os.getgid(), os.getcwd()))

@element.action
def clean(target=None):
    apply_dirs('clean')
    sphinx('clean')

def apply_dirs(target):
    for dir in dirs:
        with element.cd(join('source','elements',dir)):
            element.command(target)

def prep(target=None):
    apply_dirs('prep')
    
@element.action
def build(target):
    prep()
    sphinx(target)

@element.action
def ci_publish(target=None):
    if not args.branch:
        exit('Error: --branch <branchname> is required')
    shell('aws s3 sync --only-show-errors --delete site s3://%s/ci/branches/%s' % (staging_host, args.branch))
    element.log('published at http://staging.spec.oneapi.com.s3-website-us-west-2.amazonaws.com/ci/branches/%s/'
          % (args.branch))
    
@element.action
def prod_publish(target=None):
    # sync staging to prod
    shell('aws s3 sync --only-show-errors --delete s3://%s/site s3://spec.oneapi.com/' % (staging_host))
    element.log('published at http://spec.oneapi.com/')
    
@element.action
def stage_publish(target=None):
    local_top = 'site'
    local_versions = join(local_top, 'versions')
    local_versions_x = join(local_versions, common_conf.oneapi_spec_version)
    local_versions_latest = join(local_versions, 'latest')
    s3_top = 's3://%s/%s' % (staging_host,local_top)
    s3_versions = '%s/versions' % s3_top
    s3_versions_x = '%s/%s' % (s3_versions,common_conf.oneapi_spec_version)
    s3_versions_latest = '%s/latest' % s3_versions

    # Sync everything but versions
    # Do not use --delete, it will delete old versions
    #  even with the --exclude
    shell(('aws s3 sync --only-show-errors'
           ' --exclude \'site/versions/*\''
           ' %s %s')
          % (local_top, s3_top))
    # Sync the newly created version directory
    shell(('aws s3 sync --only-show-errors --delete'
           ' %s %s')
          % (local_versions_x, s3_versions_x))
    shell(('aws s3 sync --only-show-errors --delete'
           ' %s %s')
          % (local_versions_latest, s3_versions_latest))

    element.log('published at http://staging.spec.oneapi.com.s3-website-us-west-2.amazonaws.com/%s' % local_top)

    
@element.action
def spec_venv(target=None):
    venv.create('spec-venv', with_pip=True, clear=True)
    pip = 'spec-venv\Scripts\pip' if platform.system() == 'Windows' else 'spec-venv/bin/pip'
    shell('%s install -r requirements.txt' % pip)
    
@element.action
def clones(target=None):
    # defer loading this so script can be invoked without installing packages
    from git import Repo
    for repo_base in repos:
        dir = join('repos',repo_base)
        if os.path.exists(dir):
            continue
        uri = ('https://gitlab.devtools.intel.com/DeveloperProducts/'
               'Analyzers/Toolkits/oneAPISpecifications/%s.git' % repo_base)
        element.log('clone:', uri)
        if not args.dry_run:
            Repo.clone_from(uri, dir, multi_options=['--depth','1'])
    
@element.action
def site(target=None):
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
    element.rm(site)
    element.copytree('site-root','site')
    element.makedirs(versions)
    element.copytree(html, versions_x)
    element.copy(pdf, versions_x)
    for t in tarballs:
        tf = join('repos','oneapi-spec-tarballs','tarballs','%s.tgz' % t)
        element.log('cd',versions_x,'&& tar zxf',tf)
        if not args.dry_run:
            with tarfile.open(tf) as tar:
                tar.extractall(versions_x)
    element.copytree(versions_x, join(versions, 'latest'))

@element.action
def ci(target=None):
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
    parser.add_argument('--branch')
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()
    element.dry_run = args.dry_run

    commands[args.action](args.action)

main()
