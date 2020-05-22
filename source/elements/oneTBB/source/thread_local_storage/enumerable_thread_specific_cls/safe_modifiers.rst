===========================
Concurrently safe modifiers
===========================

All member functions in this section can be performed concurrently with each other.

.. cpp:function:: reference local()

    If there is no current element corresponding to the current thread, then this method constructs a new element.
    A new element is copy-constructed if an exemplar was provided to the constructor for
    ``*this``, otherwise a new element is default constructed.

    **Returns**: A reference to the element of ``*this`` that corresponds to the current thread.

.. cpp:function:: reference local( bool& exists )

    Similar to ``local()``, except that ``exists`` is set to true if an element
    was already present for the current thread; false otherwise.

    **Returns**: Reference to thread-local element.

