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


#ifndef VLE_VALUE_MAP_HPP
#define VLE_VALUE_MAP_HPP 1

#include <vle/value/Value.hpp>
#include <vle/value/Double.hpp>
#include <vle/DllDefines.hpp>
#include <map>

namespace vle { namespace value {

/**
 * @brief Define a list of Value in a dictionnary.
 */
typedef std::map < std::string, Value* > MapValue;

/**
 * @brief Map Value a container to a pair of std::string, Value pointer. The
 * map can not contains null data.
 */
class VLE_API Map : public Value
{
public:
    typedef MapValue::size_type size_type;
    typedef MapValue::iterator iterator;
    typedef MapValue::const_iterator const_iterator;
    typedef MapValue::value_type value_type;

    /**
     * @brief Build a Map object with an empty MapValue.
     */
    Map()
        : m_value()
    {}

    /**
     * @brief Copy constructor. All the Value are cloned.
     * @param value The value to copy.
     */
    Map(const Map& value);

    /**
     * @brief Delete all Value in the Set.
     */
    virtual ~Map()
    { clear(); }

    /**
     * @brief Build a new Map.
     * @return A new Map allocated.
     */
    static Map* create()
    { return new Map(); }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    /**
     * @brief Clone the current Map and recursively for all Value in the
     * MapValue.
     * @return A new Map.
     */
    virtual Value* clone() const
    { return new Map(*this); }

    /**
     * @brief Get the type of this class.
     * @return Value::MAP.
     */
    virtual Value::type getType() const
    { return Value::MAP; }

    /**
     * @brief Push all Value from the MapValue, recursively and colon
     * separated.
     * @code
     * (key,value), key2,123) (key3, true)
     * @endcode
     * @param out The output stream.
     */
    virtual void writeFile(std::ostream& out) const;

    /**
     * @brief Push all VAlue from the MapValue, recursively and colon
     * separated.
     * @code
     * (key,value), key2,123) (key3, true)
     * @param out The output stream.
     */
    virtual void writeString(std::ostream& out) const;

    /**
     * @brief Push all Value from the MapValue recursively in an XML
     * representation.
     * @code
     * <map>
     *  <key name="key1">
     *   <string>value</string>
     *  </key>
     *  <key name="key2">
     *   <integer>123</integer>
     *  </key>
     *  <key name="key3">
     *   <boolean>true</boolean>
     *  </key>
     * </map>
     * @endcode
     * @param out The output stream.
     */
    virtual void writeXml(std::ostream& out) const;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    /**
     * @brief Add a value into the map. Be carrefull, the data is not
     * cloned. Don't delete buffer after. If a value already exist with the
     * same key, it will be deleted and replaced.
     * @param name the name of Value to add.
     * @param value the Value to add.
     * @throw utils::ArgError if the value is null.
     */
    void add(const std::string& name, Value* value)
    {
        set(name, value);
    }

    /**
     * @brief Add a value into the map. The data is cloned. If a value already
     * eixsts with the same name it will be replaced.
     * @param name the name of Value to add.
     * @param value the Value to add.
     * @throw utils::ArgError if the value is null.
     */
    void add(const std::string& name, const Value* value)
    {
        set(name, value);
    }

    /**
     * @brief Add a value into the map. The data is cloned. If a value already
     * eixsts with the same name it will be replaced.
     * @param name the name of Value to add.
     * @param value the Value to add.
     */
    void add(const std::string& name, const Value& value)
    {
        set(name, value);
    }

    /**
     * @brief Set a value into the map. Be carrefull, the data is not
     * cloned. Don't delete buffer after. If a value already exist with the
     * same key, it will be deleted and replaced.
     * @param name the name of Value to Set.
     * @param value the Value to Set.
     * @throw utils::ArgError if the value is null.
     */
    void set(const std::string& name, Value* value)
    {
        iterator it = find(name);

        if (it != end()) {
            delete it->second;
            it->second = value;
        } else {
            m_value.insert(std::make_pair(name, value));
        }
    }

    /**
     * @brief Set a value into the map. The data is cloned. If a value already
     * eixsts with the same name it will be replaced.
     * @param name the name of Value to Set.
     * @param value the Value to Set.
     * @throw utils::ArgError if the value is null.
     */
    void set(const std::string& name, const Value* value)
    {
        Value* clone = (value) ? value->clone() : (value::Value*)0;
        iterator it = find(name);

        if (it != end()) {
            delete it->second;
            it->second = clone;
        } else {
            m_value.insert(std::make_pair(name, clone));
        }
    }

    /**
     * @brief Set a value into the map. The data is cloned. If a value already
     * eixsts with the same name it will be replaced.
     * @param name the name of Value to Set.
     * @param value the Value to Set.
     */
    void set(const std::string& name, const Value& value)
    {
        iterator it = find(name);

        if (it != end()) {
            delete it->second;
            it->second = value.clone();
        } else {
            m_value.insert(std::make_pair(name, value.clone()));
        }
    }

    /**
     * @brief Test if the map have already a Value with specified name.
     * @param name the name to find into value.
     * @return true if Value exist, false otherwise.
     */
    inline bool exist(const std::string& name) const
    { return find(name) != end(); }

