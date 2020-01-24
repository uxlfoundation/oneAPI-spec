# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line.
PYTHON        := python3

#SPHINXOPTS    := -v -v -v
SPHINXOPTS    := -q -j auto
SPHINXBUILD   := sphinx-build
SOURCEDIR     := source
BUILDDIR      := build
PUBLICDIR     := public
FORMATS       := html latexpdf
DOXYGENDIR    := doxygen
TOPTARGETS    := clean prep
SUBDIRS       := oneCCL oneDAL oneMKL oneVPL dpcpp oneDPL oneDNN
SUBDIR_PATHS   := $(foreach subdir,$(SUBDIRS),source/elements/$(subdir))
BUILDER       := $(realpath source/elements/build.py)
TBB_URI       := ssh://git@gitlab.devtools.intel.com:29418/DeveloperProducts/Runtimes/Threading/tbb-doc.git

.PHONY: clones help $(TOPTARGETS) $(SUBDIR_PATHS)

# Virtual environment with all dependencies installed
spec-venv:
	$(PYTHON) -m venv spec-venv
	. spec-venv/bin/activate && pip install -r requirements.txt

clones:
	cd repos && git clone $(TBB_URI)
	cd repos/tbb-doc && git checkout onetbb-spec

prep: $(SUBDIR_PATHS)

# make same target in all subdirectories
$(SUBDIR_PATHS):
	cd $@ && $(PYTHON) $(BUILDER) $(MAKECMDGOALS)

$(FORMATS):
	$(MAKE) -j4 prep
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)

clean-sphinx:
	@$(SPHINXBUILD) -M clean "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)

clean: $(SUBDIR_PATHS) clean-sphinx
	rm -rf $(PUBLICDIR)

public: html latexpdf
	rm -rf public
	mkdir public
	cp -r build/html/* public
	cp -r build/latex/*.pdf public
	tar -C public -xf tarballs/oneMKL.tgz
	tar -C public -xf tarballs/oneDAL.tgz
