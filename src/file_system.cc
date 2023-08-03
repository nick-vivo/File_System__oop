#include <file_system.h>


    file_system::file_system(): _capacity(0), _objects(nullptr), _size(0) {}

    file_system::file_system(const type_a capacity): _capacity(capacity), _objects(new object*[_capacity]), _size(0) 
    {
        for(type_a i = 0; i < this->_capacity; ++i)
        {
            this->_objects[i] = new object;
        }
    }

    file_system::file_system(const file_system& other): _capacity(other._capacity), _size(other._size), _objects(new object*[_capacity])
    {

        for(type_a i = 0; i < this->_capacity; ++i)
        {
            this->_objects[i] = new object;
        }

        for(type_a i = 0; i < this->_size; ++i)
        {
            *this->_objects[i] = *other._objects[i];
        }
    }

    file_system::~file_system()
    {
        if(_objects)
        {
            for(type_a i = 0; i < this->_capacity; ++i)
            {
                delete this->_objects[i];
            }
            delete[] _objects;
        }
    }

bool file_system::good_object(const object& el) const noexcept
{
    if(el.get_id() == el.get_id_p())
        return false;
    if(el.get_bytes() < 0)
        return false;
    for(type_a i = 0; i < this->_size; ++i)
    {
        if (this->_objects[i]->get_id() == el.get_id())
            return false;
        
        if(this->_objects[i]->get_id() == el.get_id_p())
        {
            if(this->_objects[i]->get_type() == File || Object)
                return false;
        }
        
        if (this->_objects[i]->get_id_p() == el.get_id_p())
        {
            if(this->_objects[i]->get_type() == el.get_type())
            {
                if(this->_objects[i]->get_name() == el.get_name())
                    return false;
            }
        }
    }
    return true;
}

void file_system::insert_c(type_a index, const object& in_object) noexcept(false)
{
    if(!good_object(in_object))
        throw std::runtime_error("bad name or id or id parrent or type parrent");
    
    if (index > this->_size || index < 0)
        throw std::runtime_error("index bad value");

    if (this->_size + 1 > this->_capacity)
    {
        file_system cp(*this);
        while(this->_size + 1 > this->_capacity)
        {
            this->_capacity += __CONST_FOR_CAPACITY;
        }

        if(this->_objects)
        {
            for(type_a i = 0 ;i < cp._capacity; ++i)
            {
                delete this->_objects[i];
            }
            delete this->_objects;
        }
        
        this->_objects = new object*[this->_capacity];
        for(type_a i = 0; i < this->_capacity; ++i)
        {
            this->_objects[i] = new object;
        }

        for(type_a i = 0; i < this->_size; ++i)
        {
            *this->_objects[i] = *cp._objects[i];
        }
    }

    for (type_a i = _size; i != index; --i)
        this->_objects[i]->swap( *_objects[i - 1] );
    ++this->_size;
    *_objects[index] = in_object;
}

void file_system::remove_one(type_a index)
{
    if (index >= this->_size || index < 0 || (this->_size - 1 == -1))
        throw std::runtime_error("Index not value or massive size = 0");

    --this->_size;
    for (type_a i = index; i < this->_size; ++i)
        this->_objects[i]->swap(*this->_objects[i + 1]);
}

void file_system::create_file(type_a index, mstd::string name, type_i id, type_i id_p, type_s bytes)
{
    this->insert_c(index, object(name, File, id, id_p, bytes));
    for(type_a i = 0; i < this->_size; ++i)
    {
        this->_objects[i]->set_bytes(size_obj(i));
    }
}

//Вычисление размера обьекта
type_s file_system::size_obj(type_a index)
{
    if (this->_objects[index]->get_type() == Cataloge)
    {
        type_s bytes = 0;
        for(type_a i = 0; i < this->_size; ++i)
        {
            if(this->_objects[index]->get_id() == this->_objects[i]->get_id_p())
            {
                if(this->_objects[i]->get_type() == Cataloge)
                {
                    bytes += size_obj(i);
                }
                else
                {
                    bytes += this->_objects[i]->get_bytes();
                }
            }
        }
        return bytes;
    }
    else
    {
        return this->_objects[index]->get_bytes();
    }
}

void file_system::create_cataloge(type_a index, mstd::string name, type_i id, type_i id_p)
{
    this->insert_c(index, object(name, Cataloge, id, id_p, 0));
    this->_objects[index]->set_bytes(size_obj(index));
}

void file_system::remove_all(type_a index)
{
    if (index >= this->_size || index < 0)
        throw std::runtime_error("Index not value or massive size = 0");
    for (type_a i = 0; i < this->_size;)
    {
        if (this->_objects[i]->get_id_p() == this->_objects[index]->get_id())
        {
            if(this->_objects[i]->get_type() == Cataloge)
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
        this->_objects[i]->set_bytes(size_obj(i));
    }

    if(this->_size < this->_capacity - __CONST_FOR_CAPACITY)
    {
        file_system cp(*this);
        while(this->_size < this->_capacity - __CONST_FOR_CAPACITY)
            --this->_capacity;
        this->~file_system();
        this->_objects = new object*[this->_capacity];
        for(type_a i = 0; i < this->_capacity; ++i)
        {
            this->_objects[i] = new object;
        }
        for (type_a i = 0; i < this->_size; ++i)
        {
            *this->_objects[i] = *cp._objects[i];
        }
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
