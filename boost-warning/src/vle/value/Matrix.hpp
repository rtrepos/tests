/*
 * This file is part of VLE, a framework for multi-modeling, simulation
 * and analysis of complex dynamical systems.
 * http://www.vle-project.org
 *
 * Copyright (c) 2003-2013 Gauthier Quesnel <quesnel@users.sourceforge.net>
 * Copyright (c) 2003-2013 ULCO http://www.univ-littoral.fr
 * Copyright (c) 2007-2013 INRA http://www.inra.fr
 *
 * See the AUTHORS or Authors.txt file for copyright owners and
 * contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef VLE_VALUE_MATRIX_HPP
#define VLE_VALUE_MATRIX_HPP 1

#include <vle/value/Value.hpp>
#include <vle/value/Double.hpp>
#include <vle/DllDefines.hpp>
#include <boost/multi_array.hpp>

namespace vle { namespace value {

/// @brief Define a Matrix of value::Value object.
typedef boost::multi_array<value::Value*, 2 >  MatrixValue;

/// @brief Define a Vector View  of the Matrix.
typedef MatrixValue::array_view < 1 >::type VectorView;

/// @brief Define a constant Vector View  of the Matrix.
typedef MatrixValue::const_array_view < 1 >::type ConstVectorView;

/// @brief Define a Matrix View of the Matrix.
typedef MatrixValue::array_view < 2 >::type MatrixView;

/// @brief Define a constant Matrix View of the Matrix.
typedef MatrixValue::const_array_view < 2 >::type ConstMatrixView;

/**
 * @brief A Matrix Value. This class wraps a boost::multi_array from the
 * Boost library (http://www.boost.org) class of two dimension of
 * value::Value.
 */
class VLE_API Matrix : public Value
{
public:
    /// Define indices of Matrix.
    typedef MatrixValue::index_gen Indices;

    /// Define a Range of Matrix.
    typedef MatrixValue::index_range Range;

    /// Define a Extents of Matrix.
    typedef MatrixValue::extent_gen Extents;

    /// Define an index of Matrix.
    typedef MatrixValue::index index;

    /// Define a dimension size of Matrix.
    typedef MatrixValue::size_type size_type;

    typedef MatrixValue::iterator iterator;
    typedef MatrixValue::const_iterator const_iterator;

    /**
     * @brief Build an empty Matrix.
     */
    Matrix()
        : m_matrix(), m_nbcol(0), m_nbrow(0), m_stepcol(1), m_steprow(1),
        m_lastX(0), m_lastY(0)
    {}

    /**
     * @brief Build an empty matrix of value of size [colums][row].
     * @param columns the initial number of columns.
     * @param rows the initial number of rows.
     * @param resizeColumns the number of columns to add when resize the matrix.
     * @param resizeRows the number of rows to add when resize the matrix.
     */
    Matrix(index columns, index rows, index resizeColumns, index resizeRows)
        : m_matrix(m_extents[columns][rows]), m_nbcol(columns), m_nbrow(rows),
        m_stepcol(resizeColumns), m_steprow(resizeRows), m_lastX(0), m_lastY(0)
    {}

    /**
     * @brief Build an empty buffered matrix of value of size [colums][rows] in
     * a matrix of [columnmax][rowmax].
     * @param columns the initial number of columns.
     * @param rows the initial number of rows.
     * @param columnmax The max number of columns.
     * @param rowmax The max number of rows.
     * @param resizeColumns the number of columns to add when resize the matrix.
     * @param resizeRow the number of rows to add when resize the matrix.
     * @throw utils::ArgError if columns > columnmax or if rows > rowmax.
     */
    Matrix(index columns, index rows, index columnmax, index rowmax,
           index resizeColumns, index resizeRow);

    /**
     * @brief Build a new Matrix, all the value::Value from the
     * Matrix are cloned.
     * @param m the Matrix to copy.
     */
    Matrix(const Matrix& m);

    /**
     * @brief Delete all data.
     */
    virtual ~Matrix()
    { clear(); }

    /**
     * @brief Build a new Matrix.
     * @param columns Define the number of columns for the buffer.
     * @param rows Define the number of rows for the buffer.
     * @param resizeColumns Number of columns when resize buffer.
     * @param resizeRows Number of row when resize buffer.
     * @return A new allocated Matrix.
     */
    static Matrix* create(index columns = 10,
                          index rows = 10,
                          index resizeColumns = 10,
                          index resizeRows = 10)
    { return new Matrix(columns, rows, resizeColumns, resizeRows); }

