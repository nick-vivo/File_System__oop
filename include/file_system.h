#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include <object.h>
#include <iostream>
#include <exception>
typedef int type_a;              //for array

#define __CONST_FOR_CAPACITY 5
class file_system
{
private:

type_a _capacity;
type_a _size;
object *_objects;

public:
    file_system();

//Сразу выделить память под capacity обьектов
    file_system(const type_a capacity);

    file_system(const file_system& other);

    ~file_system();

    inline type_a capacity() const noexcept
    {
        return this->_capacity;
    }

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
        throw std::runtime_error("not found");
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

std::ostream& operator<<(std::ostream& stream, file_system cont) noexcept;

#endif