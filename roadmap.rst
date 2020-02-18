=========
 Roadmap
=========

Schedule
========

========   ==========  ===========
Version    Date        Notes
========   ==========  ===========
0.5.0      11/17/2019  First Public Release
0.6.0_     01/30/2020  Open source Release
0.7.0_     03/26/2020  50%
0.8.0_     05/28/2020  80%
0.9.0_     07/30/2020  Final Gold Preview
1.0.0_     08/30/2020  Gold Release
========   ==========  ===========

Details:
========


0.6.0
-----

We will publish:

- HTML and PDF on spec.oneapi.org
- Sources in github

No public announcement until we can ensure we are addressing earlier
feedback.

- Overall

  - New
  
    - Unified into single doc
    - PDF of unified doc available online
    - Sources in github.com/oneapi-src/oneapi-spec
    - HTML doc links back to github
    - CI builds and publishes on commits to master
- DPC++

  - New
  
    - Editing updates
    
  - Future

- DPL

  - New
  
    - Editing updates
  - Future
- oneDNN

  - New
  
    - API document inline
    - API document sources in oneapi-spec repo
  - Future
  
    - more structured API description
- oneCCL

  - New
  
    - API document inline
    - API document sources in oneapi-spec repo
- Level Zero

  - New
  
    - API document inline
    - Sources in separate repo on github
  - Future
- oneDAL

  - New
  - Future
  
    - API document included inline
    - API document sources in oneapi-spec repo
- oneTBB

  - New
  
    - API document inline
    - Sources in separate repo on github
  - Future
- oneVPL

  - New
  
    - API descriptions moved to single section
  - Future
  
    - Content?
- oneMKL

  - New
  - Future
  
    - Transition from far html to rst
    - API document inline    
    - rst sources included in oneapi-spec repo

0.7.0
-----

Summary
+++++++

Schedule
++++++++

=========  ==========
Date       Milestone
=========  ==========
3/12/2020  Cutoff date for accepting feedback for inclusion in this version
3/24/2020  Code freeze
3/26/2020  Release
=========  ==========

Elements
++++++++

- DPC++

  - Updated extensions table and description

- oneDPL

- oneDNN

  - Rework API presentation into multiple sections
  - Add introduction, execution, primitive lifecycle, and programming model
    sections

- oneCCL

  - Add initial version of API for scale-up

- Level Zero

  - Switched to RST as format, using oneapi-spec as upstream repo
  
- oneDAL

  - Add overall spec skeleton, introduction and algorithm classes sections
  - Add initial version for sections on data structures (descriptors algorithms/tables, numeric tables),
    compute modes(batch/online), distributed algorithms and generic building blocks(train/predict) 
  - Add API for 3 oneDAL algorithms

- oneTBB

  - Using oneapi-spec as upstream repo
  
- oneVPL
  
- oneMKL

  - API descriptions in structured list
  
0.8.0
-----

Summary
+++++++

All document structuring issues resolved. Content mostly complete with
placeholders for missing sections.

Schedule
++++++++

=========  ==========
Date       Milestone
=========  ==========
5/14/2020  Cutoff date for accepting feedback for inclusion in this version
5/26/2020  Code freeze
5/28/2020  Release
=========  ==========

Elements
++++++++

- DPC++

  - Updated extensions table and description

- oneDPL
  
- oneDNN

  - Add sections on primitive attributes, data types, and memory formats
  - Start extending individual primitives' pages with detailed information
    about underlying math and with usage examples

- oneCCL

  - Update page with API for scale-up
  - Update page with GPU programming model
  - Extend page with collective operations

- Level Zero
  
- oneDAL

  - Extend API description to 18 algorithms
  - Add first version for sections on programming model, algorithmics
  - Extend numeric tables and data structure sections

- oneMKL

  - Draft suitable for review so we can distribute to reviewers before
    ISC (6/28/2020).

0.9.0
-----

Summary
+++++++

Final Gold Preview. Expectation is that everything is done and only 
small edits will be made. Incorporates all external feedback.

Schedule
++++++++

=========  ==========
Date       Milestone
=========  ==========
7/16/2020  Cutoff date for accepting feedback for inclusion in this version
7/28/2020  Code freeze
7/30/2020  Release
=========  ==========

Elements
++++++++

- DPC++

  - Updated extensions table and description

- oneDPL
  
- oneDNN

  - Finish extending individual primitives' pages with detailed information
    about underlying math and with usage examples

- oneCCL

  - Finalize on sections content and details

- Level Zero
  
- oneDAL

  - Finalize on sections content and details

- oneTBB

- oneVPL

- oneMKL
  
1.0.0
-----

Summary
+++++++

API's frozen: backwards compatible
changes at discretion of project owner, non-backwards compatible change by exception only

Schedule
++++++++

=========  ==========
Date       Milestone
=========  ==========
8/17/2020  Cutoff date for accepting feedback for inclusion in this version
8/28/2020  Code freeze
8/30/2020  Release
=========  ==========

Elements
++++++++

- DPC++

  - Updated extensions table and description
