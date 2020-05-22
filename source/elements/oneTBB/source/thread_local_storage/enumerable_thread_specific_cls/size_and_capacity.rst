=================
Size and capacity
=================

.. cpp:function:: size_type size() const

    Returns the number of elements in ``*this``.
    The value is equal to the number of distinct threads that have called ``local()`` after
    ``*this`` was constructed or most recently cleared.

.. cpp:function:: bool empty() const

    Returns ``true`` if the container is empty, ``false`` otherwise.

