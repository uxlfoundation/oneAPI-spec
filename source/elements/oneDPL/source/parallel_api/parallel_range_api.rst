.. SPDX-FileCopyrightText: Contributors to the oneAPI Specification project.
..
.. SPDX-License-Identifier: CC-BY-4.0

Parallel Range Algorithms
-------------------------

oneDPL provides variations of algorithms that work with ranges defined in the `C++ Standard`_, 6th edition (C++20)
and newer. These algorithms execute according to a oneDPL execution policy supplied as the first argument,
similarly to other oneDPL algorithms.

The oneDPL parallel range algorithms rely on the functionality of C++20 and are not available in the code
compiled for earlier editions of the C++ standard.

The parallel range algorithms reside in ``namespace oneapi::dpl::ranges``. Same as the range algorithm functions
defined by the C++ standard in ``namespace std::ranges``, they cannot be found by argument-dependent name lookup
and cannot be called with explicitly specified template arguments. [*Note*: A typical implementation uses
predefined function objects which static function call operators have the required signatures. -- *end note*]

The following differences to the standard C++ range algorithms apply:

- Parallel range algorithms cannot be used in constant expressions.
- The oneDPL execution policy parameter is added.
- Output data sequences are defined as ranges, not iterators.
- Both input and output ranges must support random access.
- As a rule, both input and output ranges must be sized.

  - Exceptions are binary ``transform``, ``equal``, and ``mismatch``, where at least one of the input ranges
    must be sized, and if a range is not sized it is supposed to be infinite.
    [*Note*: An example of an infinite range is ``std::views::repeat`` with no bound. -- *end note*]

- For algorithms with bounded output ranges, processing may not need to go over all the input data.
  In that case, the returned value contains iterators pointing to the positions past the last elements
  processed according to the algorithm semantics.
- ``for_each`` does not return its function object.

Except for these differences, the signatures of parallel range algorithms correspond to the working draft
of the next edition of the C++ standard (C++26).

Auxiliary Definitions
+++++++++++++++++++++

The following auxiliary entities are only defined for the purpose of exposition, to aid the specification
of parallel range algorithms.

.. code:: cpp

   // C++20 analogue of std::projected_value_t; exposition only
   template<typename I, typename Proj>
   using /*projected-value-type*/ = std::remove_cvref_t<std::invoke_result_t<Proj&, std::iter_value_t<I>&>>;

Whole Sequence Operations
+++++++++++++++++++++++++

.. code:: cpp

  // Defined in <oneapi/dpl/algorithm>

  namespace oneapi::dpl::ranges {

    // all_of
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_unary_predicate< std::projected<std::ranges::iterator_t<R>, Proj> > Pred>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      bool all_of (ExecutionPolicy&& pol, R&& r, Pred pred, Proj proj = {});

    // any_of
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_unary_predicate< std::projected<std::ranges::iterator_t<R>, Proj> > Pred>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      bool any_of (ExecutionPolicy&& pol, R&& r, Pred pred, Proj proj = {});

    // none_of
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_unary_predicate< std::projected<std::ranges::iterator_t<R>, Proj> > Pred>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      bool none_of (ExecutionPolicy&& pol, R&& r, Pred pred, Proj proj = {});

    // for_each
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirectly_unary_invocable< std::projected<std::ranges::iterator_t<R>, Proj> > Fn>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      std::ranges::borrowed_iterator_t<R>
        for_each (ExecutionPolicy&& pol, R&& r, Fn f, Proj proj = {});

    // count
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              typename T = /*projected-value-type*/<std::ranges::iterator_t<R>, Proj>>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> &&
               std::indirect_binary_predicate< std::ranges::equal_to,
                                               std::projected<std::ranges::iterator_t<R>, Proj>,
                                               const T* >
      std::ranges::range_difference_t<R>
        count (ExecutionPolicy&& pol, R&& r, const T& value, Proj proj = {});

    // count_if
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_unary_predicate< std::projected<std::ranges::iterator_t<R>, Proj> > Pred>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      std::ranges::range_difference_t<R>
        count_if (ExecutionPolicy&& pol, R&& r, Pred pred, Proj proj = {});

  }

