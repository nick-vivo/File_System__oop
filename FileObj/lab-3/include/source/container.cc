#ifndef __CONTAINER_HPP__
#include "../container.hpp"

    container::container(const container& other)
    {
        for(type_a i = 0; i < other._vector.size(); ++i)
        {
            *this->_vector[i] = *other._vector[i]->clone();
        }
    }

bool container::good_item(const item& el) const noexcept
{
    if(el.get_id() == el.get_id_p())
        return false;
    if(el.get_bytes() < 0)
        return false;
    for(type_a i = 0; i < this->_vector.size(); ++i)
    {
        if (this->_vector[i]->get_id() == el.get_id())
            return false;
        
        if(this->_vector[i]->get_id() == el.get_id_p())
        {
            if(this->_vector[i]->is_file())
                return false;
        }
        
        if (this->_vector[i]->get_id_p() == el.get_id_p())
        {
            if(this->_vector[i]->is_file() == el.is_file())
            {
                if(this->_vector[i]->get_name() == el.get_name())
                    return false;
            }
        }
    }
    return true;
}

void container::insert_c(type_a index, const item& in_item) noexcept(false)
{
    if(!good_item(in_item))
        throw my::exception("bad name or id or id parrent or type parrent");
    
    if (index > this->_vector.size() || index < 0)
        throw my::exception("index bad value");

    this->_vector.insert( _vector.begin() + index, in_item.clone() );
}

void container::remove_one(type_a index)
{
    if (index >= this->_vector.size() || index < 0 || (this->_vector.size() - 1 == -1))
        throw my::exception("Index not value or massive size = 0");

    this->_vector.erase(this->_vector.begin() + index);
}

void container::create_file(type_a index, my::string name, type_i id, type_i id_p, type_s bytes)
{
    this->insert_c(index, file(name, id, id_p, bytes));
    for(type_a i = 0; i < this->_vector.size(); ++i)
    {
        this->_vector[i]->set_bytes(size_obj(i));
    }
}

//Вычисление размера обьекта
type_s container::size_obj(type_a index)
{
    if (!this->_vector[index]->is_file())
    {
        type_s bytes = 0;
        for(type_a i = 0; i < this->_vector.size(); ++i)
        {
            if(this->_vector[index]->get_id() == this->_vector[i]->get_id_p())
            {
                if(!this->_vector[i]->is_file())
                {
                    bytes += size_obj(i);
                }
                else
                {
                    bytes += this->_vector[i]->get_bytes();
                }
            }
        }
        return bytes;
    }
    else
    {
        return this->_vector[index]->get_bytes();
    }
}

void container::create_cataloge(type_a index, my::string name, type_i id, type_i id_p)
{
    this->insert_c(index, cataloge(name, id, id_p, 0));
    this->_vector[index]->set_bytes(size_obj(index));
}

void container::remove_all(type_a index)
{
    if (index >= this->_vector.size() || index < 0)
        throw my::exception("Index not value or massive size = 0");
    for (type_a i = 0; i < this->_vector.size();)
    {
        if (this->_vector[i]->get_id_p() == this->_vector[index]->get_id())
        {
            if(!this->_vector[i]->is_file())
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
    for(type_a i = 0; i < this->_vector.size(); ++i)
    {
        this->_vector[i]->set_bytes(size_obj(i));
    }
    
} 

std::ostream& operator<<(std::ostream& stream, container cont) noexcept
{
    for(type_a i = 0; i < cont.get_size(); ++i)
    {
        stream << "\nindex: " << i;
        
        cont[i]->print(stream);
        stream <<std::endl <<  cont.path(i).c_str();
    }

    return stream;
}

#endif