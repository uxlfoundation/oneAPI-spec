============
Introduction
============

|dal_full_name| (|dal_short_name|) is a library that provides building blocks covering all stages of data analytics: data acquisition
from a data source, preprocessing, transformation, data mining, modeling, validation and decision making.

|dal_short_name| supports the concept of the end-to-end analytics when some of data analytics stages are performed on the
edge devices (close to where the data is generated and where it is finally consumed). Specifically,
|dal_short_name| Application Programming Interfaces (APIs) are agnostic about a particular cross-device
communication technology and therefore can be used within different end-to-end analytics frameworks.

Library consists of the following major components:

- Data Management

- Algorithms

- Services

The Data Management component includes classes and utilities for data acquisition, initial preprocessing
and normalization, for data conversion into numeric formats done by one of supported Data Sources
and for model representation.

The Algorithms component consists of classes that implement algorithms for data analysis (data mining)
and data modeling (training and prediction). These algorithms include matrix decompositions, clustering,
classification, and regression algorithms, as well as association rules discovery.

The Services component includes classes and utilities used across Data Management and Algorithms components.
These classes enable memory allocation, error handling.