Element Search Operations
+++++++++++++++++++++++++

.. code:: cpp

  // Defined in <oneapi/dpl/algorithm>

  namespace oneapi::dpl::ranges {

    // find
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              typename T = /*projected-value-type*/<std::ranges::iterator_t<R>, Proj>>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> &&
               std::indirect_binary_predicate< std::ranges::equal_to,
                                               std::projected<std::ranges::iterator_t<R>, Proj>,
                                               const T* >
      std::ranges::borrowed_iterator_t<R>
        find (ExecutionPolicy&& pol, R&& r, const T& value, Proj proj = {});

    // find_if
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_unary_predicate< std::projected<std::ranges::iterator_t<R>, Proj> > Pred>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      std::ranges::borrowed_iterator_t<R>
        find_if (ExecutionPolicy&& pol, R&& r, Pred pred, Proj proj = {});

    // find_if_not
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_unary_predicate< std::projected<std::ranges::iterator_t<R>, Proj> > Pred>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      std::ranges::borrowed_iterator_t<R>
        find_if_not (ExecutionPolicy&& pol, R&& r, Pred pred, Proj proj = {});

    // find_first_of
    template<typename ExecutionPolicy, std::ranges::random_access_range R1,
             std::ranges::random_access_range R2, typename Pred = std::ranges::equal_to,
             typename Proj1 = std::identity, typename Proj2 = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R1> && std::ranges::sized_range<R2> &&
               std::indirectly_comparable< std::ranges::iterator_t<R1>, std::ranges::iterator_t<R2>,
                                           Pred, Proj1, Proj2 >
      std::ranges::borrowed_iterator_t<R1>
        find_first_of (ExecutionPolicy&& pol, R1&& r1, R2&& r2, Pred pred = {},
                       Proj1 proj1 = {}, Proj2 proj2 = {});

    // adjacent_find
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_binary_predicate< std::projected<std::ranges::iterator_t<R>, Proj>,
                                              std::projected<std::ranges::iterator_t<R>, Proj> >
                    Pred = std::ranges::equal_to>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      std::ranges::borrowed_iterator_t<R>
        adjacent_find (ExecutionPolicy&& pol, R&& r, Pred pred = {}, Proj proj = {});

  }

Minimum and Maximum
+++++++++++++++++++

.. code:: cpp

  // Defined in <oneapi/dpl/algorithm>

  namespace oneapi::dpl::ranges {

    // min
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_strict_weak_order< std::projected<std::ranges::iterator_t<R>, Proj> >
                    Comp = std::ranges::less>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> &&
               std::indirectly_copyable_storable< std::ranges::iterator_t<R>,
                                                  std::ranges::range_value_t<R>* >
      std::ranges::range_value_t<R>
        min (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});

    // max
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_strict_weak_order< std::projected<std::ranges::iterator_t<R>, Proj> >
                    Comp = std::ranges::less>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> &&
               std::indirectly_copyable_storable< std::ranges::iterator_t<R>,
                                                  std::ranges::range_value_t<R>* >
      std::ranges::range_value_t<R>
        max (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});


    // minmax
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_strict_weak_order< std::projected<std::ranges::iterator_t<R>, Proj> >
                    Comp = std::ranges::less>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> &&
               std::indirectly_copyable_storable< std::ranges::iterator_t<R>,
                                                  std::ranges::range_value_t<R>* >
      std::ranges::minmax_result<std::ranges::range_value_t<R>>
        minmax (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});

    // min_element
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_strict_weak_order< std::projected<std::ranges::iterator_t<R>, Proj> >
                    Comp = std::ranges::less>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      std::ranges::borrowed_iterator_t<R>
        min_element (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});

    // max_element
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_strict_weak_order< std::projected<std::ranges::iterator_t<R>, Proj> >
                    Comp = std::ranges::less>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      std::ranges::borrowed_iterator_t<R>
        max_element (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});

    // minmax_element
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_strict_weak_order< std::projected<std::ranges::iterator_t<R>, Proj> >
                    Comp = std::ranges::less>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      std::ranges::minmax_element_result<std::ranges::borrowed_iterator_t<R>>
        minmax_element (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});

  }