    /**
     * @brief Build a new Matrix with a specified views.
     * @param columns Define the number of columns for the buffer.
     * @param rows Define the number of rows for the buffer.
     * @param columnmax The max number of columns.
     * @param rowmax The max number of rows.
     * @param resizeColumns Number of columns when resize buffer.
     * @param resizeRows Number of row when resize buffer.
     * @return A new allocated Matrix.
     */
    static Matrix* create(index columns,
                          index rows,
                          index columnmax,
                          index rowmax,
                          index resizeColumns,
                          index resizeRows)
    { return new Matrix(columns, rows, columnmax, rowmax, resizeColumns,
                        resizeRows); }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    /**
     * @brief Clone the Matrix and all value::Value.
     * @return A new Matrix.
     */
    virtual Value* clone() const
    { return new Matrix(*this); }

    /**
     * @brief Get the type of this class.
     * @return Value::MATRIX.
     */
    inline virtual Value::type getType() const
    { return Value::MATRIX; }

    /**
     * @brief Push all Value from the MatrixValue, recursively and space
     * separated.
     * @code
     * 1 2 3 4 5 NA 7
     * 8 9 1 2 3  4 5
     * @endcode
     * @param out The output stream.
     */
    virtual void writeFile(std::ostream& out) const;

    /**
     * @brief Push all Value from the MatrixValue, recursively and space
     * separated.
     * @code
     * 1 2 3 4 5 NA 7
     * 8 tutu 1 2 3  4 5
     * @endcode
     * @param out The output stream.
     */
    virtual void writeString(std::ostream& out) const;

    /**
     * @brief Push all Value from the MatrixValue recursively in an XML
     * representation.
     * @code
     * <matrix rows="2" columns="7" columnmax="100" rowmax="2000"
     *         columnstep="1" rowstep="12">
     *  <integer>1</integer>
     *  <integer>2</integer>
     *  <integer>3</integer>
     *  <integer>4</integer>
     *  <integer>5</integer>
     *  <null />
     *  <integer>7</integer>
     *  <string>tutu</string>
     *  <integer>9</integer>
     *  <integer>1</integer>
     *  <integer>2</integer>
     *  <integer>3</integer>
     *  <integer>4</integer>
     *  <integer>5</integer>
     * </matrix>
     * @endcode
     * @param out The output stream.
     */
    virtual void writeXml(std::ostream& out) const;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    iterator begin()
    { return m_matrix.begin(); }

    iterator end()
    { return m_matrix.end(); }

    const_iterator begin() const
    { return m_matrix.begin(); }

    const_iterator end() const
    { return m_matrix.end(); }

    size_type size() const
    { return columns() * rows() ; }

    /**
     * @brief Delete all element from the matrix. All value are deleted.
     */
    void clear();

    /**
     * @brief Resize the current matrix.
     * @param columns The number of columns of the matrix.
     * @param rows The number of rows of the matrix.
     * @throw utils::ArgError if data are loss.
     */
    void resize(const size_type& columns, const size_type& rows);

    /**
     * @brief Add a new column to the Matrix.
     */
    void addColumn();

    /**
     * @brief Add a new row to the Matrix.
     */
    void addRow();

    /**
     * @brief Set the cell at (column, row) to the specified value. Be careful,
     * the value is managed by the Matrix.
     * @param column index of the cell's column.
     * @param row index of the cell's row.
     * @param value the value to set.
     */
    void add(const size_type& column, const size_type& row,
             value::Value* val)
    {
        set(column, row, val);
    }

    /**
     * @brief Set the cell at (column, row) to the specified value.
     * @param column index of the cell's column.
     * @param row index of the cell's row.
     * @param value the value to set.
     */
    void add(const size_type& column, const size_type& row,
             const value::Value* val)
    {
        set(column, row, val);
    }

    /**
     * @brief Set the cell at (column, row) to the specified value.
     * The value is cloned.
     * @param column index of the cell's column.
     * @param row index of the cell's row.
     * @param value the value to set.
     */
    void add(const size_type& column, const size_type& row,
             const value::Value& val)
    {
        set(column, row, val);
    }

    /**
     * @brief Set the cell at (column, row) to the specified value. Be careful,
     * the value is managed by the Matrix.
     * @param column index of the cell's column.
     * @param row index of the cell's row.
     * @param value the value to set.
     */
    void set(const size_type& column, const size_type& row,
             value::Value* val)
    {
        delete m_matrix[column][row];
        m_matrix[column][row] = val;
    }

