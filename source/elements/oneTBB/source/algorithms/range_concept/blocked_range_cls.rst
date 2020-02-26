============================
blocked_range Template Class
============================


Summary
-------

Template class for a recursively divisible half-open interval.

Header
------


.. code:: cpp

   #include "tbb/blocked_range.h"


Syntax
------

.. code:: cpp

   template<typename Value> class blocked_range;


Description
-----------

A
``blocked_range<Value>`` represents a half-open
range [*i*,*j*) that can be recursively split. The types of
*i* and
*j* must model the requirements in the following table. In the
table, type
``D`` is the type of the expression
``"j-i"``. It can be any integral type that is convertible
to
``size_t``. Examples that model the Value requirements are
integral types, pointers, and STL random-access iterators whose difference can
be implicitly converted to a
``size_t``.

A
``blocked_range`` models the Range concept.

= ========================================================================================
\ Value Concept for blocked_range: Pseudo-Signature, Semantics
==========================================================================================
\ ``Value::Value( const Value& )``
  \
  Copy constructor.
------------------------------------------------------------------------------------------
\ ``Value::~Value()``
  \
  Destructor.
------------------------------------------------------------------------------------------
\ ``void operator=( const Value& )``
  \
    .. note::

     The return type
     ``void`` in the pseudo-signature denotes that
     ``operator=`` is not required to return a
     value. The actual
     ``operator=`` can return a value, which will
     be ignored by
     ``blocked_range`` .
  
  Assignment.
------------------------------------------------------------------------------------------
\ ``bool operator<( const Value& i, const Value& j )``
  \
  Value
  *i* precedes value *j*.
------------------------------------------------------------------------------------------
\ ``D operator-( const Value& i, const Value& j )``
  \
  Number of values in range
  ``[i,j)``.
------------------------------------------------------------------------------------------
\ ``Value operator+( const Value& i, D k )``
  \
  *k*th value after
  *i*.
------------------------------------------------------------------------------------------
= ========================================================================================

A
``blocked_range<Value>`` specifies a
*grain size* of type
``size_t``. A
``blocked_range`` is splittable into two subranges if the
size of the range exceeds
its grain size. The ideal grain size depends upon the context of the
``blocked_range<Value>``, which is typically as the
range argument to the loop templates
``parallel_for``,
``parallel_reduce``, or
``parallel_scan``. A too small grain size may cause
scheduling overhead within the loop templates to swamp speedup gained from
parallelism. A too large grain size may unnecessarily limit parallelism. For
example, if the grain size is so large that the range can be split only once,
then the maximum possible parallelism is two.

Here is a suggested procedure for choosing a reasonable grain size:

* Set the ``grainsize`` parameter to 10,000. This
  value is high enough to amortize scheduler overhead sufficiently for
  practically all loop bodies, but may unnecessarily limit parallelism.
* Run your algorithm on
  *one* processor.
* Start halving the ``grainsize`` parameter and see
  how much the algorithm slows down as the value decreases.

A slowdown of about 5-10% is a good setting for
most purposes.

.. tip::

   For a
   ``blocked_range [i,j)`` where ``j<i``,
   not all methods have specified behavior. However, enough methods do have
   specified behavior that
   ``parallel_for``,
   ``parallel_reduce``, and
   ``parallel_scan`` iterate over the same iteration space
   as the serial loop
   ``for( Value index=i; index<j; ++index )...``, even
   when
   ``j<i``. If
   ``TBB_USE_ASSERT`` is nonzero, methods with unspecified
   behavior raise an assertion failure.

**Example**

A
``blocked_range<Value>`` typically appears as a
range argument to a loop template. See the examples for
``parallel_for``, ``parallel_reduce``, and
``parallel_scan``.

Members
-------

.. code:: cpp

   namespace tbb {
       template<typename Value>
       class blocked_range {
       public:
           // types
           typedef size_t size_type;
           typedef Value const_iterator;
   
           // constructors
           blocked_range( Value begin, Value end,
                          size_type grainsize=1 );
           blocked_range( blocked_range& r, split );
           blocked_range( blocked_range& r, proportional_split& proportion );
   
           // Proportional split is enabled
           static const bool is_splittable_in_proportion = true;
   
           // capacity
           size_type size() const;
           bool empty() const;
   
           // access
           size_type grainsize() const;
           bool is_divisible() const;
   
           // iterators
           const_iterator begin() const;
           const_iterator end() const;
       };
   }
         

Constructors of ``blocked_range`` support class template argument deduction for C++17. For example

