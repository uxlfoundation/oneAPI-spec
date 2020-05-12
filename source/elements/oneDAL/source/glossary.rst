.. _glossary:

=========
Glossary
=========

Machine learning terms
======================

.. glossary::
    :sorted:

    Attribute
        A particular property or quality of a real object or an event.
        Has a defined type and domain.

    Classification
        A supervised machine-learning problem to assign categorical :term:`labels<Label>`
        to :term:`feature vectors<Feature vector>` describing input objects.

    Dataset
        A collection of :term:`instances<Instance>`.

    Feature
        A pair of :term:`attribute` information and a corresponding value.

    Feature vector
        A vector that encodes information about single real object or an event.
        Contains at least one :term:`feature`.

    Inference
        A process of obtaining outputs from the :term:`model` created on the :term:`training` stage

    Instance
        A vector of at least one :term:`feature` value and zero or more :term:`label<Label>` values.
        Each of :term:`labels<Label>` and :term:`features<Feature>` can encode different objects or events.

    Label
        :term:`Feature` of some object or event which is present on the :term:`training` stage but
        unavaliable on the :term:`inference` stage.

    Model
        A result of :term:`training` machine-learning algorithm that stores information necessary to run
        :term:`inference` on a new :term:`dataset`.

    Observation
        A synonym for :term:`instance`.

    Prediction
        - A synonym for :term:`inference`.
        - An output of the :term:`trained<Training>` :term:`model` when provided with an input :term:`instance`.

    Response
        A value of a single :term:`label`. For example, response may be a flag
        indicating that an observation belongs to a particular class.

    Sample
        A synonym for :term:`instance`.

    Training
        A search process of the best parameter values of the :term:`model`.

    Variable
        A synonym for an :term:`attribute`.

|dal_short_name| library terms
==============================

.. glossary::
    :sorted:

    Batch Mode
        The computation mode for an algorithm in |dal_short_name|, where all the data needed for
        computation is available at the start and fits the memory of the device on which the computations are performed.

    Immutability
        The object is immutable when it is not possible to change its state after it is constructed.

    Online Mode
        The computation mode for an algorithm in |dal_short_name|, where the data needed for computation
        becomes available in parts over time.

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



