===============
 Content Guide
===============

Principles
==========

* Use your judgement about following these recommendations
  
  * OK to consider ROI

* Strive for consistency across components

  * Newer specs expected to following pre-existing practices
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
	  

	  
		 
	


	    
g.	Short example demonstrating its use, optional. If the functionality of a given SW domain can be represented with a few examples, they are provided in the dedicated section of the domain, not in section that describes API. The structure of the example  up to SW
h.	Class description of predefined style including public methods, members. Recommended order: aliases, members, methods. Description can include other things such as base classes, if it makes the description clear
i.	Brief definition of the class is required, if it is unclear from the context of the section or is not specified in different sections
ii.	The table of predefined style with details of API: 
1.	template parameters listing ranges of supported values
2.	aliases which are used in the specifications below
3.	public members (constructors/destructors, getters/setters, other methods)
4.	methods with description of their arguments, return value  in this order. The description of the arguments can be omitted, when it is clear from the context
5.	Setters/getters operating with the same feature of the class are grouped together in the description
6.	Overloaded methods are grouped together
7.	The description specifies pre-conditions, post-conditions and invariants, when applies
8.	Specializations are provided after the description of the class template with the discussion of their specific values

i.	Free function signature of predefined style
i.	Brief definition of the function is required, if it is unclear from the context of the section or is not specified in different sections
ii.	The table of predefined style with details of API:
1.	Template parameters listing ranges of supported values
2.	Description of their arguments, return value  in this order. The description of the arguments can be omitted, when it is clear from the context
3.	Overloaded functions are grouped together
4.	The description specifies pre-conditions, post-conditions and invariants, when applies
5.	Specializations are provided after the description of the function template with the discussion of their specific values
j.	Enum description of the predefined style
i.	Brief definition is required, if it is unclear from the context of the section or is not specified in different section
ii.	The table of predefine style that lists possible enumeration values with their brief description
k.	Constants or define of the predefined style
i.	  Brief definition including discussion of its value is required, if it is unclear from the context of the section or is not specified in different section
l.	Other API pieces (such as service macros serving to shape the main API) can be described, when it helps the spec implementer understand the rest specs.
m.	The section can contain description more than one API (such as macros or classes representing ranges of function arguments), if all of them are logically connected. Cross SW data types are described once in the dedicated sections which are referred from other sections. Up to SW
n.	If the section includes multiple subsections, a navigation that allows returning to the top of the document is provided in the end of such section. Additional navigation is provided to simplify transition to the section below, if it is mentioned in the previous sections. Cross-navigation is provided to simplify transition between specs of the related functionalities. 
9.	Components have a bibliography section, when it applies (potential to have cross oneAPI bibliography, standards, etc)


