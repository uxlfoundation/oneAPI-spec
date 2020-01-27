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
SUBDIRS       := oneCCL oneDAL oneMKL oneTBB oneVPL dpcpp oneDPL oneDNN
SUBDIR_PATHS   := $(foreach subdir,$(SUBDIRS),source/elements/$(subdir))
# Need absolute path in case we cd before invoking the builder
BUILDER       := $(realpath source/elements/build.py)

.PHONY: clones help $(TOPTARGETS) $(SUBDIR_PATHS)

# Build the web site
public: html latexpf
	rm -rf public
	mkdir public
	cp -r build/html/* public
	cp -r build/latex/*.pdf public
	tar -C public -xf repos/oneapi-spec-tarballs/tarballs/oneMKL.tgz
	tar -C public -xf repos/oneapi-spec-tarballs/tarballs/oneDAL.tgz

# Virtual environment with all dependencies installed
spec-venv:
	$(PYTHON) -m venv spec-venv
	. spec-venv/bin/activate && pip install -r requirements.txt

# Support repos
clones:
	cd repos && git clone https://gitlab.devtools.intel.com/DeveloperProducts/Analyzers/Toolkits/oneAPISpecifications/onetbb-spec.git
	cd repos/onetbb-spec && git checkout onetbb-spec
	cd repos && git clone --depth 1 https://gitlab.devtools.intel.com/DeveloperProducts/Analyzers/Toolkits/oneAPISpecifications/oneapi-spec-tarballs.git

# Generic rule for all subdirectories
$(SUBDIR_PATHS):
	cd $@ && $(PYTHON) $(BUILDER) $(MAKECMDGOALS)

# Everything that must be done before invoking sphinx (e.g. run doxygen)
prep: MAKECMDGOALS=prep

prep: $(SUBDIR_PATHS)

# prep the subdirectories then build the document
$(FORMATS): prep
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)

# Only clean sphinx in the top level
clean-sphinx:
	@$(SPHINXBUILD) -M clean "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)

# clean the subdirectories then clean the master document
clean: $(SUBDIR_PATHS) clean-sphinx
	rm -rf $(PUBLICDIR)

