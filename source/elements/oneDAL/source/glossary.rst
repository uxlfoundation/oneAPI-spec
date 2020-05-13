.. _glossary:

=========
Glossary
=========

Machine learning terms
======================

.. glossary::
    :sorted:

    Categorical feature
        A :term:`feature` with a discrete set of possible values without ordering.

        Synonyms: nominal feature.

    Classification
        A :term:`supervised machine-learning problem<Supervised learning>` of assigning
        discrete :term:`labels<Label>` (:term:`categorical<Categorical feature>` or :term:`ordinal<Ordinal feature>`)
        to :term:`feature vectors<Feature vector>`.

    Continuous feature
        A :term:`feature` with values in a domain of real numbers.

        Synonyms: quantitative feature.

    Dataset
        A collection of :term:`observations<Observation>`.

    Feature
        A particular property or quality of a real object or an event.
        Has a defined type and domain.

        Synonyms: attribute, variable

    Feature value
        A single point in the domain of the :term:`feature`.

    Feature vector
        A vector that encodes information about single real object or an event.
        Contains at least one :term:`feature value`.

    Inference
        A process of applying a :term:`trained<Training>` :term:`model` to the :term:`inference set` with a goal to
        predict :term:`responses<Response>` of the :term:`labels<Label>`.

        Synonyms: prediction.

    Inference set
        An unlabeled :term:`dataset` used at the :term:`inference` stage to make an outputs from the :term:`model`.

    Label
        :term:`Feature` of some object or event which is unavailable at the :term:`inference` stage
        and needs to be predicted.

    Model
        A result of :term:`training` machine-learning algorithm that stores information necessary to run
        :term:`inference` on a new :term:`dataset`.

    Observation
        A vector of at least one :term:`feature` value and zero or more :term:`label<Label>` values.
        Each of :term:`labels<Label>` and :term:`features<Feature>` can encode different objects or events.

        Synonyms: instance, sample.

    Ordinal feature
        A :term:`feature` with a discrete set of possible values and some ordering between them.

    Regression
        A :term:`supervised machine-learning problem<Supervised learning>` of assigning
        :term:`continuous<Continuous feature>` :term:`labels<Label>` to
        :term:`feature vectors<Feature vector>`.

    Response
        A value of a single :term:`label`. For example, response may be a flag
        indicating that an observation belongs to a particular class.

    Supervised learning
        :term:`Training` process with :term:`labeled<Label>` training set.

    Training
        A search process of the best :term:`model`.

    Training set
        A :term:`dataset` used at the :term:`training` stage to create a :term:`model`.

    Unsupervised learning
        :term:`Training` process where target :term:`labels<Label>` are not present in the training set.

|dal_short_name| library terms
==============================

.. glossary::
    :sorted:

    Batch Mode
        The computation mode for an algorithm in |dal_short_name|, where all the data needed for
        computation is available at the start and fits the memory of the device on which the computations are performed.

    Contiguous data
        A special property of the :term:`data format`: the data are stored as one contiguous memory block.

    Data format
        The representation of internal structure of the data: this information is enough to efficiently access them.

    Data type
        An integral or floating-point type which is used to physically store the data.

    Homogeneous data
        A special property of the :term:`data format`: all the :term:`features<Feature>` have the same type and domain.

    Immutability
        The object is immutable if it is not possible to change its state after creation.

    Online Mode
        The computation mode for an algorithm in |dal_short_name|, where the data needed for computation
        becomes available in parts over time.

    Reference-counted object
        A |dal_short_name| object which stores the number of references to the unique implementation.
        Such object has a lightweight copy constructor and assignment operator, which simply increases the number of references.
        Implementation is automatically freed when the number of references becomes equal to zero.

    Workload
        A task of applying a |dal_short_name| algorithm to a dataset.

Other
=====
TODO: this section looks like a general one for the whole oneAPI spec.

.. glossary::
    :sorted:

    API
        Application Programming Interface

    DPC++
        Data Parallel C++ (DPC++) is a high-level language designed for data parallel programming productivity.
        DPC++ is based on :term:`SYCL* <sycl>` from the Khronos* Group to support data parallelism and heterogeneous programming.

    Host/Device
        OpenCL [OpenCLSpec]_ refers to CPU that controls the connected GPU executing kernels.

    JIT
        Just in Time Compilation --- compilation during execution of a program.

    Kernel
        Code written in OpenCL [OpenCLSpec]_ or :term:`SYCL` and executed on a GPU device.

    SPIR-V
        Standard Portable Intermediate Representation - V is a language for intermediate representation of compute kernels.

    SYCL
        SYCL(TM) [SYCLSpec]_ --- high-level programming model for OpenCL(TM) that enables code for heterogeneous
        processors to be written in a "single-source" style using completely standard C++.



