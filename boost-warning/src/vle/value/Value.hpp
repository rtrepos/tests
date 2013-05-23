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


#ifndef VLE_VALUE_VALUE_HPP
#define VLE_VALUE_VALUE_HPP 1

#include <vle/version.hpp>
#include <vle/DllDefines.hpp>
#include <ostream>

namespace vle { namespace value {


    /**
     * @brief Virtual class to assign Value into Event object.
     */
    class VLE_API Value
    {
    public:


	/**
	 * @brief Default constructor.
	 * @code
         * Value* val = value::Integer::create(13);
         * Value* val2 = new value::Integer(13);
	 * @endcode
	 */
	Value()
        {
        }
        /**
	 * @brief Nothing to delete.
	 */
	virtual ~Value()
        {
        }

        ///
        //// Abstract functions
        ///

    };


}} // namespace vle

#endif
