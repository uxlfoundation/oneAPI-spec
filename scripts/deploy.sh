#! /bin/bash

# Exit on error
set -e

git_branch=`git rev-parse --abbrev-ref HEAD`
git_branch=${CI_COMMIT_REF_NAME:=$git_branch}
git_branch=`echo $git_branch | tr / _`
deploy_dir=/var/www/html/oneapi/$git_branch

echo "$SSH_KEY" > id_rsa
unset SSH_KEY
chmod 600 id_rsa

# Clear the old web server directory and copy the new one
ssh -o StrictHostKeyChecking=no -i id_rsa oneapi@ansatnuc02.an.intel.com rm -rf $deploy_dir
scp -r -i id_rsa public oneapi@ansatnuc02.an.intel.com:$deploy_dir

rm id_rsa