    /**
     * @brief Set the cell at (column, row) to the specified value.
     * @param column index of the cell's column.
     * @param row index of the cell's row.
     * @param value the value to set.
     */
    void set(const size_type& column, const size_type& row,
             const value::Value* val)
    {
        delete m_matrix[column][row];
        if (val) {
            m_matrix[column][row] = val->clone();
        } else {
            m_matrix[column][row] = 0;
        }
    }

    /**
     * @brief Set the cell at (column, row) to the specified value.
     * The value is cloned.
     * @param column index of the cell's column.
     * @param row index of the cell's row.
     * @param value the value to set.
     */
    void set(const size_type& column, const size_type& row,
             const value::Value& val)
    {
        delete m_matrix[column][row];
        m_matrix[column][row] = val.clone();
    }

    /**
     * @brief Get a pointer from a cell of the matrix.
     * @param column The column.
     * @param row The row.
     * @return A constant pointer to the Value.
     * @throw utils::ArgError if bad access to the matrix, in debug mode only.
     */
    const Value* get(const size_type& column, const size_type& row) const
    {
#ifndef NDEBUG
        if (not (column < m_nbcol and row <= m_nbrow)) {
            throw 1;
        }
#endif

        return m_matrix[column][row];
    }

    /**
     * @brief Get a pointer from a cell of the matrix.
     * @param column The column.
     * @param row The row.
     * @return A pointer to the Value.
     * @throw utils::ArgError if bad access to the matrix, in debug mode only.
     */
    Value* get(const size_type& column, const size_type& row)
    {
#ifndef NDEBUG
        if (not (column < m_nbcol and row <= m_nbrow)) {
            throw 1;
        }
#endif
        return m_matrix[column][row];
    }

    /**
     * @brief Set the last cell to the specificed value. The value is
     * cloned.
     * @param val the value to clone and assign.
     */
    void addToLastCell(const value::Value& val)
    {
        add(m_lastX, m_lastY, val);
    }

    /**
     * @brief Set the last cell to the specificed value.
     * Be careful, the value is managed by the Matrix.
     * @param val the value to assign. Be carefull, the value is managed by
     * the Matrix class.
     */
    void addToLastCell(value::Value* val)
    {
        add(m_lastX, m_lastY, val);
    }

    /**
     * @brief Move the last cell to the nearest Cell in column or row. If
     * the last cell equal the number of column, column is set to 0, row to
     * row + 1. If the row equal the number of row, row is set to 0.
     */
    void moveLastCell();

    /**
     * @brief Get the correct subset of the Matrix define in:
     * [0, columns()][0, rows()]. Not the global Matrix:
     * [0, matrix.shape()[0][0, matrix.shape()[1]];
     * @return A view of the data.
     */
    inline MatrixView value()
    { return m_matrix[m_indices [Range(0, m_nbcol)][Range(0, m_nbrow)]]; }

    /**
     * @brief Get the correct subset of the Matrix define in:
     * [0, columns()][0, rows()]. Not the global Matrix:
     * [0, matrix.shape()[0][0, matrix.shape()[1]];
     * @return A view of the data.
     */
    inline ConstMatrixView value() const
    { return m_matrix[m_indices [Range(0, m_nbcol)][Range(0, m_nbrow)]]; }

    /**
     * @brief Get the correct subset of the Matrx define in:
     * [0, columns()][0, rows()]. Not the global Matrix:
     * [0, matrix.shape()[0][0, matrix.shape()[1]];
     * @return A constant view of the data.
     */
    inline ConstMatrixView getConstValue() const
    { return m_matrix[m_indices [Range(0, m_nbcol)][Range(0, m_nbrow)]]; }

    /**
     * @brief Get a constant reference to the complete matrix.
     * @return A constant reference to the complete matrix.
     */
    inline const MatrixValue& matrix() const
    { return m_matrix; }

    /**
     * @brief Return the number of valid column data.
     * @return the number of valid column.
     */
    inline size_type columns() const
    { return m_nbcol; }

    /**
     * @brief Return a vector from the Matrix.
     * @param index the index of the vector.
     * @return A view on the column of the Matrix.
     */
    inline VectorView column(index index)
    { return m_matrix[boost::indices[index][Range(0, m_nbrow)]]; }

    /**
     * @brief Return a vector from the Matrix.
     * @param index the index of the vector.
     * @return A view on the column of the Matrix.
     */
    inline ConstVectorView column(index index) const
    { return m_matrix[boost::indices[index][Range(0, m_nbrow)]]; }

    /**
     * @brief Return the number of valid row data.
     * @return the number of valid row.
     */
    inline size_type rows() const
    { return m_nbrow; }

