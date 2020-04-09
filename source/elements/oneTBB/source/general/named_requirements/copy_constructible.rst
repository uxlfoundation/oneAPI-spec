=================
CopyConstructible
=================
**[general_information.named_requirements.copy_constructible]**

This page defines the *CopyConstructible* named requirement, which is defined by the ISO C++ standard.
The table below shows the requirements for *CopyConstructible* in pseudo-signature form.

---------------------------------------------------------------

**CopyConstructible Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: T( const T& )

  Construct copy of const T.

.. cpp:function:: ~T()

  Destructor.

.. cpp:function:: T* operator&()

  Take address.

.. cpp:function:: const T* operator&() const

  Take address of const T.
