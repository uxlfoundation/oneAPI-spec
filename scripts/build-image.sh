#! /bin/bash
mkdir Docker/tmp
cp requirements.txt Scripts/install.sh Docker
cd Docker
docker build --build-arg http_proxy=$http_proxy --build-arg https_proxy=$https_proxy --tag oneapi-spec .
# cleanup
rm requirements.txt install.sh



