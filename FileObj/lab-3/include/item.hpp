#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include "../../../libs/include/source/string" //библиотека string, своя
#include <iostream>
#include <memory>

typedef int type_i;                 //id
typedef unsigned short type_s;      //size

namespace my
{
template<typename T>
inline void swap(T &a, T &b);
}

class item
{
protected:

my::string _name;
type_i _id;
type_i _id_p;
type_s _bytes;

public:

    item() = default;
    item(const item& other) = default;
    item(my::string name, type_i id, type_i id_p, type_s bytes): _name(name), _id(id), _id_p(id_p), _bytes(bytes) {}
    item(const char* name, type_i id, type_i id_p, type_s bytes): _name(name), _id(id), _id_p(id_p), _bytes(bytes) {}
    virtual ~item() = default;

//Operators
    item& operator=(const item& other) noexcept;

//Setters

    inline void set_name(my::string name) noexcept
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

    inline my::string get_name() const noexcept
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

    inline void swap(item& other) noexcept;

    bool operator==(const item& other) const noexcept
    {
        return (this->_bytes == other._bytes) && (this->_id == other._id) && (this->_id_p == other._id_p) && (this->_name == other._name);
    }

    bool operator!=(const item& other) const noexcept
    {
        return !this->operator==(other);
    }

    virtual void print(std::ostream& stream) const = 0;

    virtual inline bool is_file() const noexcept = 0;

    virtual std::unique_ptr<item> clone() const  = 0;

};

class file: public item
{
public:
    file() = default;
    file(my::string name, type_i id, type_i id_p, type_s bytes): item(name, id, id_p, bytes) {}
    file(const char* name, type_i id, type_i id_p, type_s bytes): item(name, id, id_p, bytes) {}

    void print(std::ostream& stream) const override;
    inline bool is_file() const noexcept override;
    std::unique_ptr<item> clone() const override;
};

class cataloge: public item
{
public:
    cataloge() = default;
    cataloge(my::string name, type_i id, type_i id_p, type_s bytes): item(name, id, id_p, bytes) {}
    cataloge(const char* name, type_i id, type_i id_p, type_s bytes): item(name, id, id_p, bytes) {}

    void print(std::ostream& stream) const override;
    inline bool is_file() const noexcept override;
    std::unique_ptr<item> clone() const override;
};

#endif