===============
 Meeting Notes
===============

 2020-11-23
============

* Updates

  * Published 1.0 rev 3

    * CCL fixes, version macros
    * Fixed PDF - MKL tables are still an issue
    
* Discussion of completing spec before product release

  * Need to do implementation at same time as definition

    * experience from implementation leads to changes
    * specification first would lock us in too early

  * implementation experience

    * preview features in products
    * internal prototyping

  * preview features
    
    * no claim for long term support
    * parameters and behavior can change
    * not on by default, protected by macro on other mechanism, or
      otherwise called out as experimental
    * still product quality
    * Used by:
      * mediasdk, API next
      * tbb, dpl have preview features
      * rendering toolkit
    * Do we need to formalize/make practice consistent across
      products?
    * different process for big new features and smaller features
    * preview feature later becomes official part of product

* Need to sketch out v1.1

  * Expect it to be bug fix for most components
  * Big additions

    * oneART: advanced ray tracing

      * not openswor or opengl, but rest of rendering toolkit (6-7
        components)
      * ospray is prototype for anari from khronos

	* khronos spec in a few months
	  
    * oneDNN graph

      * currently published as standalone
	
    * IPP

      * image processing, data compression

  * Need list of items

    * See oneDAL as sample:

* Bug/typo/etc fixes
* Extensions
  - Data Management:
    - SoA table
    - CSR table
  -  Algorithms:
     - Random Forest for classification, training and inference, batch computing mode
     - Random Forest for regression, training and inference, batch computing mode
     - Support Vector Machine/SVM, binary classification, training and inference, batch computing mode
     - At least one kernel function to be used with SVM (to be defined)
       - Linear Regression, training and inference, batch computing mode
       - extension of K Nearest Neighbors model with support of KDTree
     - Covariance
     - Low Order Moments
						      

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
  
