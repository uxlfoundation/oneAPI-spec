namespace oneapi::dal {

class base {
public:
    virtual ~base() = default;
};

enum class data_type {
    /// 8-bit signed integer value type
    int8,
    /// 16-bit signed integer value type
    int16,
    /// 32-bit signed integer value type
    int32,
    /// 64-bit signed integer value type
    int64,
    /// 8-bit unsigned integer value type
    uint8,
    /// 16-bit unsigned integer value type
    uint16,
    /// 32-bit unsigned integer value type
    uint32,
    /// 64-bit unsigned integer value type
    uint64,
    /// 32-bit floating-point value type
    float32,
    /// 64-bit floating-point value type
    float64,
    /// bi-float value type
    bfloat16
};

struct range {
public:
    /// Constructs a range of elements from start and end indices.
    ///
    /// @param start The first index in the range. The value shall be >= 0
    /// @param end   The relative end index in the range. Indicates the next index after
    ///              last one in the range. If positive, shall be greater than $start$.
    ///              If negative, indicates the offset of the last element from the end of the range.
    ///              For example, :expr:`start=1`, :expr:`end=-2` specify the range of elements
    ///              [1, 2, 3] in the set [0, 1, 2, 3, 4]
    range(std::int64_t start, std::int64_t end);

    /// The number of elements in the range.
    /// The ``max_end_index`` value specifies the last maximal index in the sequence.
    std::int64_t get_element_count(std::int64_t max_end_index) const noexcept;

    /// The start index in the range
    std::int64_t start_idx;

    /// The relative index of last element in the range.
    /// If positive, points to the next element after last one in the range.
    /// If negative, poinst to the last element in the range.
    std::int64_t end_idx;
};

} // namespace oneapi::dal
