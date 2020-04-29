===============
 Content Guide
===============

Principles
==========

* Use your judgement about following these recommendations
  
  * OK to consider ROI

* Strive for consistency across components

  * Especially newer specs
  * Component must be consistent with itself

* Target audience

  * implementors
  * sophisticated users who will be providing feedback

    * assume final product will have separate programming guide with
      tutorial-level information

* Spec must be publishable as part of unified doc and as standalone
  describing a single component

  * when published as a standalone, it will contain some sections that
    are normally at top-level. e.g. bibliography
  
Structure of Document
=====================

* Top-level spec contains sections for information common to all
  libraries

  * Conventions

    * C++ standard compliance 
    * Basic scalar data types
    * Exceptions
    * Usm pointers
    * Guidelines (or just guidelines that include all other conventions?)
    * Namespaces (dedicated table of the namespaces?)

  * Math notations
  * Glossary: terms common to multiple components. e.g. SYCL, DPC++, USM
  * Bibliography

* Component-level sections for information specific to the component
  
  * Introduction: defines the scope of the SW
  * Glossary: defines terms used to describe specs
  * Math notations
  * Namespace-related information: e.g., the first level namespace,
    the lib introduces additional namespaces based on some internal
    logic
  * header files
  * SW API usage with examples demonstrating the API of the lib
  * Programming model, the most important basic blocks, their intended use cases

    * may use UML diagrams, sequence notation

  * Detailed functionality for the blocks described above.

    * functionality or API-level descriptions
    * description is defined by the breakdown of the SW. e.g. All API
      related to functional block are grouped in same section
    * description with sufficient information to understand definition
      and how to implement it. May refer to other documents for details.
    * Each API/functionality broken down into subsections with consistent subsection naming/ordering

      * Following information should be covered, but may be presented
        at API-level, group-level, or component-level as appropriate.

	* e.g. group of API shares a common namespace/header
          file. Describe namespace naming scheme when group is
          introduced

      * Common to all interface elements

        * Name of API/functionality
        * Syntax of interfaces
        * namespace
        * header file with API and related data structures
        * description
        * examples. keep in mind the target audience when deciding how much detail is needed

      * Interface-element specific

	* Class

	  * signature (template <int d> class foo;)
          * brief description
	  * template parameters, including ranges of supported values
	  * public members

	    * Recommended groupings

	      * member types
              * member functions
	      * non-member functions (e.g. static and operator overloads)

		* Recommended subgroups

		  * overloads
		  * constructor/destructor, getter/setters

	  * method-level descriptions

	    * subgroups may share descriptions
            * breakdown

              * signature
	      * template parameters listing ranges of supported values
	      * parameters (may omit when apparent from context)
	      * return value
	      * pre/post conditions
	      * invariants
	      * template specializations
	      * exceptions raised

	* Free functions (consistent with methods, where appropriate)

          * signature
	  * template parameters listing ranges of supported values
	  * parameters (may omit when apparent from context)
	  * return value
	  * pre/post conditions
	  * invariants
	  * template specializations
	  * exceptions raised

        * enums

	  * brief description
	  * enumerations values and brief description

	* constants/define

	  * brief description

	* service macros
