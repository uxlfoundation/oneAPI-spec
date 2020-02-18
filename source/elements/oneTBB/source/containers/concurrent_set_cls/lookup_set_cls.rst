======
Lookup
======

The following table provides information on the members of the
``concurrent_set`` and ``concurrent_multiset``
template classes.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``iterator find(const key_type& k)``
  \
  Finds an element in the set.
  
  **Returns**: ``iterator`` pointing to the element equivalent
  to ``k``, or ``end()`` if no such element exists.
------------------------------------------------------------------------------------------
\ ``const_iterator find(const key_type& k)``
  \
  Finds an element in the set.
  
  **Returns**: ``const_iterator`` pointing to the element
  equivalent to ``k`` or ``end()`` if no such element exists.
------------------------------------------------------------------------------------------
\ ``template<typename K> iterator find(const K& k)``
  \
  Finds an element in the set that compares ``equivalent``
  to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
  
  **Returns**: ``iterator`` pointing on the found element or ``end()``
  if no such element exists.
------------------------------------------------------------------------------------------
\ ``template<typename K> const_iterator find(const K& k) const``
  \
  Finds an element in the set that compares ``equivalent``
  to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
  
  **Returns**: ``const_iterator`` pointing on the found element or ``end()``
  if no such element exists.
------------------------------------------------------------------------------------------
\ ``bool contains(const key_type& k) const``
  \
  Checks if there is an element in the set equivalent to ``k``.
  
  **Returns**: ``true`` if the element exists, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``template<typename K> bool contains(const K& k) const``
  \
  Checks if there is an element in the set, that compares ``equivalent``
  to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
  
  **Returns**: ``true`` if the element exists, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``size_type count(const key_type& k) const``
  \
  **Returns**: the number of elements in the set equivalent to ``k``.
------------------------------------------------------------------------------------------
\ ``template<typename K> size_type count(const K& k) const``
  \
  **Returns**: the number of elements in the set, that compares ``equivalent``
  to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
------------------------------------------------------------------------------------------
\ ``std::pair<iterator, iterator> equal_range(const key_type& k)``
  \
  **Returns**: a range, containing all elements in the set, equivalent to ``k``.
------------------------------------------------------------------------------------------
\ ``std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const``
  \
  **Returns**: a range, containing all elements in the set, equivalent to ``k``.
------------------------------------------------------------------------------------------
\ ``template<typename K> std::pair<iterator, iterator> equal_range(const K& k)``
  \
  **Returns**: a range, containing all elements in the set,
  that compares ``equivalent`` to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
------------------------------------------------------------------------------------------
\ ``template<typename K> std::pair<const_iterator, const_iterator> equal_range(const K& k) const``
  \
  **Returns**: a range, containing all elements in the set,
  that compares ``equivalent`` to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
------------------------------------------------------------------------------------------
\ ``iterator lower_bound(const key_type& k)``
  \
  **Returns**: an iterator pointing on the first element in the set
  that is not less than ``k``.
------------------------------------------------------------------------------------------
\ ``const_iterator lower_bound(const key_type& k) const``
  \
  **Returns**: ``const_iterator`` pointing on the first element in the set
  that is not less than ``k``.
------------------------------------------------------------------------------------------
\ ``template<typename K> iterator lower_bound(const K& k)``
  \
  **Returns**: an iterator pointing on the first element in the set that is
  *not less* than the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
------------------------------------------------------------------------------------------
\ ``template<typename K> const_iterator lower_bound(const K& k) const``
  \
  **Returns**: ``const_iterator`` pointing on the first element in the set that is
  *not less* than the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
------------------------------------------------------------------------------------------
\ ``iterator upper_bound(const key_type& k)``
  \
  **Returns**: an iterator pointing on the first element in the set that is
  greater than ``k``.
------------------------------------------------------------------------------------------
\ ``const_iterator upper_bound(const key_type& k) const``
  \
  **Returns**: ``const_iterator`` pointing on the first element in the set
  that is greater than ``k``.
------------------------------------------------------------------------------------------
\ ``template<typename K> iterator upper_bound(const K& k)``
  \
  **Returns**: an iterator pointing on the first element in the set that is
  *greater* than the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
------------------------------------------------------------------------------------------
\ ``template<typename K> const_iterator upper_bound(const K& k) const``
  \
  **Returns**: ``const_iterator`` pointing on the first element in the set
  that is *greater* than the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type. It means, that compare object allows execution without constructing
  an instance of``key_type``.
------------------------------------------------------------------------------------------
= ========================================================================================
