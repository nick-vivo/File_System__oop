#ifndef __CONTAINER_HPP__
#include "../container.hpp"

bool container::good_item(const item& el) const noexcept
{
    if(el.get_id() == el.get_id_p())
        return false;
        
    if(el.get_bytes() < 0)
        return false;
        
    for(type_a i = 0; i < this->_size; ++i)
    {
        if (this->_items[i].get_id() == el.get_id())
            return false;
        
        if(this->_items[i].get_id() == el.get_id_p())
        {
            if(this->_items[i].get_type() == File || Object)
                return false;
        }
        
        if (this->_items[i].get_id_p() == el.get_id_p())
        {
            if(this->_items[i].get_type() == el.get_type())
            {
                if(this->_items[i].get_name() == el.get_name())
                    return false;
            }
        }
    }
    return true;
}

void container::insert_m(type_a index, item& in_item) noexcept(false)
{
    if(!good_item(in_item))
        throw my::exception("bad name or id or id parrent or type parrent");

    if (index > this->_size || index < 0 || this->_size + 1 > _SIZE_ARRAY_STATIC)
        throw my::exception("index bad value or array is full");
    
    for (type_a i = _size; i != index; --i)
        _items[i].swap(_items[i - 1]);
    ++this->_size;
    _items[index] = std::move(in_item);
}

void container::insert_c(type_a index, const item& in_item) noexcept(false)
{
    if(!good_item(in_item))
        throw my::exception("bad name or id or id parrent or type parrent");
    
    if (index > this->_size || index < 0 || this->_size + 1 > _SIZE_ARRAY_STATIC)
        throw my::exception("index bad value or array is full");

    for (type_a i = _size; i != index; --i)
        _items[i].swap(_items[i - 1]);
    
    ++this->_size;
    _items[index] = in_item;
}

void container::remove_one(type_a index)
{
    if (index >= this->_size || index < 0 || (this->_size - 1 == -1))
        throw my::exception("Index not value or massive size = 0");

    --this->_size;
    for (type_a i = index; i < this->_size; ++i)
        this->_items[i].swap(this->_items[i + 1]);
}

void container::create_file(type_a index, my::string name, type_i id, type_i id_p, type_s bytes)
{
    this->insert_c(index, item(name, File, id, id_p, bytes));
    for(type_a i = 0; i < this->_size; ++i)
    {
        this->_items[i].set_bytes(size_obj(i));
    }
}

//Вычисление размера обьекта
type_s container::size_obj(type_a index)
{
    if (this->_items[index].get_type() == Cataloge)
    {
        type_s bytes = 0;
        for(type_a i = 0; i < this->_size; ++i)
        {
            if(this->_items[index].get_id() == this->_items[i].get_id_p())
            {
                if(this->_items[i].get_type() == Cataloge)
                {
                    bytes += size_obj(i);
                }
                else
                {
                    bytes += this->_items[i].get_bytes();
                }
            }
        }
        return bytes;
    }
    else
    {
        return this->_items[index].get_bytes();
    }
}

void container::create_cataloge(type_a index, my::string name, type_i id, type_i id_p)
{
    this->insert_c(index, item(name, Cataloge, id, id_p, 0));
    this->_items[index].set_bytes(size_obj(index));
}

void container::remove_all(type_a index)
{
    if (index >= this->_size || index < 0)
        throw my::exception("Index not value or massive size = 0");
    for (type_a i = 0; i < this->_size;)
    {
        if (this->_items[i].get_id_p() == this->_items[index].get_id())
        {
            if(this->_items[i].get_type() == Cataloge)
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
        this->_items[i].set_bytes(size_obj(i));
    }
}

std::ostream& operator<<(std::ostream& stream, container cont) noexcept
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
        stream << "\nName: " << cont[i].get_name() << "\nID: " << cont[i].get_id() 
        << "\nParrent: " << cont[i].get_id_p() << "\nBytes: " << cont[i].get_bytes() 
        << "\nPATH:" << cont.path(cont[i].get_id()) << std::endl;  
    }
    return stream;
}

#endif
