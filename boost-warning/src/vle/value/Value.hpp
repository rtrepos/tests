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

    class Value;
    class Double;
    class String;
    class Set;
    class Map;
    class Table;
    class Matrix;

    /**
     * @brief Virtual class to assign Value into Event object.
     */
    class VLE_API Value
    {
    public:
#ifndef NDEBUG
        static unsigned long int allocated;
        static unsigned long int deallocated;
#endif

        enum type {DOUBLE, SET, MAP, TABLE,
            MATRIX };

	/**
	 * @brief Default constructor.
	 * @code
         * Value* val = value::Integer::create(13);
         * Value* val2 = new value::Integer(13);
	 * @endcode
	 */
	Value()
        {
#ifndef NDEBUG
            Value::allocated++;
#endif
        }

        /**
         * @brief Copy constructor. In subclass, all datas are cloned.
         * @param value The value to clone;
         */
        Value(const Value& /* value */)
        {
#ifndef NDEBUG
            Value::allocated++;
#endif
        }

        /**
	 * @brief Nothing to delete.
	 */
	virtual ~Value()
        {
#ifndef NDEBUG
            Value::deallocated++;
#endif
        }

        ///
        //// Abstract functions
        ///

	/**
	 * @brief Pure virtual clone function.
	 * @return Clone of instantiate object.
	 */
        virtual Value* clone() const = 0;

	/**
	 * @brief Transform value into a simple std::string for text file.
	 * @return std::string representation of Value.
	 */
	virtual void writeFile(std::ostream& /* out */) const = 0;

	/**
	 * @brief Transform value into a simple std::string.
	 * @return std::string representation of Value.
	 */
	virtual void writeString(std::ostream& /* out */) const = 0;

	/**
	 * @brief Transform value into XML structure.
	 * @return std::string representation of XML structure of Value.
	 */
	virtual void writeXml(std::ostream& /* out */) const = 0;

	/**
	 * @brief Return the type of value. The type is one of the 'type'
	 * enumeration ie. BOOL, INTEGER, DOUBLE, STRING, SET, MAP.
	 * @return the type of value object.
	 */
	virtual Value::type getType() const = 0;

        ///
        ////
        ///

        /**
         * @brief Build a file representation of this class. This function
         * call the virtual function Value::writeString to build the string.
         * @return A string representation of this class.
         */
        std::string writeToFile() const;

        /**
         * @brief Build a string representation of this class. This function
         * call the virtual function Value::writeString to build the string.
         * @return A string representation of this class.
         */
        std::string writeToString() const;

        /**
         * @brief Build an xml representation of this class. This function
         * call the virtual function Value::writeString to build the string.
         * @return A string representation of this class.
         */
        std::string writeToXml() const;

	inline bool isDouble() const
	{ return getType() == Value::DOUBLE; }

	inline bool isSet() const
	{ return getType() == Value::SET; }

	inline bool isMap() const
	{ return getType() == Value::MAP; }


	inline bool isTable() const
	{ return getType() == Value::TABLE; }

	inline bool isMatrix() const
	{ return getType() == Value::MATRIX; }

        const Double& toDouble() const;
        const Set& toSet() const;
        const Map& toMap() const;
        const Table& toTable() const;
        const Matrix& toMatrix() const;

        /**
         * @brief Check if the Value is a composite value, ie., a Map, a Set or
         * a Matrix.
         * @param val The Value to check.
         * @return True if the Value is a Map, a Set or a Matrix.
         */
        inline static bool isComposite(const Value* val)
        {
            switch (val->getType()) {
            case Value::MAP:
            case Value::SET:
            case Value::MATRIX:
                return true;
            default:
                return false;
            }
        }



    private:
        Value& operator=(const Value& /* value */) { return *this; }
    };


}} // namespace vle

#endif
