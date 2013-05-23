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

    Matrix(index columns, index rows, index columnmax, index rowmax,
           index resizeColumns, index resizeRow);


    virtual ~Matrix()
    {

    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *



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


}} // namespace vle value

#endif
