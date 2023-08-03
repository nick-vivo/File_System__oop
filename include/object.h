#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <string.hpp> //библиотека string, своя
#include <iostream>
#include <tools.h>
#include <memory>

typedef int type_i;                 //id
typedef unsigned short type_s;      //size

class object
{
protected:

mstd::string _name;
type_i _id;
type_i _id_p;
type_s _bytes;

public:

    object() = default;
    object(const object& other) = default;
    object(mstd::string name, type_i id, type_i id_p, type_s bytes): _name(name), _id(id), _id_p(id_p), _bytes(bytes) {}
    object(const char* name, type_i id, type_i id_p, type_s bytes): _name(name), _id(id), _id_p(id_p), _bytes(bytes) {}
    virtual ~object() = default;

//Operators
    object& operator=(const object& other) noexcept;

//Setters

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

    inline void swap(object& other) noexcept
    {
        this->_name.swap(other._name);
        mstd::swap<type_i>(this->_id, other._id);
        mstd::swap<type_i>(this->_id_p, other._id_p);
        mstd::swap<type_s>(this->_bytes, other._bytes);
    }
    bool operator==(const object& other) const noexcept
    {
        return (this->_bytes == other._bytes) && (this->_id == other._id) && (this->_id_p == other._id_p) && (this->_name == other._name);
    }

    bool operator!=(const object& other) const noexcept
    {
        return !this->operator==(other);
    }

    virtual void print(std::ostream& stream) const = 0;

    virtual inline bool is_file() const noexcept = 0;

    virtual std::unique_ptr<object> clone() const  = 0;

};

class file: public object
{
public:
    file() = default;
    file(mstd::string name, type_i id, type_i id_p, type_s bytes): object(name, id, id_p, bytes) {}
    file(const char* name, type_i id, type_i id_p, type_s bytes): object(name, id, id_p, bytes) {}

    void print(std::ostream& stream) const override;
    inline bool is_file() const noexcept override;
    std::unique_ptr<object> clone() const override;
};

inline bool file::is_file() const noexcept
{
    return true;
}

class cataloge: public object
{
public:
    cataloge() = default;
    cataloge(mstd::string name, type_i id, type_i id_p, type_s bytes): object(name, id, id_p, bytes) {}
    cataloge(const char* name, type_i id, type_i id_p, type_s bytes): object(name, id, id_p, bytes) {}

    void print(std::ostream& stream) const override;
    inline bool is_file() const noexcept override;
    std::unique_ptr<object> clone() const override;
};

inline bool cataloge::is_file() const noexcept
{
    return false;
}


#endif