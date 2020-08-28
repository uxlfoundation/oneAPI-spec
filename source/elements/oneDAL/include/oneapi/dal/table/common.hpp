namespace oneapi::dal {

enum class feature_type { nominal, ordinal, interval, ratio };

enum class data_layout { unknown, row_major, column_major };

class table_metadata {
public:
    /// Creates the metadata instance without information about features.
    /// The :expr:`feature_count` shall be set to zero.
    /// The properties :expr:`data_type` and :expr:`feature_type` shall not be initialized.
    table_metadata();

    /// Creates the metadata instance from external information about data types and
    /// feature types.
    /// @param dtypes Data types of features. Shall be assigned into the :expr:`data_type` property.
    /// @param ftypes Feature types of features. Shall be assigned into the :expr:`feature_type` property.
    /// @pre :expr:`dtypes.get_count() == ftypes.get_count()`
    table_metadata(const array<data_type>& dtypes, const array<feature_type>& ftypes);

    /// The count of features that metadata has information about
    /// @pre :expr:`feature_count >= 0`
    std::int64_t get_feature_count() const;

    /// Feature types in the metadata object. Shall be in range ``[0, feature_count)``
    const feature_type& get_feature_type(std::int64_t feature_index) const;

    /// Data types of features in the metadata object. Shall be in range ``[0, feature_count)``
    const data_type& get_data_type(std::int64_t feature_index) const;
};

class table {
public:
    /// Creates the table instance with zero row and column count.
    /// All the table properties shall be set to default value (see Properties section).
    table();

    /// Creates new table instance which shares all the data and property
    /// values with $other$.
    table(const table& other);

    /// Creates new table instance and moves all property values from $other$ into it.
    table(table&& other);

    /// Replaces the values of all properties by references to property values of $other$
    table& operator=(const table& other);

    /// Swaps the property values of this object and $other$.
    table& operator=(table&& other);

    /// Indicates whether table contains non-zero count of rows and columns or not
    bool has_data() const noexcept;

    /// The count of columns in the table.
    /// @remark default = 0
    std::int64_t get_column_count() const;

    /// The count of rows in the table.
    /// @remark default = 0
    std::int64_t get_row_count() const;

    /// The metadata object that hold additional information
    /// about the data within the table.
    /// @remark default = oneapi::dal::table_metadata{}
    const table_metadata& get_metadata() const;

    /// The runtime id of the table type.
    /// Every particular table sub-type shall have its unique ``kind``.
    /// Empty table shall have a unique kind value as well.
    /// @remark default = empty_table_kind
    std::int64_t get_kind() const;

    /// The layout of the data within the table
    /// @remark default = data_layout::unknown
    data_layout get_data_layout() const;
};

} // namespace oneapi::dal