    /**
     * @brief Get a Value from the map specified by his name.
     * @param name The name of the value.
     * @return A reference to the specified value or a newly builded.
     * @throw utils::ArgError if the key does not exist.
     */
    Value* operator[](const std::string& name);

    /**
     * @brief Get a Value from the map specified by his name.
     * @param name The name of the value.
     * @return A constant reference to the specified value or a newly
     * builded.
     * @throw utils::ArgError if the key does not exist.
     */
    const Value* operator[](const std::string& name) const;

    /**
     * @brief Get the Value objet for specified name.
     * @param name The name of the Value in the map.
     * @return a reference to the Value.
     * @throw utils::ArgError if value don't exist.
     */
    const Value* get(const std::string& name) const
    {
        const_iterator it = find(name);

        if (it == end()) {
            throw 1;
        }

        return (*it).second;
    }

    /**
     * @brief Get the Value objet for specified name.
     * @param name The name of the Value in the map.
     * @return a reference to the Value.
     * @throw utils::ArgError if value don't exist.
     */
    Value* get(const std::string& name)
    {
        iterator it = find(name);

        if (it == end()) {
            throw 1;
        }

        return (*it).second;
    }

    /**
     * @brief Get the Value object for the specified name. If the name
     * exist, the pair key value is destroyed and the value is returned.
     * @param name The name of the Value in the map.
     * @return the pointer to the Value.
     * @throw utils::ArgError if value don't exist.
     */
    Value* give(const std::string& name);

    /**
     * @brief Get an access to the std::map.
     * @return a reference to the set::map.
     */
    inline MapValue& value()
    { return m_value; }

    /**
     * @brief Get a constant access to the std::map.
     * @return a reference to the const std::map.
     */
    inline const MapValue& value() const
    { return m_value; }

    /**
     * @brief Delete all value from map.
     */
    void clear();

    /**
     * @brief Return true if the value::Map does not contain any element.
     * @return True if empty, false otherwise.
     */
    inline bool empty() const
    { return m_value.empty(); }

    /**
     * Return the number of element in the @c std::map.
     *
     * @return An integer [0..MAX_SIZE_T];
     */
    inline size_type size() const
    { return m_value.size(); }

    /**
     * @brief Get the first constant iterator from Map.
     * @return the first iterator.
     */
    inline const_iterator begin() const
    { return m_value.begin(); }

    /**
     * @brief Get the last constant iterator from Map.
     * @return the last iterator.
     */
    inline const_iterator end() const
    { return m_value.end(); }

    /**
     * @brief Get the first constant iterator from Map.
     * @return the first iterator.
     */
    inline iterator begin()
    { return m_value.begin(); }

    /**
     * @brief Get the last constant iterator from Map.
     * @return the last iterator.
     */
    inline iterator end()
    { return m_value.end(); }

    /**
     * @brief Find an constant iterator into the value::Map using a key.
     * @param key The key of the std::pair < key, value > to find.
     * @return A constant iterator or end() if key is not found.
     */
    inline const_iterator find(const std::string& key) const
    { return m_value.find(key); }

    /**
     * @brief Find an iterator into the value::Map using a key.
     * @param key The key of the std::pair < key, value > to find.
     * @return An iterator or end() if key is not found.
     */
    inline iterator find(const std::string& key)
    { return m_value.find(key); }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    /**
     * @brief Set a double to the value of the specified key. If the
     * key does not exist, it will be build.
     * @param name The key of the map.
     * @param value The value of the key.
     */
    void addDouble(const std::string& name, const double& value)
    {
        add(name, new Double(value));
    }

    /**
     * @brief Add a Map into the Map.
     * @param name The key name.
     * @return A reference to the newly allocated Map.
     */
    Map& addMap(const std::string& name);

    /**
     * @brief Add a Matrix into the Map.
     * @param name The key name.
     * @return A reference to the newly allocated Matrix.
     */
    Matrix& addMatrix(const std::string& name);

    /**
     * @brief Get the Map value objet from specified name.
     * @param name The name of the Value in the map.
     * @return a reference to the Value.
     * @throw utils::ArgError if type is not Value::Map or value do not
     * exist.
     */
    Map& getMap(const std::string& name);

    /**
     * @brief Get the Matrix value from specified key.
     * @param name The name of the Value in the Map.
     * @return A referece to the Matrix.
     * @throw utils::ArgError if type is not Value::add or value do not
     * exist.
     */
    Matrix& getMatrix(const std::string& name);

    /**
     * @brief Get the Map value objet from specified name.
     * @param name The name of the Value in the map.
     * @return a reference to the Value.
     * @throw utils::ArgError if type is not Value::Map or value do not
     * exist.
     */
    const Map& getMap(const std::string& name) const;

    /**
     * @brief Get the Matrix value from specified key.
     * @param name The name of the Value in the Map.
     * @return A referece to the Matrix.
     * @throw utils::ArgError if type is not Value::add or value do not
     * exist.
     */
    const Matrix& getMatrix(const std::string& name) const;

private:
    MapValue m_value;

    Value* getPointer(const std::string& name);

    const Value* getPointer(const std::string& name) const;
};

inline const Map& toMapValue(const Value& value)
{ return value.toMap(); }

inline const Map* toMapValue(const Value* value)
{ return value ? &value->toMap() : 0; }


inline const MapValue& toMap(const Value& value)
{ return value.toMap().value(); }



}} // namespace vle value

#endif
