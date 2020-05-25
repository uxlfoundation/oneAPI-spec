=========
Combining
=========

The member functions in this section iterate across the entire container sequentially in the calling thread.

.. cpp:function:: template<typename BinaryFunc> T combine(BinaryFunc f)

    **Requires**: A ``BinaryFunc`` shall meet the `Function Objects` requirements from [function.objects] ISO C++ Standard section.
    Specifically, the type should be an associative binary functor with the signature ``T BinaryFunc(T,T)`` or ``T BinaryFunc(const T&,const T&)``.
    A ``T`` type must be the same as a corresponding template parameter for ``enumerable_thread_specific`` object.

    **Effects**: Computes reduction over all elements using binary functor ``f``.
    If there are no elements, creates the result using the same rules as for creating a thread-local element.

    **Returns**: Result of the reduction.

.. cpp:function:: template<typename UnaryFunc> void combine_each(UnaryFunc f)

    **Requires**: An ``UnaryFunc`` shall meet the `Function Objects` requirements from [function.objects] ISO C++ Standard section.
    Specifically, the type should be an unary functor with the signature ``void UnaryFunc(T)`` or ``void UnaryFunc(T&)`` or ``void UnaryFunc(const T&)``
    A ``T`` type must be the same as a corresponding template parameter for ``enumerable_thread_specific`` object.

    **Effects**: Evaluates ``f(x)`` for each instance ``x`` of ``T`` in ``*this``.

