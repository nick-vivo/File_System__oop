#include <file_system.h>

bool file_system::good_object(const object& el) const noexcept
{
    if(el.get_id() == el.get_id_p())
        return false;
        
    if(el.get_bytes() < 0)
        return false;
        
    for(type_a i = 0; i < this->_size; ++i)
    {
        if (this->_objects[i].get_id() == el.get_id())
            return false;
        
        if(this->_objects[i].get_id() == el.get_id_p())
        {
            if(this->_objects[i].get_type() == File || Object)
                return false;
        }
        
        if (this->_objects[i].get_id_p() == el.get_id_p())
        {
            if(this->_objects[i].get_type() == el.get_type())
            {
                if(this->_objects[i].get_name() == el.get_name())
                    return false;
            }
        }
    }
    return true;
}

void file_system::insert_m(type_a index, object& in_object) noexcept(false)
{
    if(!good_object(in_object))
        throw std::runtime_error("bad name or id or id parrent or type parrent");

    if (index > this->_size || index < 0 || this->_size + 1 > _SIZE_ARRAY_STATIC)
        throw std::runtime_error("index bad value or array is full");
    
    for (type_a i = _size; i != index; --i)
        _objects[i].swap(_objects[i - 1]);
    ++this->_size;
    _objects[index] = std::move(in_object);
}

void file_system::insert_c(type_a index, const object& in_object) noexcept(false)
{
    if(!good_object(in_object))
        throw std::runtime_error("bad name or id or id parrent or type parrent");
    
    if (index > this->_size || index < 0 || this->_size + 1 > _SIZE_ARRAY_STATIC)
        throw std::runtime_error("index bad value or array is full");

    for (type_a i = _size; i != index; --i)
        _objects[i].swap(_objects[i - 1]);
    
    ++this->_size;
    _objects[index] = in_object;
}

void file_system::remove_one(type_a index)
{
    if (index >= this->_size || index < 0 || (this->_size - 1 == -1))
        throw std::runtime_error("Index not value or massive size = 0");

    --this->_size;
    for (type_a i = index; i < this->_size; ++i)
        this->_objects[i].swap(this->_objects[i + 1]);
}

void file_system::create_file(type_a index, mstd::string name, type_i id, type_i id_p, type_s bytes)
{
    this->insert_c(index, object(name, File, id, id_p, bytes));
    for(type_a i = 0; i < this->_size; ++i)
    {
        this->_objects[i].set_bytes(size_obj(i));
    }
}

//Вычисление размера обьекта
type_s file_system::size_obj(type_a index)
{
    if (this->_objects[index].get_type() == Cataloge)
    {
        type_s bytes = 0;
        for(type_a i = 0; i < this->_size; ++i)
        {
            if(this->_objects[index].get_id() == this->_objects[i].get_id_p())
            {
                if(this->_objects[i].get_type() == Cataloge)
                {
                    bytes += size_obj(i);
                }
                else
                {
                    bytes += this->_objects[i].get_bytes();
                }
            }
        }
        return bytes;
    }
    else
    {
        return this->_objects[index].get_bytes();
    }
}

void file_system::create_cataloge(type_a index, mstd::string name, type_i id, type_i id_p)
{
    this->insert_c(index, object(name, Cataloge, id, id_p, 0));
    this->_objects[index].set_bytes(size_obj(index));
}

void file_system::remove_all(type_a index)
{
    if (index >= this->_size || index < 0)
        throw std::runtime_error("Index not value or massive size = 0");
    for (type_a i = 0; i < this->_size;)
    {
        if (this->_objects[i].get_id_p() == this->_objects[index].get_id())
        {
            if(this->_objects[i].get_type() == Cataloge)
            {
                this->remove_all(i);
            }
            else
            {
                this->remove_one(i);
            }
        }
        else
            ++i;
    }
    this->remove_one(index);
    for(type_a i = 0; i < this->_size; ++i)
    {
        this->_objects[i].set_bytes(size_obj(i));
    }
}

std::ostream& operator<<(std::ostream& stream, file_system cont) noexcept
{
    for(type_a i = 0; i < cont.get_size(); ++i)
    {
        stream << "\nindex: " << i;
        if(cont[i].get_type() == Cataloge)
        {
            stream << "\nType: Cataloge";
        }
        else if(cont[i].get_type() == File)
        {
            stream << "\nType: File";
        }
        else
        {
            stream << "\nType: Object";
        }
        stream << "\nName: " << cont[i].get_name().c_str() << "\nID: " << cont[i].get_id() 
        << "\nParrent: " << cont[i].get_id_p() << "\nBytes: " << cont[i].get_bytes() 
        << "\nPATH:" << cont.path(cont[i].get_id()).c_str() << std::endl;  
    }
    return stream;
}