Sequence Search and Comparison
++++++++++++++++++++++++++++++

.. code:: cpp

  // Defined in <oneapi/dpl/algorithm>

  namespace oneapi::dpl::ranges {

    // equal
    template<typename ExecutionPolicy, std::ranges::random_access_range R1,
             std::ranges::random_access_range R2, typename Pred = std::ranges::equal_to,
             typename Proj1 = std::identity, typename Proj2 = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               (std::ranges::sized_range<R1> || std::ranges::sized_range<R2>) &&
               std::indirectly_comparable< std::ranges::iterator_t<R1>, std::ranges::iterator_t<R2>,
                                           Pred, Proj1, Proj2 >
      bool equal (ExecutionPolicy&& pol, R1&& r1, R2&& r2, Pred pred = {},
                  Proj1 proj1 = {}, Proj2 proj2 = {});

    // mismatch
    template<typename ExecutionPolicy, std::ranges::random_access_range R1,
             std::ranges::random_access_range R2, typename Pred = std::ranges::equal_to,
             typename Proj1 = std::identity, typename Proj2 = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               (std::ranges::sized_range<R1> || std::ranges::sized_range<R2>) &&
               std::indirectly_comparable< std::ranges::iterator_t<R1>, std::ranges::iterator_t<R2>,
                                           Pred, Proj1, Proj2 >
      std::ranges::mismatch_result<std::ranges::borrowed_iterator_t<R1>,
                                   std::ranges::borrowed_iterator_t<R2>>
        mismatch (ExecutionPolicy&& pol, R1&& r1, R2&& r2, Pred pred = {},
                  Proj1 proj1 = {}, Proj2 proj2 = {});
                  

    // find_end
    template<typename ExecutionPolicy, std::ranges::random_access_range R1,
             std::ranges::random_access_range R2, typename Pred = std::ranges::equal_to,
             typename Proj1 = std::identity, typename Proj2 = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R1> && std::ranges::sized_range<R2> &&
               std::indirectly_comparable< std::ranges::iterator_t<R1>, std::ranges::iterator_t<R2>,
                                           Pred, Proj1, Proj2 >
      std::ranges::borrowed_subrange_t<R1>
        find_end (ExecutionPolicy&& pol, R1&& r1, R2&& r2, Pred pred = {},
                  Proj1 proj1 = {}, Proj2 proj2 = {});

    // search
    template<typename ExecutionPolicy, std::ranges::random_access_range R1,
             std::ranges::random_access_range R2, typename Pred = std::ranges::equal_to,
             typename Proj1 = std::identity, typename Proj2 = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R1> && std::ranges::sized_range<R2> &&
               std::indirectly_comparable< std::ranges::iterator_t<R1>, std::ranges::iterator_t<R2>,
                                           Pred, Proj1, Proj2 >
      std::ranges::borrowed_subrange_t<R1>
        search (ExecutionPolicy&& pol, R1&& r1, R2&& r2, Pred pred = {},
                Proj1 proj1 = {}, Proj2 proj2 = {});

    // search_n
    template<typename ExecutionPolicy, std::ranges::random_access_range R,
             typename Pred = std::ranges::equal_to, typename Proj = std::identity,
             typename T = /*projected-value-type*/<std::ranges::iterator_t<R>, Proj>>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> &&
               std::indirectly_comparable< std::ranges::iterator_t<R>, const T*, Pred, Proj >
      std::ranges::borrowed_subrange_t<R>
        search_n (ExecutionPolicy&& pol, R&& r, std::ranges::range_difference_t<R> count,
                  const T& value, Pred pred = {}, Proj proj = {});

  }

Sorting and Merge
+++++++++++++++++

