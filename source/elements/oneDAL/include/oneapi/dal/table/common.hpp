namespace oneapi::dal {

enum class feature_type { nominal, ordinal, interval, ratio };

enum class data_layout { unknown, row_major, column_major };

class table_metadata {
public:
    /// Creates the metadata instance without information about the features.
    /// The :expr:`feature_count` shall be set to zero.
    /// The :expr:`data_type` and :expr:`feature_type` properties shall not be initialized.
    table_metadata();

    /// Creates the metadata instance from external information about the data types and the
    /// feature types.
    /// @param dtypes The data types of the features. Shall be assigned into the :expr:`data_type` property.
    /// @param ftypes The feature types. Shall be assigned into the :expr:`feature_type` property.
    /// @pre :expr:`dtypes.get_count() == ftypes.get_count()`
    table_metadata(const array<data_type>& dtypes, const array<feature_type>& ftypes);

    /// The number of features that metadata contains information about
    /// @pre :expr:`feature_count >= 0`
    std::int64_t get_feature_count() const;

    /// Feature types in the metadata object. Shall be within the range ``[0, feature_count)``
    const feature_type& get_feature_type(std::int64_t feature_index) const;

    /// Data types of the features in the metadata object. Shall be within the range ``[0, feature_count)``
    const data_type& get_data_type(std::int64_t feature_index) const;
};

class table {
public:
    /// An empty table constructor: creates the table instance with zero number of rows and columns.
    /// Implementation shall be set to the special "empty" object that returns all the property values
    /// set to default (see Properties section).
    table();

    /// Creates a new table instance which shares implementation with $other$.
    table(const table& other);

    /// Creates a new table instance and moves implementation from $other$ into it.
    table(table&& other);

    /// Replaces the implementation by another one from $other$.
    table& operator=(const table& other);

    /// Swaps the implementation of this object and $other$.
    table& operator=(table&& other);

    /// Indicates whether a table contains non-zero number of rows and columns.
    bool has_data() const noexcept;

    /// The number of columns in the table.
    /// @remark default = 0
    std::int64_t get_column_count() const;

    /// The number of rows in the table.
    /// @remark default = 0
    std::int64_t get_row_count() const;

    /// The metadata object that holds additional information
    /// about the data within the table.
    /// @remark default = table_metadata()
    const table_metadata& get_metadata() const;

    /// The runtime id of the table type.
    /// Each table sub-type shall have its unique ``kind``.
    /// An empty table (see the default constructor) shall have a unique ``kind`` value as well.
    /// @remark default = empty_table_kind
    std::int64_t get_kind() const;

    /// The layout of the data within the table
    /// @remark default = data_layout::unknown
    data_layout get_data_layout() const;
};

} // namespace oneapi::dal
