======
Lookup
======

The following table provides information on the members of the
``concurrent_map`` and ``concurrent_multimap``
template classes.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``iterator find(const key_type& k)``
  \
  Finds an element in the table.
  
  **Returns**: ``iterator`` pointing to the element with the key equivalent
  to ``k``, or ``end()`` if no such element exists.
------------------------------------------------------------------------------------------
\ ``const_iterator find(const key_type& k)``
  \
  Finds an element in the table.
  
  **Returns**: ``const_iterator`` pointing to the element with the key
  equivalent to ``k`` or ``end()`` if no such element exists.
------------------------------------------------------------------------------------------
\ ``template<typename K> iterator find(const K& k)``
  \
  Finds an element in the table with the key that compares ``equivalent``
  to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
  
  **Returns**: ``iterator`` pointing on the found element or ``end()``
  if no such element exists.
------------------------------------------------------------------------------------------
\ ``template<typename K> const_iterator find(const K& k) const``
  \
  Finds an element in the table with the key that compares ``equivalent``
  to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
  
  **Returns**: ``const_iterator`` pointing on the found element or ``end()``
  if no such element exists.
------------------------------------------------------------------------------------------
\ ``bool contains(const key_type& k) const``
  \
  Checks if there is an element in the table with the key, equivalent to ``k``.
  
  **Returns**: ``true`` if the element exists, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``template<typename K> bool contains(const K& k) const``
  \
  Checks if there is an element in the table with the key, that compares ``equivalent``
  to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
  
  **Returns**: ``true`` if the element exists, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``size_type count(const key_type& k) const``
  \
  **Returns**: the number of elements with the key equivalent to ``k``.
------------------------------------------------------------------------------------------
\ ``template<typename K> size_type count(const K& k) const``
  \
  **Returns**: the number of elements with the key, that compares ``equivalent``
  to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
------------------------------------------------------------------------------------------
\ ``std::pair<iterator, iterator> equal_range(const key_type& k)``
  \
  **Returns**: a range, containing all elements in the table with the key, equivalent to ``k``.
------------------------------------------------------------------------------------------
\ ``std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const``
  \
  **Returns**: a range, containing all elements in the table with the key, equivalent to ``k``.
------------------------------------------------------------------------------------------
\ ``template<typename K> std::pair<iterator, iterator> equal_range(const K& k)``
  \
  **Returns**: a range, containing all elements in the table with the key,
  that compares ``equivalent`` to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
------------------------------------------------------------------------------------------
\ ``template<typename K> std::pair<const_iterator, const_iterator> equal_range(const K& k) const``
  \
  **Returns**: a range, containing all elements in the table with the key,
  that compares ``equivalent`` to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
------------------------------------------------------------------------------------------
\ ``iterator lower_bound(const key_type& k)``
  \
  **Returns**: an iterator pointing on the first element in the table with the key,
  that is not less than ``k``.
------------------------------------------------------------------------------------------
\ ``const_iterator lower_bound(const key_type& k) const``
  \
  **Returns**: ``const_iterator`` pointing on the first element in the table that is
  not less than ``k``.
------------------------------------------------------------------------------------------
\ ``template<typename K> iterator lower_bound(const K& k)``
  \
  **Returns**: an iterator pointing on the first element in the table with the key that is
  *not less* than the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
------------------------------------------------------------------------------------------
\ ``template<typename K> const_iterator lower_bound(const K& k) const``
  \
  **Returns**: ``const_iterator`` pointing on the first element in the table
  with the key, that is *not less* than the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
------------------------------------------------------------------------------------------
\ ``iterator upper_bound(const key_type& k)``
  \
  **Returns**: an iterator pointing on the first element in the table with the key that is
  greater than ``k``.
------------------------------------------------------------------------------------------
\ ``const_iterator upper_bound(const key_type& k) const``
  \
  **Returns**: ``const_iterator`` pointing on the first element in the table
  with the key that is greater than ``k``.
------------------------------------------------------------------------------------------
\ ``template<typename K> iterator upper_bound(const K& k)``
  \
  **Returns**: an iterator pointing on the first element in the table with the key that is
  *greater* than the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
------------------------------------------------------------------------------------------
\ ``template<typename K> const_iterator upper_bound(const K& k) const``
  \
  **Returns**: ``const_iterator`` pointing on the first element in the table
  with the key that is *greater* than the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of ``key_type``.
------------------------------------------------------------------------------------------
= ========================================================================================

The following table provides additional information on the
``concurrent_map`` template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``mapped_type& operator[](const key_type& k)``
  \
  Inserts the new item ``value_type(k, mapped_type())`` if the key ``k``
  does not exists in the table.
  
  **Returns**: reference to ``val.second``, where ``val``
  is an item in the table with the key equivalent to ``k``.
------------------------------------------------------------------------------------------
\ ``mapped_type& operator[](key_type&& k)``
  \
  Emplaces the new item ``value_type(std::piecewise_construct, std::forward_as_tuple(key), std::tuple<>())``
  if the key ``k`` does not exists in the table.
  
  **Returns**: reference to ``val.second``, where ``val``
  is an item in the table with the key equivalent to ``k``.
------------------------------------------------------------------------------------------
\ ``mapped_type& at(const key_type& k)``
  \
  Throws an exception if an element with the key equivalent to ``k`` does not exists in the table.
  
  **Returns**: reference to ``val.second``, where ``val``
  is an item in the table with the key equivalent to ``k``.
------------------------------------------------------------------------------------------
\ ``const mapped_type& at(const key_type& k) const``
  \
  Throws an exception if an element with the key equivalent to ``k`` does not exists in the table.
  
  **Returns**: reference to ``val.second``, where ``val``
  is an item in the table with the key equivalent to ``k``.
------------------------------------------------------------------------------------------
= ========================================================================================
