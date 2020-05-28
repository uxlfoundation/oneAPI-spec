.. _onemkl_arch_other:

Other Features
----------------
This section covers all other features in the design of oneMKL architecture.



.. _onemkl_spec_versioning:

oneMKL Specification Versioning Strategy
+++++++++++++++++++++++++++++++++++++++++

This oneMKL specification uses a ``MAJOR.MINOR.PATCH`` approach for its versioning strategy.  
The ``MAJOR`` count is updated when a significant new feature or domain is added or backward compatibility is broken.  
The ``MINOR`` count is updated when new APIs are changed or added or deleted, or language updated with relatively significant change to the meaning but without breaking backwards compatibility.  
The ``PATCH`` count is updated when wording, language or structure is updated without significant change to the meaning or interpretation.


.. _onemkl_spec_current_version:

Current Version of this oneMKL Specification
+++++++++++++++++++++++++++++++++++++++++++++

This is the oneMKL specification version 0.8.0.


.. _onemkl_pre_post_conditions:

Pre/Post Condition Checking
+++++++++++++++++++++++++++++++++++++++

The individual oneMKL computational routines will define any preconditions and postconditions and will define in this specification any specific checks or verifications that should be enabled for all implementations.


