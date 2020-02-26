================
Global Functions
================

These functions in namespace 
``tbb`` improve the STL compatibility of 
``concurrent_hash_map``.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``template<typename Key, typename T, typename HashCompare, typename A1, typename A2> bool operator==( const concurrent_hash_map<Key,T,HashCompare,A1>& a, const concurrent_hash_map<Key,T,HashCompare,A2>& b);``
  \
  **Returns**: True if``a``
  and 
  ``b`` contain equal sets of keys and for each
  pair ``(k,v1)∈``a and 
  ``(k,v2)∈b``, the expression ``bool(v1==v2)`` is true.
------------------------------------------------------------------------------------------
\ ``template<typename Key, typename T, typename HashCompare, typename A1, typename A2> bool operator!=(const concurrent_hash_map<Key,T,HashCompare,A1> &a, const concurrent_hash_map<Key,T,HashCompare,A2> &b);``
  \
  **Returns**: 
  ``!(a==b)``
------------------------------------------------------------------------------------------
\ ``template<typename Key, typename T, typename HashCompare, typename A> void swap(concurrent_hash_map<Key, T, HashCompare, A> &a, concurrent_hash_map<Key, T, HashCompare, A> &b)``
  \
  ``a.swap(b)``
------------------------------------------------------------------------------------------
= ========================================================================================
