#! /bin/bash
export DEBIAN_FRONTEND=noninteractive
apt-get update
apt-get install -y \
                    python3-pip \
                    python3
apt-get install -y  \
                    doxygen \
	            git
apt-get install -y \
                    latexmk \
                    texlive-latex-base \
                    texlive-fonts-recommended \
                    texlive-fonts-extra \
                    texlive-latex-extra
apt-get install -y \
	            openssh-client
pip3 install -r requirements.txt
