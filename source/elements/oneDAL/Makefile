
.PHONY: build doxygen

build:
	sphinx-build -M html source build -q

doxygen:
	doxygen

parse-doxygen: doxygen
	python -m dalapi.doxypy.cli doxygen/xml --compact > build/tree.yaml
