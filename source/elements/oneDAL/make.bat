@echo off
REM SPDX-FileCopyrightText: 2019-2020 Intel Corporation
REM
REM SPDX-License-Identifier: CC-BY-4.0
REM SPDX-License-Identifier: MIT

if /I %1 == html goto :html
if /I %1 == pdf goto :pdf
if /I %1 == doxygen goto :doxygen
if /I %1 == parse-doxygen goto :parse-doxygen
if /I %1 == gh-pages goto :gh-pages
if /I %1 == clean goto :clean

:html
sphinx-build -M html source build -q
goto :eof

:pdf
sphinx-build -M latexpdf source build -q
goto :eof

:doxygen
doxygen
goto :eof

:parse-doxygen
if not exist build mkdir build
python -m dalapi.doxypy.cli doxygen/xml --compact > build/tree.yaml
goto :eof

:clean
rd /s /q build
goto :eof

:gh-pages
set gh_pages=build\gh-pages
for /f %%i in ('git branch --show-current') do set git_branch=%%i
for /f %%i in ('git remote get-url origin') do set git_url=%%i

if not exist %gh_pages% (
    if not exist build mkdir build
    pushd build
    git clone --single-branch --branch gh-pages %git_url% gh-pages
    popd
)

if not exist %gh_pages%\%git_branch% mkdir %gh_pages%\%git_branch%
if not exist build\html (
    echo Error: build\html directory does not exist, build html first
    goto :eof
)
xcopy "build\html\*" %gh_pages%\%git_branch% /y /s
rd /s /q %gh_pages%\%git_branch%\.nojekyll

pushd %gh_pages%
git checkout gh-pages
git pull --rebase origin gh-pages
git add .
git commit -m "Update gh-pages for %git_branch%"
git push origin gh-pages
popd
goto :eof
