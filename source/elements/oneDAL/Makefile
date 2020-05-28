GH_PAGES = build/gh-pages

.PHONY: build doxygen parse-doxygen clean gh-pages

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
	rm -rf build/html

gh-pages: build
	cp -r build/html/* $(GH_PAGES)
	cd $(GH_PAGES) && \
		git checkout gh-pages && \
		git add . && \
		git commit -m Update && \
		git push origin gh-pages
