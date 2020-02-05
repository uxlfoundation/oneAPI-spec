#! /bin/bash
set -e
set -x

export DEBIAN_FRONTEND=noninteractive
apt-get update
apt-get install -y \
                    python3-pip \
                    python3 \
                    wget
apt-get install -y  \
	            git
wget http://doxygen.nl/files/doxygen-1.8.17.linux.bin.tar.gz
tar zxf doxygen-1.8.17.linux.bin.tar.gz
pushd doxygen-1.8.17
./configure
set +e
make install
set -e
popd
apt-get install -y \
                    latexmk \
                    texlive-latex-base \
                    texlive-fonts-recommended \
                    texlive-fonts-extra \
                    texlive-latex-extra
apt-get install -y \
	            openssh-client
pip3 install -r requirements.txt
