
Specific API of oneDPL
----------------------

.. code:: cpp

  namespace dpstd {

  // Declared in <dpstd/iterators.h>

    template <typename Integral>
    class counting_iterator;

    template <typename... Iterators>
    class zip_iterator;
    template <typename... Iterators>
    zip_iterator<Iterators...> make_zip_iterator(Iterators...);

    template <typename UnaryFunc, typename Iterator>
    class transform_iterator;
    template <typename UnaryFunc, typename Iterator>
    transform_iterator<UnaryFunc, Iterator> make_transform_iterator(Iterator, UnaryFunc);


  // Declared in <dpstd/functional>

    struct identity;

  // Defined in <dpstd/algorithm>

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename T>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              T init);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename T, typename BinaryPredicate>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              T init, BinaryPredicate binary_pred);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename T, typename BinaryPredicate, typename BinaryOp>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              T init, BinaryPredicate binary_pred, BinaryOp binary_op);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt>
    OutputValueIt
    inclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename BinaryPred>
    OutputValueIt
    inclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              BinaryPred binary_pred);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename BinaryPred, typename BinaryOp>
    OutputValueIt
    inclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              BinaryPred binary_pred, BinaryOp binary_op);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputKeyIt,
             typename OutputValueIt>
    std::pair<OutputKeyIt,OutputValueIt>
    reduce_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                      InputValueIt values_first, OutputKeyIt keys_result, OutputValueIt values_result);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputKeyIt,
             typename OutputValueIt, typename BinaryPred>
    std::pair<OutputKeyIt,OutputValueIt>
    reduce_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                      InputValueIt values_first, OutputKeyIt keys_result, OutputValueIt values_result,
                      BinaryPred binary_pred);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputKeyIt,
             typename OutputValueIt, typename BinaryPred, typename BinaryOp>
    std::pair<OutputKeyIt,OutputValueIt>
    reduce_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                      InputValueIt values_first, OutputKeyIt keys_result, OutputValueIt values_result,
                      BinaryPred binary_pred, BinaryOp binary_op);

  }
