#ifndef __ITEM_HPP__

#include "../item.hpp"

template <typename T>
inline void my::swap(T &a, T &b)
{
    T c = a;
    a = b;
    b = c;
}
    
item::item(item &&other) : _type(other._type), _name(other._name), _id(other._id), _id_p(other._id_p), _bytes(other._bytes)
{
    other._type = Object;
    other._name = "Moved";
    other._id = 0;
    other._id_p = 0;
    other._bytes = 0;
}

item &item::operator=(const item &other) noexcept
{
    this->_type = other._type;
    this->_name = other._name;
    this->_id = other._id;
    this->_id_p = other._id_p;
    this->_bytes = other._bytes;
    return *this;
}

void item::operator=(item &&other) noexcept
{
    this->_type = other._type;
    this->_name = other._name;
    this->_id = other._id;
    this->_id_p = other._id_p;
    this->_bytes = other._bytes;

    other._type = Object;
    other._name = "Moved";
    other._id = 0;
    other._id_p = 0;
    other._bytes = 0;
}

inline void item::swap(item &other) noexcept
{
    this->_name.swap(other._name);
    my::swap<type_o>(this->_type, other._type);
    my::swap<type_i>(this->_id, other._id);
    my::swap<type_i>(this->_id_p, other._id_p);
    my::swap<type_s>(this->_bytes, other._bytes);
}

std::ostream& operator<<(std::ostream& stream, item& cont) noexcept
{
        if(cont.get_type() == Cataloge)
        {
            stream << "\nType: Cataloge";
        }
        else if(cont.get_type() == File)
        {
            stream << "Type: File";
        }
        else
        {
            stream << "Type: Object";
        }
        stream << "\nName: " << cont.get_name() << "\nID: " << cont.get_id() << "\nParrent: " << cont.get_id_p() << "\nBytes: " << cont.get_bytes() << std::endl;  
    return stream;
}

#endif