    /**
     * @brief Return a vector from the Matrix.
     * @param index the index of the vector.
     * @return A view on the row of the Matrix.
     */
    inline VectorView row(index index)
    { return m_matrix[boost::indices[Range(0, m_nbcol)][index]]; }

    /**
     * @brief Return a constant vector from the Matrix.
     * @param index the index of the vector.
     * @return A constant view on the row of the Matrix.
     */
    inline ConstVectorView row(index index) const
    { return m_matrix[boost::indices[Range(0, m_nbcol)][index]]; }

    /**
     * @brief Return the number of column to add.
     * @return the number of column to add.
     */
    inline size_type resizeColumn() const
    { return m_stepcol; }

    /**
     * @brief Update the column to add factor.
     * @param colstep The number of column to add.
     */
    inline void setResizeColumn(size_type colstep)
    { m_stepcol = (colstep <= 0) ? m_stepcol : colstep; }

    /**
     * @brief Return the number of row to add.
     * @return the number of row to add.
     */
    inline size_type resizeRow() const
    { return m_steprow; }

    /**
     * @brief Update the row to add factor.
     * @param colrow The number of row to add.
     */
    inline void setResizeRow(size_type colrow)
    { m_steprow = (colrow <= 0) ? m_steprow : colrow; }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    /**
     * @brief Add a double into the matrix.
     * @param column The column.
     * @param row The row.
     * @param value The value of the double.
     */
    void addDouble(const size_type& column, const size_type& row,
                   const double& value)
    {
        add(column, row, new Double(value));
    }


    /**
     * @brief Add a Map at the end of the Set.
     * @param column The column.
     * @param row The row.
     * @return A reference to the newly allocated Map.
     */
    Map& addMap(const size_type& column, const size_type& row);

    /**
     * @brief Add a Matrix at the end of the Set.
     * @param column The column.
     * @param row The row.
     * @return A reference to the newly allocated Set.
     */
    Matrix& addMatrix(const size_type& column, const size_type& row);

    /**
     * @brief Get a Map from the specified index.
     * @param column The column.
     * @param row The row.
     * @return A Map.
     * @throw utils::ArgError if the index 'column' or 'row' are to big (in
     * debug mode) or if the value at (column, row) is null or is not a Set.
     */
    Map& getMap(const size_type& column, const size_type& row);

    /**
     * @brief Get a Matrix from the specified index.
     * @param column The column.
     * @param row The row.
     * @return A Matrix.
     * @throw utils::ArgError if the index 'column' or 'row' are to big (in
     * debug mode) or if the value at (column, row) is null or is not a Map.
     */
    Matrix& getMatrix(const size_type& column, const size_type& row);

    /**
     * @brief Get a constant Map from the specified index.
     * @param column The column.
     * @param row The row.
     * @return A Map.
     * @throw utils::ArgError if the index 'column' or 'row' are to big (in
     * debug mode) or if the value at (column, row) is null or is not an Matrix.
     */
    const Map& getMap(const size_type& column, const size_type& row) const;

    /**
     * @brief Get a constant Matrix from the specified index.
     * @param column The column.
     * @param row The row.
     * @return A Matrix.
     * @throw utils::ArgError if the index 'column' or 'row' are to big (in
     * debug mode) or if the value at (column, row) is null or is not an Matrix.
     */
    const Matrix& getMatrix(const size_type& column,
                            const size_type& row) const;

private:
    MatrixValue m_matrix; /// @brief to store the values.
    Indices m_indices;  /// @brief indices for the matrix.
    Extents m_extents; /// @brief to extents matrix.
    size_type m_nbcol;  /// @brief to store the column number.
    size_type m_nbrow;  /// @brief to store the row number.
    size_type m_stepcol; /// @brief the column when resize.
    size_type m_steprow; /// @brief the row when resize.
    size_type m_lastX; /// @brief the last columns set.
    size_type m_lastY; /// @brief the last row set.
};

/**
 * @brief A functor to test is a Value is a Matrix. To use with algorithms
 * of test.
 */
struct VLE_API IsMatrixValue
{
    bool operator()(const value::Value& value) const
    { return value.getType() == Value::MATRIX; }

    bool operator()(const value::Value* value) const
    { return value and value->getType() == Value::MATRIX; }
};

inline const Matrix& toMatrixValue(const Value& value)
{ return value.toMatrix(); }

inline const Matrix* toMatrixValue(const Value* value)
{ return value ? &value->toMatrix() : 0; }



inline ConstMatrixView toMatrix(const Value& value)
{ return value.toMatrix().value(); }


}} // namespace vle value

#endif
