
.PHONY: build doxygen

build:
	sphinx-build -M html source build -q

doxygen:
	doxygen

parse-doxygen: doxygen
	mkdir -p build
	python -m dalapi.doxypy.cli doxygen/xml --compact > build/tree.yaml

clean:
	rm -rf build
