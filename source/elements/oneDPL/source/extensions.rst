
Specific API of oneDPL
----------------------

The oneDPL extensions include iterators, function objects, and parallel algorithms.

.. code:: cpp

  namespace dpstd {

  // Declared in <dpstd/iterators.h>

    template <typename Integral>
    class counting_iterator;

    template <typename... Iterators>
    class zip_iterator;
    template <typename... Iterators>
    zip_iterator<Iterators...>
    make_zip_iterator(Iterators...);

    template <typename UnaryFunc, typename Iterator>
    class transform_iterator;
    template <typename UnaryFunc, typename Iterator>
    transform_iterator<UnaryFunc, Iterator>
    make_transform_iterator(Iterator, UnaryFunc);


  // Declared in <dpstd/functional>

    struct identity;
  }

Parallel Algorithms
++++++++++++++++++++++

The parallel algorithms are defined in the header :code:`<dpstd/algorithm>`.  They are defined in
:code:`namespace dpstd` like the iterators and function object included in the extensions.

.. code:: cpp

    template<typename Policy, typename InputKeyIt, typename InputValueIt,
        typename OutputValueIt,
        typename T = typename std::iterator_traits<InputValueIt>::value_type,
        typename BinaryPred =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type>,
        typename BinaryOp =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first,
        InputKeyIt keys_last, InputValueIt values_first, OutputValueIt values_result,
        T initial_value = 0,
        BinaryPred binary_pred =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type>(),
        BinaryOp binary_op =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>());

:code:`dpstd::exclusive_scan_by_segment` performs partial prefix scans by applying the :code:`binary_op`
operation to a sequence of values. Each partial scan applies to a contiguous subsequence determined by
the keys associated with the values being equal according to the :code:`binary_pred` predicate,
and the first element of each scan is the initial value provided. The return value is an iterator
targeting the end of the result sequence.

The initial value used if one is not provided is an instance of the :code:`value_type` of the
:code:`InputValueIt` iterator type initialized to 0. If no binary predicate is provided for the
comparison of keys an instance of :code:`std::equal_to` with the :code:`value_type` of the
:code:`InputKeyIt` iterator type is used.  Finally, an instance of :code:`std::plus` with the
:code:`value_type` of the :code:`InputValueIt` iterator type is used if no binary operator is
provided to combine the elements of the value subsequences.

.. code:: cpp

    template<typename Policy, typename InputKeyIt, typename InputValueIt,
        typename OutputValueIt,
        typename BinaryPredcate =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type,
        typename BinaryOp =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>>
    OutputValueIt
    inclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first,
        InputKeyIt keys_last, InputValueIt values_first, OutputValueIt values_result
        BinaryPred binary_pred =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type>(),
        BinaryOp binary_op =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>());

:code:`dpstd::inclusive_scan_by_segment` performs partial prefix scans by applying the :code:`binary_op`
operation to a sequence of values. Each partial scan applies to a contiguous subsequence determined by
the keys associated with the values being equal according to the :code:`binary_pred` predicate.
The return value is an iterator targeting the end of the result sequence.

If no binary predicate is provided for the comparison of keys an instance of :code:`std::equal_to`
with the :code:`value_type` of the :code:`InputKeyIt` iterator type is used.  An instance of
:code:`std::plus` with the :code:`value_type` of the :code:`InputValueIt` iterator type is used if
no binary operator is provided to combine the elements of the value subsequences.

.. code:: cpp

    template<typename Policy, typename InputKeyIt, typename InputValueIt,
        typename OutputKeyIt, typename OutputValueIt,
        typename BinaryPredcate =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type,
        typename BinaryOp =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>>
    std::pair<OutputKeyIt,OutputValueIt>
    reduce_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
        InputValueIt values_first, OutputKeyIt keys_result,
        OutputValueIt values_result,
        BinaryPred binary_pred =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type>(),
        BinaryOp binary_op =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>());

:code:`dpstd::reduce_by_segment` performs partial reductions on a sequence of values. Each
reduction is computed with the :code:`binary_op` operation for a contiguous subsequence of values
determined by the associated keys being equal according to the :code:`binary_pred` predicate.
For each subsequence the first of the equal keys is stored into :code:`keys_result` and the computed
reduction is stored into :code:`values_result`. The return value is a pair of
iterators holding the end of the resulting sequences.

If no binary predicate is provided for the comparison of keys an instance of :code:`std::equal_to`
with the :code:`value_type` of the :code:`InputKeyIt` iterator type is used. An instance of
:code:`std::plus` with the :code:`value_type` of the :code:`InputValueIt` iterator type is used to
combine the values in each subsequence identified if a binary operator is not provided.

.. code:: cpp

    template<typename Policy, typename InputIt1, typename InputIt2, typename OutputIt,
        typename Comparator =
            std::less<typename std::iterator_traits<InputIt>::value_type>>
    OutputIt
    binary_search(Policy&& policy, InputIt1 start, InputIt1 end,
        InputIt2 value_first, InputIt2 value_last, OutputIterator result,
        Comparator comp =
            std::less<typename std::iterator_traits<InputIt1>::value_type>());

:code:`dpstd::binary_search` performs a binary search over the data in :code:`[start, end)` for each
value in :code:`[value_first, value_last)`.  If the value exists in the data searched then the
corresponding element in :code:`[result, result + distance(value_first, value_last))` is set to true,
otherwise it is set to false.

If no comparator is provided, :code:`operator<` is used to determine
when the search value is less than an element in the range being searched.

.. code:: cpp

    template<typename Policy, typename InputIt1, typename InputIt2, typename OutputIt,
        typename Comparator =
            std::less<typename std::iterator_traits<InputIt>::value_type>>
    OutputIt
    lower_bound(Policy&& policy, InputIt1 start, InputIt1 end,
        InputIt2 value_first, InputIt2 value_last, OutputIterator result,
        Comparator comp =
            std::less<typename std::iterator_traits<InputIt1>::value_type>());

:code:`dpstd::lower_bound` performs a binary search over the data in :code:`[start, end)` for each
value in :code:`[value_first, value_last)` to find the lowest index at which the search value could
be inserted in :code:`[start, end)` without violating the ordering defined by the comparator
provided. That lowest index is then assigned to the corresponding element in
:code:`[result, result + distance(value_first, value_last))`.

If no comparator is provided, :code:`operator<` is used to determine
when the search value is less than an element in the range being searched.

.. code:: cpp

    template<typename Policy, typename InputIt1, typename InputIt2, typename OutputIt,
        typename Comparator =
            std::less<typename std::iterator_traits<InputIt>::value_type>>
    OutputIt
    upper_bound(Policy&& policy, InputIt1 start, InputIt1 end,
        InputIt2 value_first, InputIt2 value_last, OutputIterator result,
        Comparator comp =
            std::less<typename std::iterator_traits<InputIt1>::value_type>());

:code:`dpstd::upper_bound` performs a binary search over the data in :code:`[start, end)` for each
value in :code:`[value_first, value_last)` to find the highest index at which the search value could
be inserted in :code:`[start, end)` without violating the ordering defined by the comparator
provided. That highest index is then assigned to the corresponding element in
:code:`[result, result + distance(value_first, value_last))`.
  
If no comparator is provided, :code:`operator<` is used to determine
when the search value is less than an element in the range being searched.

