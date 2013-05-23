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


#ifndef VLE_VPZ_STRUCTURES_HPP
#define VLE_VPZ_STRUCTURES_HPP

#include <vle/vpz/Base.hpp>
#include <vle/DllDefines.hpp>

namespace vle { namespace vpz {

    /**
     * @brief The Structure, only used by the SaxParser.
     */
    class VLE_API Structures : public Base
    {
    public:
        /**
         * @brief Build a new Structures.
         */
        Structures()
        {}

        /**
         * @brief Nothing to output.
         */
        virtual void write(std::ostream& /* out */) const
        {}

        /**
         * @brief Nothing to delete.
         */
        virtual ~Structures()
        {}

        /**
         * @brief Get the type of this class.
         * @return STRUCTURES.
         */
        virtual Base::type getType() const
        { return VLE_VPZ_STRUCTURES; }
    };

}} // namespace vle vpz

#endif
