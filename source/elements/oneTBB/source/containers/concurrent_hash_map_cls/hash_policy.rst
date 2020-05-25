===========
Hash policy
===========

Rehashing
---------

    .. code:: cpp

        void rehash( size_type n = 0 );

    If ``n > 0`` sets the number of buckets to the value which is not less than ``n``.

bucket_count
------------

    .. code:: cpp

        size_type bucket_count() const;

    **Returns**: the number of buckets in the container.
