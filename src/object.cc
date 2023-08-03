#include <object.h>
    
object &object::operator=(const object &other) noexcept
{
    this->_name = other._name;
    this->_id = other._id;
    this->_id_p = other._id_p;
    this->_bytes = other._bytes;
    return *this;
}

void file::print(std::ostream& stream) const
{
    stream << "\nType: File" << "\nName: " << this->get_name().c_str() << "\nID: " << this->get_id() 
    << "\nParrent: " << this->get_id_p() << "\nBytes: " << this->get_bytes();
}

std::unique_ptr<object> file::clone() const
{
    std::unique_ptr<object> cp(new file(this->_name, this->_id, this->_id_p, this->_bytes));
    return cp;
}

void cataloge::print(std::ostream& stream) const
{
    stream << "\nType: Cataloge" << "\nName: " << this->get_name().c_str() << "\nID: " << this->get_id() 
    << "\nParrent: " << this->get_id_p() << "\nBytes: " << this->get_bytes();
}

std::unique_ptr<object> cataloge::clone() const
{
    std::unique_ptr<object> cp(new cataloge(this->_name, this->_id, this->_id_p, this->_bytes));
    return cp;
}