.. code:: cpp

  // Defined in <oneapi/dpl/algorithm>

  namespace oneapi::dpl::ranges {

    // sort
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Comp = std::ranges::less, typename Proj = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> && std::sortable<std::ranges::iterator_t<R>, Comp, Proj>
      std::ranges::borrowed_iterator_t<R>
        sort (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});

    // stable_sort
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Comp = std::ranges::less, typename Proj = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> && std::sortable<std::ranges::iterator_t<R>, Comp, Proj>
      std::ranges::borrowed_iterator_t<R>
        stable_sort (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});

    // is_sorted
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_strict_weak_order< std::projected<std::ranges::iterator_t<R>, Proj> >
                    Comp = std::ranges::less>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      bool is_sorted (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});

    // is_sorted_until
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_strict_weak_order< std::projected<std::ranges::iterator_t<R>, Proj> >
                    Comp = std::ranges::less>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R>
      std::ranges::borrowed_iterator_t<R>
        is_sorted_until (ExecutionPolicy&& pol, R&& r, Comp comp = {}, Proj proj = {});

    // merge
    template <typename ExecutionPolicy, std::ranges::random_access_range R1,
              std::ranges::random_access_range R2, std::ranges::random_access_range OutR,
              typename Comp = std::ranges::less, typename Proj1 = std::identity,
              typename Proj2 = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R1> && std::ranges::sized_range<R2> &&
               std::ranges::sized_range<OutR> &&
               std::mergeable<std::ranges::iterator_t<R1>, std::ranges::iterator_t<R2>,
                              std::ranges::iterator_t<OutR>, Comp, Proj1, Proj2>
      std::ranges::merge_result<std::ranges::borrowed_iterator_t<R1>,
                                std::ranges::borrowed_iterator_t<R2>,
                                std::ranges::borrowed_iterator_t<OutR>>
        merge (ExecutionPolicy&& pol, R1&& r1, R2&& r2, OutR&& result, Comp comp = {},
               Proj1 proj1 = {}, Proj2 proj2 = {});

  }

Copying Mutating Operations
+++++++++++++++++++++++++++

.. code:: cpp

  // Defined in <oneapi/dpl/algorithm>

  namespace oneapi::dpl::ranges {

    // copy
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              std::ranges::random_access_range OutR>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> && std::ranges::sized_range<OutR> &&
               std::indirectly_copyable<std::ranges::iterator_t<R>, std::ranges::iterator_t<OutR>>
      std::ranges::copy_result<std::ranges::borrowed_iterator_t<R>,
                               std::ranges::borrowed_iterator_t<OutR>>
        copy (ExecutionPolicy&& pol, R&& r, OutR&& result);

    // copy_if
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              std::ranges::random_access_range OutR, typename Proj = std::identity,
              std::indirect_unary_predicate< std::projected<std::ranges::iterator_t<R>, Proj> > Pred>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> && std::ranges::sized_range<OutR> &&
               std::indirectly_copyable<std::ranges::iterator_t<R>, std::ranges::iterator_t<OutR>>
      std::ranges::copy_if_result<std::ranges::borrowed_iterator_t<R>,
                                  std::ranges::borrowed_iterator_t<OutR>>
        copy_if (ExecutionPolicy&& pol, R&& r, OutR&& result, Pred pred, Proj proj = {});

    // move
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              std::ranges::random_access_range OutR>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> && std::ranges::sized_range<OutR> &&
               std::indirectly_movable<std::ranges::iterator_t<R>, std::ranges::iterator_t<OutR>>
      std::ranges::move_result<std::ranges::borrowed_iterator_t<R>,
                               std::ranges::borrowed_iterator_t<OutR>>
        move (ExecutionPolicy&& pol, R&& r, OutR&& result);

    // transform (unary)
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              std::ranges::random_access_range OutR, std::copy_constructible Fn,
              typename Proj = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> && std::ranges::sized_range<OutR> &&
               std::indirectly_writable< std::ranges::iterator_t<OutR>,
                    std::indirect_result_t<Fn&, std::projected<std::ranges::iterator_t<R>, Proj>> >
      std::ranges::unary_transform_result<std::ranges::borrowed_iterator_t<R>,
                                          std::ranges::borrowed_iterator_t<OutR>>
        transform (ExecutionPolicy&& pol, R&& r, OutR&& result, Fn unary_op, Proj proj = {});

    // transform (binary)
    template <typename ExecutionPolicy, std::ranges::random_access_range R1,
              std::ranges::random_access_range R2, std::ranges::random_access_range OutR,
              std::copy_constructible Fn, typename Proj1 = std::identity,
              typename Proj2 = std::identity>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               (std::ranges::sized_range<R1> || std::ranges::sized_range<R2>) &&
               std::ranges::sized_range<OutR> &&
               std::indirectly_writable< std::ranges::iterator_t<OutR>,
                    std::indirect_result_t<Fn&, std::projected<std::ranges::iterator_t<R1>, Proj1>,
                                                std::projected<std::ranges::iterator_t<R2>, Proj2>> >
      std::ranges::binary_transform_result<std::ranges::borrowed_iterator_t<R1>,
                                           std::ranges::borrowed_iterator_t<R2>,
                                           std::ranges::borrowed_iterator_t<OutR>>
        transform (ExecutionPolicy&& pol, R1&& r1, R2&& r2, OutR&& result, Fn binary_op,
                   Proj1 proj1 = {}, Proj2 proj2 = {});

  }

