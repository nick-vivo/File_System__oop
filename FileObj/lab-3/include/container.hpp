#ifndef __CONTAINER_HPP__
#define __CONTAINER_HPP__

#include "./source/item.cc"
#include "../../../libs/include/source/exception" //библиотека исключений, своя
#include <iostream>
#include <vector>
#include <memory>

typedef int type_a;              //for array

class container
{
private:

std::vector< std::unique_ptr<item> > _vector;

public:
    container() = default;

    container(const container& other);

    ~container() = default;

    inline type_a get_size() const noexcept
    {
        return this->_vector.size();
    }

    inline std::unique_ptr<item> operator[](type_a index) const noexcept(false)
    {        
        if(index >= this->_vector.size() || index < 0)
            throw my::exception("index bad value");
        return _vector[index]->clone();
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
        if(index >= this->_vector.size() || index < 0)
        {
            throw my::exception("index bad value");
        }
        return this->_vector[index]->get_bytes();
    }

//Поиск в наборе обьекта с укзанным id
    std::unique_ptr<item> search_id(const type_i id) const
    {
        for(type_a i = 0; i < this->_vector.size(); ++i)
        {
            if (this->_vector[i]->get_id() == id)
                return this->_vector[i]->clone();
        }
        throw my::exception("not found");
    }

//Построение абсолютного пути обьекта с указанным индефикатором
    my::string path(const type_i id)
    {
        try
        {
            return path(search_id(id)->get_id_p()) + "/" + search_id(id)->get_name();
        }
        catch(const my::exception& e)
        {
            return "~";
        }
    }

    void print(std::ostream& stream) const 
    {
        for(type_a i = 0; i < this->_vector.size(); ++i)
        {
            stream << "\nindex: " << i;
            this->_vector[i]->print(stream);
            stream << std::endl;
        }
    }
};

std::ostream& operator<<(std::ostream& stream, container cont) noexcept;

#endif