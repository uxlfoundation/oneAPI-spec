============
Introduction
============

|dal_full_name| (|dal_short_name|) is a library that provides building blocks covering all stages of data analytics: data acquisition
from a data source, preprocessing, transformation, data mining, modeling, validation and decision making.

.. image:: _static/data_analytics_stages.png
  :width: 800
  :alt: Data analytis stages

|dal_short_name| supports the concept of the end-to-end analytics when some of data analytics stages are performed on the
edge devices (close to where the data is generated and where it is finally consumed). Specifically,
|dal_short_name| Application Programming Interfaces (APIs) are agnostic about a particular cross-device
communication technology and therefore can be used within different end-to-end analytics frameworks.

.. image:: _static/e2eframeworks.png
  :width: 800
  :alt: End to End Analytics Frameworks

|dal_short_name| consists of the following major components: 

 - The :ref:`Data Management <data_management>` component includes classes and utilities for data acquisition, initial preprocessing and normalization,
   for data conversion into numeric formats done by one of supported Data Sources, and for model representation.

 - The :ref:`Algorithmst <algorithms>` component consists of classes that implement algorithms for data analysis (data mining), and data modeling
   (training and prediction). These algorithms include matrix decompositions, clustering, classification, and regression
   algorithms, as well as association rules discovery. 
   Algorithms support the following computation modes:

   - :ref:`Batch processing <Batch>`

   - :ref:`Online processing <Online>`

   - :ref:`Distributed processing <Distributed>`

   In the batch processing mode, the algorithm works with the entire data set to produce the final result. A more
   complex scenario occurs when the entire data set is not available at the moment or the data set does not fit
   into the device memory.

   In the online processing mode, the algorithm processes a data set in blocks streamed into device memory by doing
   incrementally updating partial results, which are finalized upon processing of the last data block.

   In the distributed processing mode, the algorithm operates on a data set distributed across several devices
   (compute nodes). The algorithm produces partial results on each node, which are finally merged into the final
   result on the master node.

   Distributed algorithms in |dal_short_name| are abstracted from underlying cross-device communication technology,
   which enables use of the library in a variety of multi-device computing and data transfer scenarios.
   
   Depending on the usage, algorithms operate both on actual data (data set) and data models.
   Analysis algorithms typically operate on data sets. Training algorithms typically operate
   on a data set to train an appropriate data model. Prediction algorithms typically work with
   the trained data model and with a working data set.


 - The **Services** component includes classes and utilities used across Data Management and Algorithms components.
   These classes enable memory allocation, error handling.

Classes in Data Management, Algorithms, and Services components cover the most important usage scenarios and allow
seamless implementation of complex data analytics workflows through direct API calls. At the same time the library
is an object-oriented framework that helps customize the API by redefining particular classes and methods of the library.
