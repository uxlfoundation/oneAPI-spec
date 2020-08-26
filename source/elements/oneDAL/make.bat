@echo off
if /I %1 == html goto :html
if /I %1 == pdf goto :pdf
if /I %1 == doxygen goto :doxygen
if /I %1 == parse-doxygen goto :parse-doxygen
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
rd /s /q "build\doctrees"
rd /s /q "build\html"
rd /s /q "build\latex"
goto :eof
