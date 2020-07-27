============
Architecture
============

SDK functions fall into the following categories:

.. glossary::

   DECODE
      Functions that decode compressed video streams into raw video frames

   ENCODE
      Functions that encode raw video frames into compressed bitstreams

   VPP
      Functions that perform video processing on raw video frames

   CORE
      Auxiliary functions in the SDK for synchronization

   Misc
      Global auxiliary functions

With the exception of the global auxiliary functions, SDK functions are named
after their functioning domain and category, as shown in Figure 1. The oneVPL
SDK exposes video domain functions.

.. figure:: images/sdk_function_naming_convention.png
   :alt: SDK function name notation

   Figure 1: SDK function name notation

Applications use SDK functions by linking with the SDK dispatcher library, as
shown in Figure 2. The dispatcher library identifies the hardware acceleration
device on the running platform, determines the most suitable platform library
for the identified hardware acceleration, and then redirects function calls accordingly.

.. graphviz::
   :caption: Figure 2: SDK library dispatching mechanism

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

.. toctree::
   :hidden:

   MSDK_decoding
   MSDK_encoding
   MSDK_processing
