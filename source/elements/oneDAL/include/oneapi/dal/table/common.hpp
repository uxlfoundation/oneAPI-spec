namespace oneapi::dal {

enum class feature_type { nominal, ordinal, interval, ratio };

enum class data_layout { unknown, row_major, column_major };

class table_metadata {
public:
    /// Creates empty metadata - without any feature information.
    /// @post :expr:`feature_count == 0`
    table_metadata();

    /// Creates metadata object from external information about data types and
    /// feature types.
    /// @param dtypes Data types of features. Shall be assigned into :expr:`data_type` property.
    /// @param ftypes Feature types of features. Shall be assigned into :expr:`feature_type` property.
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
    /// Creates an empty table - with zero row and column count. This table
    /// shall not contains any data, other properties are set to default values.
    table();

    /// Creates a new table object which shares all the data and property
    /// values with $t$.
    ///
    /// @param t The table object that will share its data with this object.
    table(const table& t);

    /// Moves $t$ into new table object.
    ///
    /// @param t The table object to be moved inside this one.
    table(table&& t);

    /// Creates table from an implementation object. $Impl$ shall be the
    /// appropriate implementation type: it shall implement all the properties
    /// of table class with the getter semantics as defined in the table class.
    /// The checks can be done in compile-time using SFINAE technique or in
    /// run-time using $impl$ object API. $Impl$ shall not be derived from table
    /// type.
    /// `template <typename T> static constexpr bool oneapi::dal::is_table_impl_v<T>`
    /// implements the mentioned optional compile-time checks on $Impl$ type.
    template <typename Impl,
              typename ImplType = std::decay_t<Impl>,
              typename          = std::enable_if_t<!std::is_base_of_v<table, ImplType> &&
                                                   is_table_impl_v<ImplType>>>
    table(Impl&& impl);

    /// Assigns reference to $t$ inside this object. Leaves data and properties
    /// held by the table before. The table shall share data and properties with
    /// $t$.
    ///
    /// @param t The table object that will share its data with this object.
    table& operator=(const table& t);

    /// Moves $t$ inside this object. Leaves data and properties held by the
    /// table before. All data and properties are reassigned from $t$ to this
    /// object.
    ///
    /// @param t The table object to be moved inside this one.
    table& operator=(table&& t);

    /// Indicates whether table is empty or not
    /// @return has_data True if table contains non-zero count of rows and columns.
    ///                  Otherwise returns false.
    bool has_data() const noexcept;

    /// The count of columns in the table.
    /// @remark default = 0
    std::int64_t get_column_count() const;

    /// The count of rows in the table.
    /// @remark default = 0
    std::int64_t get_row_count() const;

    /// The metadata object that hold additional information
    /// about data inside the table.
    /// @remark default = oneapi::dal::table_metadata{}
    const table_metadata& get_metadata() const;

    /// The runtime id of the actual table type.
    /// Every particular table sub-type shall have its unique ``kind``.
    /// Empty table shall have a unique kind value as well.
    /// @remark default = empty_table_kind
    std::int64_t get_kind() const;

    /// The layout of data inside the table
    /// @remark default = data_layout::unknown
    data_layout get_data_layout() const;
};

} // namespace oneapi::dal
