#include <object.h>
    
object::object(object &&other) : _type(other._type), _name(other._name), _id(other._id), _id_p(other._id_p), _bytes(other._bytes)
{
    other._type = Object;
    other._name = "Moved";
    other._id = 0;
    other._id_p = 0;
    other._bytes = 0;
}

object &object::operator=(const object &other) noexcept
{
    this->_type = other._type;
    this->_name = other._name;
    this->_id = other._id;
    this->_id_p = other._id_p;
    this->_bytes = other._bytes;
    return *this;
}

void object::operator=(object &&other) noexcept
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

std::ostream& operator<<(std::ostream& stream, object& cont) noexcept
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
        stream << "\nName: " << cont.get_name().c_str() << "\nID: " << cont.get_id() << "\nParrent: " << cont.get_id_p() << "\nBytes: " << cont.get_bytes() << std::endl;  
    return stream;
}
