#ifndef __CONTAINER_HPP__
#define __CONTAINER_HPP__

#include "./source/item.cc"
#include "../../../libs/include/source/exception" //библиотека исключений, своя
#include <iostream>

typedef int type_a;              //for array

#define __CONST_FOR_CAPACITY 5
class container
{
private:

type_a _capacity;
type_a _size;
item **_items;

public:
    container();

//Сразу выделить память под capacity обьектов
    container(const type_a capacity);

    container(const container& other);

    ~container();

    inline type_a capacity() const noexcept
    {
        return this->_capacity;
    }

    inline type_a get_size() const noexcept
    {
        return this->_size;
    }

    inline item operator[](type_a index) const noexcept(false)
    {        
        if(index >= this->_size || index < 0)
            throw my::exception("index bad value");
        return *_items[index];
    }
//Получить обьект по индексу в режиме чтения
    inline item at_r(type_a index) const noexcept(false)
    {
        if(index >= this->_size || index < 0)
            throw my::exception("index bad value");
        return *_items[index];
    }

private:

    void insert_c(type_a index, const item& in_item) noexcept(false);

    bool good_item(const item& el) const noexcept;
    
    void remove_one(type_a index);

//Вычисление размера обьекта системы
    type_s size_obj(type_a index);
public:
//Создать обьект типа файл в контейнере
    void create_file(type_a index, my::string name, type_i id, type_i id_p, type_s bytes);

//Создать обьект типа каталог в контейнере
    void create_cataloge(type_a index, my::string name, type_i id, type_i id_p);

//Для удаления папки целиком или файла
    void remove_all(type_a index);

//Узнать размер обьекта системы
    type_s get_bytes(const type_a index) const noexcept(false)
    {
        if(index >= this->_size || index < 0)
        {
            throw my::exception("index bad value");
        }
        return this->_items[index]->get_bytes();
    }

//Поиск в наборе обьекта с укзанным id
    item search_id(const type_i id) const
    {
        for(type_a i = 0; i < this->_size; ++i)
        {
            if (this->_items[i]->get_id() == id)
                return *this->_items[i];
        }
        throw my::exception("not found");
    }
//Построение абсолютного пути обьекта с указанным индефикатором
    my::string path(const type_i id)
    {
        try
        {
            return path(search_id(id).get_id_p()) + "/" + search_id(id).get_name();
        }
        catch(const my::exception& e)
        {
            return "~";
        }
    }
};

std::ostream& operator<<(std::ostream& stream, container cont) noexcept;

#endif