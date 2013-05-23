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

    Matrix()
        : m_matrix(m_extents[1][1])
    {

    }

    virtual ~Matrix()
    {

    }

    void resize()
    {
      m_matrix.resize(m_extents[1][1]);
    }









private:
    MatrixValue m_matrix; /// @brief to store the values.
    Extents m_extents; /// @brief to extents matrix.

};


}} // namespace vle value

#endif
