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


#include <vle/value/Value.hpp>
#include <vle/value/Double.hpp>
#include <vle/value/Matrix.hpp>
#include <sstream>

namespace vle { namespace value {

#ifndef NDEBUG
unsigned long int Value::allocated = 0;
unsigned long int Value::deallocated = 0;
#endif

std::string Value::writeToFile() const
{
    std::ostringstream out;
    writeFile(out);
    return out.str();
}

std::string Value::writeToString() const
{
    std::ostringstream out;
    writeString(out);
    return out.str();
}

std::string Value::writeToXml() const
{
    std::ostringstream out;
    writeXml(out);
    return out.str();
}


const Double& Value::toDouble() const
{
    if (not isDouble()) {
        throw 1;
    }
    return static_cast < const Double& >(*this);
}





const Matrix& Value::toMatrix() const
{
    if (not isMatrix()) {
        throw 1;
    }
    return static_cast < const Matrix& >(*this);
}


}} // namespace vle value

