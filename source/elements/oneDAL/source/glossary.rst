.. _glossary:

=========
Glossary
=========

Machine learning terms
======================

.. glossary::
    :sorted:

    Categorical feature
        A :term:`feature` with a discrete domain. Can be :term:`nominal <Nominal
        feature>` or :term:`ordinal <Ordinal feature>`.

        **Synonyms:** discrete feature, qualitative feature

    Nominal feature
        A :term:`categorical feature` without ordering between values. Only
        equality operation is defined for nominal features.

        **Examples:** a person's gender, color of a car

    Classification
        A :term:`supervised machine learning problem <Supervised learning>` of
        assigning :term:`labels <Label>` to :term:`feature vectors <Feature
        vector>`.

        **Examples:** predict what type of object is on the picture (a dog or a cat?),
        predict whether or not an email is spam

    Clustering
        An :term:`unsupervised machine learning problem <Unsupervised learning>`
        of grouping :term:`feature vectors <Feature vector>` into bunches, which
        are usually encoded as :term:`nominal <Nominal feature>` values.

        **Example:** find big star clusters in the space images

    Continuous feature
        A :term:`feature` with values in a domain of real numbers. Can be
        :term:`interval <Interval feature>` or :term:`ratio <Ratio feature>`

        **Synonyms:** quantitative feature, numerical feature

        **Examples:** a person's height, the price of the house

    Dataset
        A collection of :term:`observations <Observation>`.

    Feature
        A particular property or quality of a real object or an event. Has a
        defined type and domain. In machine learning problems, features are
        considered as input variable that are independent from each other.

        **Synonyms:** attribute, variable, input variable

    Feature vector
        A vector that encodes information about real object, an event or a group
        of objects or events. Contains at least one :term:`feature`.

        **Example:** A rectangle can be described by two features: its width and
        height

    Inference
        A process of applying a :term:`trained <Training>` :term:`model` to the
        :term:`dataset` in order to predict :term:`response`
        values based on input :term:`feature vectors <Feature vector>`.

        **Synonym:** prediction

    Inference set
        A :term:`dataset` used at the :term:`inference` stage.
        Usually without :term:`responses <Response>`.

    Interval feature
        A :term:`continuous feature` with values that can be compared, added or
        subtracted, but cannot be multiplied or divided.

        **Examples:** a timeframe scale, a temperature in Celcius or Fahrenheit

    Label
        A :term:`response` with :term:`categorical <Categorical feature>` or
        :term:`ordinal <Ordinal feature>` values. This is an output in
        :term:`classification` and :term:`clustering` problems.

        **Example:** the spam-detection problem has a binary label indicating
        whether the email is spam or not

    Model
        An entity that stores information necessary to run :term:`inference`
        on a new :term:`dataset`. Typically a result of a :term:`training`
        process.

        **Example:** in linear regression algorithm, the model contains weight
        values for each input feature and a single bias value

    Observation
        A :term:`feature vector` and zero or more :term:`responses<Response>`.

        **Synonyms:** instance, sample

    Ordinal feature
        A :term:`categorical feature` with defined operations of equality and
        ordering between values.

        **Example:** student's grade

    Ratio feature
        A :term:`continuous feature` with defined operations of equality,
        comparison, addition, subtraction, multiplication, and division.
        Zero value element means the absence of any value.

        **Example:** the height of a tower

    Regression
        A :term:`supervised machine learning problem <Supervised learning>` of
        assigning :term:`continuous <Continuous feature>`
        :term:`responses<Response>` for :term:`feature vectors <Feature vector>`.

        **Example:** predict temperature based on weather conditions

    Response
        A property of some real object or event which dependency from
        :term:`feature vector` need to be defined in :term:`supervised learning`
        problem. While a :term:`feature` is an input in the machine learning
        problem, the response is one of the outputs can be made by the
        :term:`model` on the :term:`inference` stage.

        **Synonym:** dependent variable

    Supervised learning
        :term:`Training` process that uses a :term:`dataset` with information
        about dependencies between :term:`features <Feature>` and
        :term:`responses <Response>`. The goal is to get a :term:`model` of
        dependencies between input :term:`feature vector` and
        :term:`responses <Response>`.

    Training
        A process of creating a :term:`model` based on information extracted
        from a :term:`training set`. Resulting :term:`model` is selected in
        accordance with some quality criteria.

    Training set
        A :term:`dataset` used at the :term:`training` stage to create a
        :term:`model`.

    Unsupervised learning
        :term:`Training` process that uses a :term:`training set` with no
        :term:`responses <Response>`. The goal is to find hidden patters inside
        :term:`feature vectors <Feature vector>` and dependencies between them.

