#! /bin/bash
set -e
pushd docker
cp ../requirements.txt ../scripts/install.sh .
docker build --build-arg http_proxy=$http_proxy --build-arg https_proxy=$https_proxy --tag rscohn2/oneapi-spec .
# cleanup
rm requirements.txt install.sh
popd



