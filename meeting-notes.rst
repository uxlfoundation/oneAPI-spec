===============
 Meeting Notes
===============

2020-08-19
==========

* Opens

  * pdf issues

    * consider dropping. Ask TAB.
      
    * tables do not look good, columns over-write each other

      AR: Vasily pointers for fixing
      AR: Robert look for something general

    * table of contents is too long. Need individual TOC

      AR: Robert investigate
    
    * page breaks for sections

  * integrating level zero

    AR: Robert and Zack talk offline

  * MKL has domains, can be optional

    * See DPC++ & VPL for description of optional functionality
    * Throw error
    * Macro to check

      AR: Alexey to send c++ standard method
      
* Versioning

  * Primary change is to drop component versioning as required.
  * Teams need the freedom to define API versioning. Discussion about
    whether this needs to be a spec feature or could be a product
    feature. No strong objections to dropping spec component
    versioning today, but will consider adding it in future when there
    is a clear need.

* Governance

  * No objections


2020-08-11
==========

* Opens

  * Dates of releases and ability to make changes for individual elements
  * coupled versions vs elements versioning
    * concern about in sync vs time, don't want randomness in components
  * macro for testing which version of spec is supported by implementation
    AR: Robert, define following pattern for components

    AR: encourage implementations to refer to oneAPI version number
    not element number for master number, unless reason

    major.minor relates to IP, revision for everything else
    we should be able to change minor more quickly.
    revision can update mapping to element versions
    update rev on quarterly releases
    
* 1.0 release

  * OK to add APIs, but don't want to break compatibliity
  *

* Review governance doc
* Review versioning doc
  
