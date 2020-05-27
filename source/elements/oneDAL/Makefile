
.PHONY: build doxygen

html:
	sphinx-build -M html source build -q

pdf:
	sphinx-build -M latexpdf source build -q

doxygen:
	doxygen

parse-doxygen: doxygen
	mkdir -p build
	python -m dalapi.doxypy.cli doxygen/xml --compact > build/tree.yaml

clean:
	rm -rf build