|dal_short_name| terms
======================

.. glossary::
    :sorted:

    Accessor
        A |dal_short_name| concept for an object that provides access to the data
        of another object in the special :term:`data format` .

    Batch Mode
        The computation mode for an algorithm in |dal_short_name|, where all the
        data needed for computation is available at the start and fits the
        memory of the device on which the computations are performed.

    Builder
        A |dal_short_name| concept for an object that encapsulates the creation
        process of another object and enables its iterative creation.

    Contiguous data
        Data that are stored as one contiguous memory block. One of the
        characteristics of a :term:`data format`.

    Data format
        Representation of the internal structure of the data.

        **Examples:** data can be stored in array-of-structures or
        compressed-sparse-row format

    Data layout
        A characteristic of :term:`data format` which describes the
        order of elements in a :term:`contiguous data` block.

        **Example:** row-major format, where elements are stored row by row

    Data type
        An attribute of data used by a compiler to store and access them.
        Includes size in bytes, encoding principles, and available operations
        (in terms of a programming language).

        **Examples:** int32_t, float, double

    Heterogeneous data
        A property of the :term:`data format`, where :term:`features<Feature>`
        have different :term:`data types<Data type>` and/or operations defined
        between values.

        Data which contain values either of different :term:`data types <Data
        type>` or different sets of operations defined on them. One of the
        characteristics of a :term:`data format`.

        **Example:** A :term:`dataset` with 100
        :term:`observations <Observation>` of three :term:`interval features <Interval
        feature>`. The first two features are of float32 :term:`data type`, while the
        third one is of float64 data type.

    Homogeneous data
        Data with values of single :term:`data type` and the same set of
        available operations defined on them. One of the characteristics of a
        :term:`data format`.

        **Example:** A :term:`dataset` with 100
        :term:`observations <Observation>` of three  :term:`interval features <Interval
        feature>`, each of type float32

    Immutability
        The object is immutable if it is not possible to change its state after
        creation.

    Online Mode
        The computation mode for an algorithm in |dal_short_name|, where the
        data needed for computation becomes available in parts over time.

    Reference-counted object
        A copy-constructible and copy-assignable |dal_short_name| object which
        stores the number of references to the unique implementation. Both copy
        operations defined for this object are lightweight, which means that
        each time a new object is created, only the number of references is
        increased. An implementation is automatically freed when the number of
        references becomes equal to zero.

    Table
        A |dal_short_name| concept for a :term:`dataset` that contains only
        numerical data, :term:`categorical <Categorical feature>` or
        :term:`continuous <Continuous feature>`.

    Workload
        A problem of applying a |dal_short_name| algorithm to a :term:`dataset`.

Common oneAPI terms
===================

.. glossary::
    :sorted:

    API
        Application Programming Interface

    DPC++
        Data Parallel C++ (DPC++) is a high-level language designed for data
        parallel programming productivity. DPC++ is based on :term:`SYCL*
        <sycl>` from the Khronos* Group to support data parallelism and
        heterogeneous programming.

    Host/Device
        OpenCL [OpenCLSpec]_ refers to CPU that controls the connected GPU
        executing kernels.

    JIT
        Just in Time Compilation --- compilation during execution of a program.

    Kernel
        Code written in OpenCL [OpenCLSpec]_ or :term:`SYCL` and executed on a
        GPU device.

    SPIR-V
        Standard Portable Intermediate Representation - V is a language for
        intermediate representation of compute kernels.

    SYCL
        SYCL(TM) [SYCLSpec]_ --- high-level programming model for OpenCL(TM)
        that enables code for heterogeneous processors to be written in a
        "single-source" style using completely standard C++.
