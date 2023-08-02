#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <string.hpp> //библиотека string, своя
#include <iostream>
#include <tools.h>

typedef int type_i;                 //id
typedef unsigned short type_s;      //size
enum type_o{Object, Cataloge, File};  //obj

class object
{
private:

type_o _type;
mstd::string _name;
type_i _id;
type_i _id_p;
type_s _bytes;

public:

    object() = default;
    object(const object& other) = default;
    object(object&& other);
    object(mstd::string name, type_o type, type_i id, type_i id_p, type_s bytes): _name(name), _type(type), _id(id), _id_p(id_p), _bytes(bytes) {}
    object(const char* name, type_o type, type_i id, type_i id_p, type_s bytes): _name(name), _type(type), _id(id), _id_p(id_p), _bytes(bytes) {}
    ~object() = default;

//Operators
    object& operator=(const object& other) noexcept;

    void operator=(object&& other) noexcept;

//Setters

    inline void set_type(type_o type) noexcept
    {
        this->_type = type;
    }

    inline void set_name(mstd::string name) noexcept
    {
        this->_name = name;
    }

    inline void set_id(type_i id) noexcept
    {
        this->_id = id;
    }

    inline void set_id_p(type_i id_p) noexcept
    {
        this->_id_p = id_p;
    }

    inline void set_bytes(type_s bytes) noexcept
    {
        this->_bytes = bytes;
    }

//Getters

    inline type_o get_type() const noexcept
    {
        return this->_type;
    }

    inline mstd::string get_name() const noexcept
    {
        return this->_name;
    }

    inline type_i get_id() const noexcept
    {
        return this->_id;
    }

    inline type_i get_id_p() const noexcept
    {
        return this->_id_p;
    }

    inline type_s get_bytes() const noexcept
    {
        return this->_bytes;
    }

    inline void swap(object& other) noexcept;

    bool operator==(const object& other) const noexcept
    {
        return (this->_bytes == other._bytes) && (this->_id == other._id) && (this->_id_p == other._id_p) && (this->_name == other._name) && (this->_type == other._type);
    }

    bool operator!=(const object& other) const noexcept
    {
        return !this->operator==(other);
    }
};

std::ostream& operator<<(std::ostream& stream, object& cont) noexcept;
#endif