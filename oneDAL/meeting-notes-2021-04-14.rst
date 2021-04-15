************************
Meeting notes 2021-04-14
************************

Opens
-----

Specification versioning is being discussed at the libraries workgroup
(performance libraries, oneTBB, PSTL, oneCCL). The current proposal is to have a
common version for the whole oneAPI spec and align its number with the
year. Along with it, every oneAPI component shall have its own independent spec
version. All the component specifications will be aggregated in the oneAPI spec
under this common spec version.

Agenda
------

- Usage of "response" terminology as a common one for the ML task types (clustering,
  classification, regression) instead of "label" terminology.

- Further steps on updating the specification.

Response vs label terminology
-----------------------------

**The presentation**: proposal_

.. _proposal: proposals/2021-04-14/api_extension_adding_responses.pptx

Q: At the library level, we decided to use "response" terminology in API instead
of "label". This affects the specification of KMeans and KNN algorithms. Why do
we think that response is common terminology for all ML task types?

A: We are aligned with our glossary that defines the "response" as a common
terminology for all ML tasks.

Q: Does the literature use response as terminology for classification tasks?

A: Yes, for example, "The Elements of Statistical Learning" (Trevor Hastie,
Robert Tibshirani, Jerome Friedman) use this as a common definition too (see
chapter 2.1, Introduction). This book also does not use "label" terminology
so often, it uses "class labels" instead for the classification tasks.

Q: How good is to use "response" for clustering task?

A: We see several benefits to use "response" for clustering:

- Consistency across the library with other task types. We can write universal
  code that does not depend on the task type if we use the same terminology for
  all task types.

- "Response" is widely used for regression and classification

- Using "response" is better than "cluster" for some clustering algorithms like
  DBSCAN, where some points do not specify a cluster.

- "Response" is good to be used as a result of inference tasks even for
  clustering algorithms.

**Decision**:

1. Use "response" terminology as a common one for all ML task types.

2. Adjust the glossary to point that "response" is generic terminology for all
   types of tasks.

3. Change the specs of Kmeans and KNN to use response in APIs, deprecate the
   methods that use "label".

Further steps on updating the specification
-------------------------------------------

Q: What is the plan to apply these deprecations and changes accepted earlier?

A: The first step is to approve the changes at "Developer software engineering
review forum". We will put all the changes we are proposing in one bunch for
that. The next step is to change APIs and specification.

Q: What is our plan on the convergence between the code and specification?

A: We are fixing doxygen sources in the library now. The next step is to update
the spec with these doxygen comments from the library code. We plan to update
the spec for the release of oneAPI spec revision 2.
