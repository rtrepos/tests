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


#include <vle/value/Set.hpp>
#include <vle/value/Map.hpp>
#include <vle/value/Matrix.hpp>
#include <vle/value/Double.hpp>
#include <boost/checked_delete.hpp>
#include <fstream>
#include <sstream>

namespace vle { namespace value {

Set::Set(const Set& setfactory)
    : Value(setfactory)
{
    m_value.resize(setfactory.size());

}

void Set::writeFile(std::ostream& out) const
{
    for (const_iterator it = m_value.begin(); it != m_value.end(); ++it) {
        if (it != m_value.begin()) {
            out << ",";
        }
        if (*it) {
            (*it)->writeFile(out);
        } else {
            out << "NA";
        }
    }
}

void Set::writeString(std::ostream& out) const
{
    out << "(";

    for (const_iterator it = m_value.begin(); it != m_value.end(); ++it) {
        if (it != m_value.begin()) {
            out << ",";
        }
        if (*it) {
            (*it)->writeString(out);
        } else {
            out << "NA";
        }
    }

    out << ")";
}

void Set::writeXml(std::ostream& out) const
{
    out << "<set>";

    for (const_iterator it = m_value.begin(); it != m_value.end(); ++it) {
        if (*it) {
            (*it)->writeXml(out);
        } else {
            out << "<null />";
        }
    }

    out << "</set>";
}

Value* Set::give(const size_type& i)
{
    if (i >= size()) {
        throw 1;
    }

    Value* result = m_value[i];
    m_value[i] = 0;
    return result;
}

void Set::del(const size_type i)
{
    if (i >= size()) {
        throw 1;
    }

    delete m_value[i];
    m_value[i] = 0;
    m_value.erase(begin() + i);
}

void Set::clear()
{
    std::for_each(begin(), end(), boost::checked_deleter < Value >());

    m_value.clear();
}

Set& Set::addSet()
{
    Set* value = new Set();

    m_value.push_back(value);

    return *value;
}

Map& Set::addMap()
{
    Map* value = new Map();

    m_value.push_back(value);

    return *value;
}

Matrix& Set::addMatrix()
{
    Matrix* value = new Matrix();

    m_value.push_back(value);

    return *value;
}

}} // namespace vle value
