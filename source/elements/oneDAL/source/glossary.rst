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

        **Examples:** prediction of the object on the picture (dog or cat?),
        prediction of the email type (spam or not?)

    Clustering
        An :term:`unsupervised machine learning problem <Unsupervised learning>`
        of grouping :term:`feature vectors <Feature vector>` into groups,
        usually :term:`categorical <Categorical feature>`,
        without prior information about them.

        **Example:** A problem of marking big star clusters at the space images

    Continuous feature
        A :term:`feature` with values in a domain of real numbers. Can be
        :term:`interval <Interval feature>` or :term:`ratio <Ratio feature>`

        **Synonyms:** quantitative feature, numerical feature

        **Examples:** a person's height, the price on the house

    Dataset
        A collection of :term:`observations <Observation>`.

    Feature
        A particular property or quality of a real object or an event. Has a
        defined type and domain. In machine learning problems, features are
        considered as input variable that are independent from each other.

        **Synonyms:** attribute, variable, input variable

    Feature vector
        A vector that encodes information about a single real object or an event.
        Contains at least one :term:`feature`.

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
        values for each input feature and single bias value

    Observation
        A :term:`feature vector` and zero or more :term:`responses<Response>`.
        Each of them can encode different objects or events.

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

        **Example:** prediction of the temperature based on weather conditions

    Response
        A property of some real object or event which value is target to be
        predicted in the :term:`supervised learning` problem. While the
        :term:`feature` is an input in the machine learning problem, the
        response is one of the outputs can be made by the :term:`model` on the
        :term:`inference` stage.

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
        :term:`Training` process where :term:`training set` does not contain
        information on dependencies between :term:`feature vectors<Feature
        vector>` and :term:`responses<Response>`. The goal is to get a
        :term:`model` matching :term:`feature vectors<Feature vector>` into
        groups.

|dal_short_name| terms
======================

.. glossary::
    :sorted:

    Accessor
        A |dal_short_name| concept of an object that provides access to the data
        of another object in the special :term:`data format` .

    Batch Mode
        The computation mode for an algorithm in |dal_short_name|, where all the
        data needed for computation is available at the start and fits the
        memory of the device on which the computations are performed.

    Builder
        A |dal_short_name| concept of an object that encapsulates the creation
        process of another object and enables its iterative creation.

    Contiguous data
        A special property of the :term:`data format`: the data are stored as
        one contiguous memory block.

    Data format
        Representation of the internal structure of the data.

        **Examples:** data can be stored in array-of-structures or
        compressed-sparse-row format

    Data layout
        A property :term:`data format` of :term:`contiguous data`. Describes an
        order of elements inside contiguous data block.

        **Example:** row-major format, where elements are stored row by row

    Data type
        An integral or a floating-point type used to physically store the
        data.

        **Examples:** int32_t, float, double

    Heterogeneous data
        A property of the :term:`data format`, where :term:`features<Feature>`
        have different :term:`data types<Data type>` and/or operations defined
        between values.

        **Example:** A :term:`dataset` with 100
        :term:`observations<Observation>` of 3 :term:`interval features<Interval
        feature>`. The first two features have data type of float32, but the
        third one of float64

    Homogeneous data
        A special property of the :term:`data format`: all the types of the
        :term:`features<Feature>` are the same. This means that they have
        similar :term:`data type` and defined set of available operations.

        **Example:** A :term:`dataset` with 100
        :term:`observations<Observation>` of 3 :term:`interval features<Interval
        feature>` of type float32

    Immutability
        The object is immutable if it is not possible to change its state after
        creation.

    Online Mode
        The computation mode for an algorithm in |dal_short_name|, where the
        data needed for computation becomes available in parts over time.

    Reference-counted object
        A copy-constructible and copy-assignable |dal_short_name| object which
        stores the number of references to the unique implementation. Has
        lightweight copy operations which increases the number of references.
        An implementation is automatically freed when the number of references
        becomes equal to zero.

    Table
        A |dal_short_name| concept of a :term:`dataset` that contains only
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


