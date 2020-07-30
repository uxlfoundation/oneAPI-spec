=================
BlockedRangeValue
=================
**[req.blocked_range_value]**

A type `Value` satisfies `BlockedRangeValue` if it meets the following requirements:

------------------------------------------------------------------------------------------

**BlockedRangeValue Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Value::Value( const Value& )

    Copy constructor.

.. cpp:function:: Value::~Value()

    Destructor.

.. cpp:function:: void operator=( const Value& )

    .. note::

         The return type ``void`` in the pseudo-signature denotes that
         ``operator=`` is not required to return a value. The actual ``operator=``
         can return a value, which will be ignored by ``blocked_range`` .

    Assignment.

.. cpp:function:: bool operator<( const Value& i, const Value& j )

    Value *i* precedes value *j*.

.. cpp:function:: D operator-( const Value& i, const Value& j )

    Number of values in range ``[i,j)``.

.. cpp:function:: Value operator+( const Value& i, D k )

    *k*-th value after *i*.

``D`` is the type of the expression ``j-i``. It can be any integral type that is convertible to ``size_t``.
Examples that model the Value requirements are integral types, pointers, and STL random-access iterators
whose difference can be implicitly converted to a ``size_t``.

