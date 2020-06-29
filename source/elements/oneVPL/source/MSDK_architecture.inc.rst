SDK functions fall into the following categories:

======================================     ====================================== 
Category                                   Description
======================================     ======================================
DECODE	                                   Decode compressed video streams into raw video frames
ENCODE	                                   Encode raw video frames into compressed bitstreams
VPP	                                   Perform video processing on raw video frames
CORE	                                   Auxiliary functions for synchronization
Misc	                                   Global auxiliary functions
======================================     ======================================

With the exception of the global auxiliary functions, SDK functions are named after their functioning
domain and category, as illustrated below. Here, SDK only exposes video domain functions.

.. image:: images/sdk_function_naming_convention.png
   :alt: SDK function name notation

Applications use SDK functions by linking with the SDK dispatcher library, as illustrated below.
The dispatcher library identifies the hardware acceleration device on the running platform,
determines the most suitable platform library, and then redirects function calls.
If the dispatcher is unable to detect any suitable platform-specific hardware, the dispatcher redirects SDK function calls
to the default software library.

.. graphviz::

  digraph {
    rankdir=TB;
    Application [shape=record label="Application" ];
    Sdk [shape=record  label="SDK Dispatcher Library"];
    Lib1 [shape=record  label="SDK Library 1 (CPU)"];
    Lib2 [shape=record  label="SDK Library 2 (Platform 1)"];
    Lib3 [shape=record  label="SDK Library 3 (Platform 2)"];
    Application->Sdk;
    Sdk->Lib1;
    Sdk->Lib2;
    Sdk->Lib3;
  }

  