In-place Mutating Operations
++++++++++++++++++++++++++++

.. code:: cpp

  // Defined in <oneapi/dpl/algorithm>

  namespace oneapi::dpl::ranges {

    // fill
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename T = std::ranges::range_value_t<R>>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> &&
               std::indirectly_writable<std::ranges::iterator_t<R>, const T&>
      std::ranges::borrowed_iterator_t<R>
        fill (ExecutionPolicy&& pol, R&& r, const T& value);
  
    // replace
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              typename T1 = /*projected-value-type*/<std::ranges::iterator_t<R>, Proj>, typename T2 = T1>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> &&
               std::indirectly_writable<std::ranges::iterator_t<R>, const T2&> &&
               std::indirect_binary_predicate< std::ranges::equal_to,
                                               std::projected<std::ranges::iterator_t<R>, Proj>,
                                               const T1* >
      std::ranges::borrowed_iterator_t<R>
        replace (ExecutionPolicy&& pol, R&& r, const T1& old_value, const T2& new_value,
                 Proj proj = {});

    // replace_if
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              typename T = /*projected-value-type*/<std::ranges::iterator_t<R>, Proj>,
              std::indirect_unary_predicate< std::projected<std::ranges::iterator_t<R>, Proj> > Pred>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> &&
               std::indirectly_writable<std::ranges::iterator_t<R>, const T&>
      std::ranges::borrowed_iterator_t<R>
        replace_if (ExecutionPolicy&& pol, R&& r, Pred pred, const T& new_value, Proj proj = {});

    // remove
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              typename T = /*projected-value-type*/<std::ranges::iterator_t<R>, Proj>>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> && std::permutable<std::ranges::iterator_t<R> &&
               std::indirect_binary_predicate< std::ranges::equal_to,
                                               std::projected<std::ranges::iterator_t<R>, Proj>,
                                               const T* >
      std::ranges::borrowed_subrange_t<R>
        remove (ExecutionPolicy&& pol, R&& r, const T& value, Proj proj = {});

    // remove_if
    template <typename ExecutionPolicy, std::ranges::random_access_range R,
              typename Proj = std::identity,
              std::indirect_unary_predicate< std::projected<std::ranges::iterator_t<R>, Proj> > Pred>
      requires oneapi::dpl::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>> &&
               std::ranges::sized_range<R> && std::permutable<std::ranges::iterator_t<R>>
      std::ranges::borrowed_subrange_t<R>
        remove_if (ExecutionPolicy&& pol, R&& r, Pred pred, Proj proj = {});

  }

.. _`C++ Standard`: https://isocpp.org/std/the-standard
.. _`SYCL`: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html
