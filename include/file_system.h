#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include <object.h>
#include <iostream>
#include <exception>
#define _SIZE_ARRAY_STATIC 25
typedef unsigned short type_a;              //for array

class container
{
private:

object _objects[_SIZE_ARRAY_STATIC];
type_a _size;

public:
    container(): _size(0) {}

    ~container() = default;

    inline type_a get_size() const noexcept
    {
        return this->_size;
    }

    inline object operator[](type_a index) const noexcept(false)
    {        
        if(index >= this->_size || index < 0)
            throw std::runtime_error("index bad value");
        return _objects[index];
    }
//Получить обьект по индексу в режиме чтения
    inline object at_r(type_a index) const noexcept(false)
    {
        if(index >= this->_size || index < 0)
            throw std::runtime_error("index bad value");
        return _objects[index];
    }

private:
    void insert_m(type_a index, object& in_object) noexcept(false);

    void insert_c(type_a index, const object& in_object) noexcept(false);

    bool good_object(const object& el) const noexcept;
    
    void remove_one(type_a index);

//Вычисление размера обьекта системы
    type_s size_obj(type_a index);
public:
//Создать обьект типа файл в контейнере
    void create_file(type_a index, mstd::string name, type_i id, type_i id_p, type_s bytes);

//Создать обьект типа каталог в контейнере
    void create_cataloge(type_a index, mstd::string name, type_i id, type_i id_p);

//Для удаления папки целиком или файла
    void remove_all(type_a index);

//Узнать размер обьекта системы
    type_s get_bytes(const type_a index) const noexcept(false)
    {
        if(index >= this->_size || index < 0)
        {
            throw std::runtime_error("index bad value");
        }
        return this->_objects[index].get_bytes();
    }

//Поиск в наборе обьекта с укзанным id
    object search_id(const type_i id) const
    {
        for(type_a i = 0; i < this->_size; ++i)
        {
            if (this->_objects[i].get_id() == id)
                return this->_objects[i];
        }
        throw std::runtime_error("index bad value");
    }
//Построение абсолютного пути обьекта с указанным индефикатором
    mstd::string path(const type_i id)
    {
        try
        {
            return path(search_id(id).get_id_p()) + "/" + search_id(id).get_name();
        }
        catch(const std::runtime_error& e)
        {
            return "~";
        }
    }
};

std::ostream& operator<<(std::ostream& stream, container cont) noexcept;

#endif