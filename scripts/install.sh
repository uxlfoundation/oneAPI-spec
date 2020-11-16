#! /bin/bash

# Copyright (c) 2020, Intel Corporation
# SPDX-FileCopyrightText: 2019-2020 Intel Corporation
#
# SPDX-License-Identifier: MIT

set -e
set -x

apt-get update -qq
DEBIAN_FRONTEND=noninteractive xargs -a ubuntu-packages.txt apt-get install -qq

python3 -m venv venv
. venv/bin/activate
pip install --upgrade pip wheel
pip install --upgrade --quiet -r requirements.txt
