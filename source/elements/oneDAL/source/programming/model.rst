Programming Model
=========================

Basic Usage Scenario
~~~~~~~~~~~~~~~~~~~~~

Below you can find a typical workflow of using |dal_short_name| algorithm on GPU.
The example is provided for Principal Component Analysis algorithm (PCA).

The following steps depict how to:

- Pass the data
- Initialize the algorithm
- Request statistics to be calculated (means, variances, eigenvalues)
- Compute results
- Get calculated eigenvalues and eigenvectors

#. Include the following header file to enable the DPC++ interface for
   |dal_short_name|:

   .. substitution-code-block::

      #include "|daal_in_code|_sycl.h"

#. Create a DPC++ queue with the desired device selector. In this case,
   GPU selector is used:

   .. parsed-literal::

      cl::sycl::queue queue { cl::sycl::gpu_selector() };

#. Create an execution context from the DPC++ queue and set up as the
   default for all algorithms. The execution context is the |dal_short_name|
   concept that is intended for delivering queue and device information
   to the algorithm kernel:

   .. parsed-literal::

      |dal_namespace|::services::Environment::getInstance()->setDefaultExecutionContext(
            |dal_namespace|::services::SyclExecutionContext(queue) );

#. Create a DPC++ buffer from the data allocated on host:

   .. parsed-literal::

      constexpr size_t nRows = 10;
      constexpr size_t nCols = 5;
      const float dataHost[] = {
             0.42, -0.88,  0.46,  0.04, -0.86,
            -0.74, -0.59,  0.42, -1.44, -0.40,
            -1.45,  1.07, -1.00, -0.29,  0.35,
            -0.67,  0.20,  0.47, -1.07,  0.71,
            -1.19,  0.20,  0.84, -0.26,  1.47,
            -1.87, -0.94, -1.16, -0.64, -2.10,
            -0.65, -0.40, -1.88, -0.48,  0.70,
            -0.52, -0.34, -1.48, -0.63, -0.87,
            -0.74, -0.46,  1.07,  0.65, -1.68,
             0.94,  1.88, -0.73, -1.16,  0.10
      };
      auto dataBuffer = cl::sycl::buffer<float, 1>(dataHost, nCols * nRows);

#. Create a DPC++ numeric table from a DPC++ buffer. DPC++ numeric table is a new concept
   introduced as a part of DPC++ interfaces to work with data stored in DPC++ buffer.
   It implements an interface of a classical numeric table acting as an adapter between DPC++
   and |dal_short_name| APIs for data representation.

   .. parsed-literal::

      auto data = |dal_namespace|::data_management::SyclHomogenNumericTable<float>::create(
            dataBuffer, nCols, nRows);


#. Create an algorithm object, configure its parameters, set up input
   data, and run the computations.

   .. parsed-literal::

      |dal_namespace|::algorithms::pca::Batch<float> pca;

      pca.parameter.nComponents = 3;
      pca.parameter.resultsToCompute = |dal_namespace|::algorithms::pca::mean |
      |dal_namespace|::algorithms::pca::variance |
      |dal_namespace|::algorithms::pca::eigenvalue;
      pca.input.set(|dal_namespace|::algorithms::pca::data, data);

      pca.compute();

#. Get the algorithm result:

   .. parsed-literal::

      auto result = pca.getResult();
      NumericTablePtr eigenvalues = result->get(|dal_namespace|::algorithms::pca::eigenvalues);
      NumericTablePtr eigenvectors = result->get(|dal_namespace|::algorithms::pca::eigenvectors);

#. Get the raw data as DPC++ buffer from the resulting numeric tables:

   .. parsed-literal::

      const size_t startRowIndex = 0;
      const size_t numberOfRows = eigenvectors->getNumberOfRows();

      BlockDescriptor<float> block;
      eigenvectors->getBlockOfRows(startRowIndex, numberOfRows, readOnly, block);

      cl::sycl::buffer<float, 1> buffer = block.getBuffer().toSycl();

      eigenvectors->releaseBlockOfRows(block);

At the end of the stage, the resulting numeric tables can be used as an input for another algorithm,
or the buffer can be passed to the user-defined kernel.

