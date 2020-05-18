.. _glossary:

=========
Glossary
=========

Machine learning terms
======================

.. glossary::
    :sorted:

    Categorical feature
        A :term:`feature` with a discrete domain without ordering between values.

        Synonyms: nominal feature, qualitative feature.

        Examples: a person's gender, color of a car.

    Classification
        A :term:`supervised machine-learning problem<Supervised learning>` of assigning
        :term:`labels<Label>` to :term:`feature vectors<Feature vector>`.

    Clustering
        An :term:`unsupervised machine-learning problem<Unsupervised learning>` of grouping
        :term:`feature vectors<Feature vector>` onto (usually
        :term:`categorical<Categorical feature>`) groups without prior information on them.

    Continuous feature
        A :term:`feature` with values in a domain of real numbers.

        Synonyms: quantitative feature, numerical feature.

        Examples: a person's height, the price on the house.

    Dataset
        A collection of :term:`observations<Observation>`.

    Feature
        A particular property or quality of a real object or an event.
        Has a defined type and domain. In machine learning tasks, feature is
        considered as input variable independent from others.

        Synonyms: attribute, variable, input variable.

    Feature vector
        A vector that encodes information about single real object or an event.
        Contains at least one :term:`feature`.

    Inference
        A process of applying a :term:`trained<Training>` :term:`model` to the :term:`inference set` with a goal to
        make outputs based on input :term:`feature vectors<Feature vector>`.

        Synonyms: prediction.

    Inference set
        A :term:`dataset` (usually without :term:`responses<Response>` present)
        used at the :term:`inference` stage to make an outputs from the :term:`model`.

    Label
        A :term:`response` with :term:`categorical<Categorical feature>` or :term:`ordinal<Ordinal feature>`
        values. This is an output in :term:`classification` and :term:`clustering` tasks.

    Model
        A result of :term:`training` machine-learning algorithm that stores information necessary to run
        :term:`inference` on a new :term:`dataset`.

    Observation
        A vector of at least one :term:`feature` and zero or more :term:`responses<Response>`.
        Each of them can encode different objects or events.

        Synonyms: instance, sample.

    Ordinal feature
        A :term:`feature` with a discrete set of possible values and some ordering between them.

    Regression
        A :term:`supervised machine-learning problem<Supervised learning>` of assigning
        :term:`continuous<Continuous feature>` :term:`responses<Response>` to
        :term:`feature vectors<Feature vector>`.

    Response
        A property of some real object or event which value is target to be predicted in the
        :term:`supervised learning` task. While the :term:`feature` is an input in the machine learning task,
        the response is one of the outputs can be made by the :term:`model` on the :term:`inference` stage.

        Synonyms: dependent variable.

    Supervised learning
        :term:`Training` process with a :term:`dataset` containing information on dependencies
        between :term:`features<Feature>` and :term:`responses<Response>`.
        The goal is to get a :term:`model` of dependencies between input :term:`feature vector`
        and :term:`responses<Response>`.

    Training
        A process of creating a :term:`model` based on information extracted from a :term:`training set`.
        Resulting :term:`model` is selected in accordance with some quality criteria.

    Training set
        A :term:`dataset` used at the :term:`training` stage to create a :term:`model`.

    Unsupervised learning
        :term:`Training` process where :term:`training set` does not contain information
        on dependencies between :term:`feature vectors<Feature vector>` and :term:`responses<Response>`.
        The goal is to get a :term:`model` matching :term:`feature vectors<Feature vector>` into groups.

|dal_short_name| terms
======================

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
        A copy-constructible and copy-assignable |dal_short_name| object
        which stores the number of references to the unique implementation.
        Has lightweight copy operations which increases the number of references.
        An implementation is automatically freed when the number of references becomes equal to zero.

    Workload
        A task of applying a |dal_short_name| algorithm to a dataset.

Common oneAPI terms
===================

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



