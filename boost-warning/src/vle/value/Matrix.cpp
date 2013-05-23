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


#include <vle/value/Matrix.hpp>

namespace vle { namespace value {

Matrix::Matrix(index columns, index rows, index columnmax, index rowmax, index
               resizeColumns, index resizeRows)
    : m_matrix(m_extents[columnmax][rowmax]), m_nbcol(columns), m_nbrow(rows),
    m_stepcol(resizeColumns), m_steprow(resizeRows), m_lastX(0), m_lastY(0)
{
    if (columns > columnmax) {
        throw 1;
    }

    if (rows > rowmax) {
        throw 1;
    }
}



void Matrix::resize(const size_type& columns, const size_type& rows)
{
    m_matrix.resize(m_extents[columns][rows]);
}



}} // namespace vle value

