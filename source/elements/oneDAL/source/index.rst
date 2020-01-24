..
  Copyright 2019 Intel Corporation

.. _oneDAL-section:

========================
|dal_full_name| (oneDAL)
========================

oneAPI Data Analytics Library (oneDAL) is a library of building blocks covering all
stages of data analytics: data acquisition from a data source, preprocessing,
transformation, data mining, modeling, validation, and decision-making.

The library consists of the following components:

- Data Management provides interfaces for data acquisition, initial
  preprocessing, data and model representation.
- Algorithms provide interfaces for data analysis and data modeling,
  and support batch, online and distributed computation modes.
- Services include interfaces used across the library by Data
  Management and Algorithms components: memory allocation, error
  handling and interaction with underlying hardware. The programmer
  can provide a queue specify the target device for algorithm
  execution.

.. Much of oneDAL is defined only for the host processor.  The features are
.. enabled to run on oneAPI devices.

.. 1. **Data Management**: DPC++ numeric table
.. 2. **Algorithms**: K-means, Covariance, Principal Component Analysis,
..    Stochastic Gradient Descent, and Logistic Regression
.. 3. **Services**: DPC++ execution context


.. code:: cpp

  #include "daal_sycl.h"

  // Common oneDAL namespaces
  using namespace daal::services;
  using namespace daal::algorithms;
  using namespace daal::data_management;

  int main(int argc, char *argv[]) {
    // Create a DPC++ queue with the desired device selector
    cl::sycl::queue queue{cl::sycl::gpu_selector()};

    // Create an execution context from the DPC++ queue and set up as the
    // default for all algorithms
    Environment::getInstance()->
      setDefaultExecutionContext(SyclExecutionContext{queue});

    // Create a DPC++ buffer from the data allocated on host
    const size_t nRows = 10;
    const size_t nCols = 5;
    const float dataHost[] = {
      0.42, -0.88,  0.46,  0.04, -0.86,
      -0.74, -0.59,  0.42, -1.44, -0.40,
      ...
    };
    cl::sycl::buffer<float, 1> dataBuffer{dataHost, nCols * nRows);

    // Create a DPC++ numeric table from the DPC++ buffer
    auto data = SyclHomogenNumericTable<float>::create(dataBuffer, nCols, nRows);

    // Create an algorithm object, for instance, a PCA algorithm
    pca::Batch<float> pca;

    // Set up PCA parameters
    pca.parameter.nComponents = 3;
    pca.parameter.resultsToCompute = pca::mean |
                                     pca::variance |
                                     pca::eigenvalue;
    // Set up input data
    pca.input.set(pca::data, data);

    // Run the computations
    pca.compute();

    // Get the algorithm result
    pca::ResultPtr result = pca.getResult();
    NumericTablePtr eigenvalues = result->get(pca::eigenvalues);
    NumericTablePtr eigenvectors = result->get(pca::eigenvectors);

    // Define a block descriptor for accessing numeric table
    BlockDescriptor<float> block;

    // Read block from the numeric table into the block descriptor
    const size_t startRowIndex = 0;
    const size_t numberOfRows = eigenvectors->getNumberOfRows();
    eigenvectors->getBlockOfRows(startRowIndex, numberOfRows, readOnly, block);

    // Get the raw data as DPC++ buffer from the numeric table
    cl::sycl::buffer<float, 1> eigenvectorsBuffer = block.getBuffer().toSycl();

    // Release resources associated with the block descriptor
    eigenvectors->releaseBlockOfRows(block);
  }


--------------------------
Open Source Implementation
--------------------------

An `open source implementation`_ is available under an Apache
license.

-------
Testing
-------

Intel's binary distribution of oneDAL contains example code that can
be used to test library functionality.

The `open source implementation`_ includes a comprehensive test suite.
Consult the `README`_ for directions.

-------------------------
Detailed API Descriptions
-------------------------

The detailed specification for oneDAL is available `online`_.


.. _`open source implementation`: https://github.com/intel/daal
.. _`README`: https://github.com/intel/daal/blob/master/README.md
.. _`online`: ../../../oneDAL/index.html