.. code:: cpp

   tbb::blocked_range range(0, 100);

declares ``range`` as ``tbb::blocked_range<int>``.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``size_type``
  \
  The type for measuring the size of a
  ``blocked_range``. The type is always a
  ``size_t``.
------------------------------------------------------------------------------------------
\ ``const_iterator``
  \
  The type of a value in the range. Despite
  its name, the type
  ``const_iterator`` is not necessarily an STL
  iterator; it merely needs to meet the Value requirements in the table above.
  However, it is convenient to call it
  ``const_iterator`` so that if it is a
  const_iterator, then the ``blocked_range`` behaves like a
  read-only STL container.
------------------------------------------------------------------------------------------
\ ``blocked_range( Value begin, Value end, size_t grainsize=1 )``
  \
  **Requirements**: The parameter
  ``grainsize`` must be positive. The debug
  version of the library raises an assertion failure if this requirement is not
  met.
  
  **Effects**: Constructs a
  ``blocked_range`` representing the half-open
  interval
  ``[begin, end)`` with the given
  ``grainsize``.
  
  **Example**: The statement
  ``"blocked_range<int> r(5, 14, 2);"``
  constructs a range of
  ``int`` that contains the values 5 through 13
  inclusive, with the grain size of 2. Afterwards,
  ``r.begin()==5`` and
  ``r.end()==14``.
------------------------------------------------------------------------------------------
\ ``blocked_range( blocked_range& range, split )``
  \
  Basic splitting constructor.
  
  **Requirements**:
  ``is_divisible()`` is true.
  
  **Effects**: Partitions
  ``range`` into two subranges. The newly
  constructed
  ``blocked_range`` is approximately the second
  half of the original
  ``range``, and
  ``range`` is updated to be the remainder. Each
  subrange has the same
  ``grainsize`` as the original range.
  
  **Example**: Let ``r`` be a
  ``blocked_range`` that represents a
  half-open interval ``[i, j)`` with a grain
  size ``g``. Running the statement
  ``blocked_range<int> s(r, split);``
  subsequently causes r to represent ``[i, i+(j-i)/2)`` and ``s`` to represent
  ``[i+(j-i)/2, j)``, both with grain size
  ``g``.
------------------------------------------------------------------------------------------
\ ``blocked_range( blocked_range& range, proportional_split proportion )``
  \
  Proportional splitting constructor.
  
  **Requirements**: ``is_divisible()`` is true.
  
  **Effects**: Partitions ``range`` into two subranges such that the ratio of their sizes is
  close to the ratio of ``proportion.left()`` to ``proportion.right()``. The newly
  constructed ``blocked_range`` is the subrange at the right, and ``range`` is
  updated to be the subrange at the left.
  
  **Example**: Let ``r`` be a ``blocked_range`` that represents a half-open
  interval ``[i, j)`` with a grain size ``g``. Running the statement
  ``blocked_range<int> s(r, proportional_split(2, 3));`` subsequently causes
  ``r`` to represent ``[i, i+2*(j-i)/(2+3))`` and ``s`` to represent
  ``[i+2*(j-i)/(2+3), j)``, both with grain size ``g``.
------------------------------------------------------------------------------------------
\ ``static const bool is_splittable_in_proportion``
  \
  Special field denotes the ability of
  ``blocked_range`` instances to be split
  proportionally. Set to
  ``true``.
------------------------------------------------------------------------------------------
\ ``size_type size() const``
  \
  **Requirements**: ``end()<begin()`` is false.
  
  **Effects**: Determines size of range.
  
  **Returns**: ``end()-begin()``.
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Effects**: Determines if range is empty.
  
  **Returns**:
  ``!(begin()<end())``
------------------------------------------------------------------------------------------
\ ``size_type grainsize() const``
  \
  **Returns**: Grain size of range.
------------------------------------------------------------------------------------------
\ ``bool is_divisible() const``
  \
  **Requirements**:
  ``!(end()<begin())``
  
  **Effects**: Determines if range can be split into
  subranges.
  
  **Returns**: True if
  ``size()>grainsize();`` false otherwise.
------------------------------------------------------------------------------------------
\ ``const_iterator begin() const``
  \
  **Returns**: Inclusive lower bound on range.
------------------------------------------------------------------------------------------
\ ``const_iterator end() const``
  \
  **Returns**: Exclusive upper bound on range.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`parallel_for Template Function <../parallel_for_func>`
* :doc:`parallel_reduce Template Function <../parallel_reduce_func>`
* :doc:`parallel_scan Template Function <../parallel_scan_func>`
