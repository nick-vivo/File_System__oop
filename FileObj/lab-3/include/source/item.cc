#ifndef __ITEM_HPP__

#include "../item.hpp"

template <typename T>
inline void my::swap(T &a, T &b)
{
    T c = a;
    a = b;
    b = c;
}
    
item &item::operator=(const item &other) noexcept
{
    this->_name = other._name;
    this->_id = other._id;
    this->_id_p = other._id_p;
    this->_bytes = other._bytes;
    return *this;
}

inline void item::swap(item &other) noexcept
{
    this->_name.swap(other._name);
    my::swap<type_i>(this->_id, other._id);
    my::swap<type_i>(this->_id_p, other._id_p);
    my::swap<type_s>(this->_bytes, other._bytes);
}

inline bool file::is_file() const noexcept
{
    return true;
}

void file::print(std::ostream& stream) const
{
    stream << "\nType: File" << "\nName: " << this->get_name() << "\nID: " << this->get_id() 
    << "\nParrent: " << this->get_id_p() << "\nBytes: " << this->get_bytes();
}

std::unique_ptr<item> file::clone() const
{
    std::unique_ptr<item> cp(new file(this->_name, this->_id, this->_id_p, this->_bytes));
    return cp;
}

inline bool cataloge::is_file() const noexcept
{
    return false;
}

void cataloge::print(std::ostream& stream) const
{
    stream << "\nType: Cataloge" << "\nName: " << this->get_name() << "\nID: " << this->get_id() 
    << "\nParrent: " << this->get_id_p() << "\nBytes: " << this->get_bytes();
}

std::unique_ptr<item> cataloge::clone() const
{
    std::unique_ptr<item> cp(new cataloge(this->_name, this->_id, this->_id_p, this->_bytes));
    return cp;
}

#endif