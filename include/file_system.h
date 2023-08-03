#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include <object.h>
#include <iostream>
#include <exception>
#include <memory>
#include <vector>

typedef int type_a;              //for array

class file_system
{
private:

std::vector< std::unique_ptr<object> > _vector;

public:
    file_system() = default;

    file_system(const file_system& other);

    ~file_system() = default;

    inline type_a get_size() const noexcept
    {
        return this->_vector.size();
    }

    inline std::unique_ptr<object> operator[](type_a index) const noexcept(false)
    {        
        if(index >= this->_vector.size() || index < 0)
            throw std::runtime_error("index bad value");
        return _vector[index]->clone();
    }

private:

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
        if(index >= this->_vector.size() || index < 0)
        {
            throw std::runtime_error("index bad value");
        }
        return this->_vector[index]->get_bytes();
    }

//Поиск в наборе обьекта с укзанным id
    std::unique_ptr<object> search_id(const type_i id) const
    {
        for(type_a i = 0; i < this->_vector.size(); ++i)
        {
            if (this->_vector[i]->get_id() == id)
                return this->_vector[i]->clone();
        }
        throw std::runtime_error("not found");
    }

//Построение абсолютного пути обьекта с указанным индефикатором
    mstd::string path(const type_i id)
    {
        try
        {
            return path(search_id(id)->get_id_p()) + "/" + search_id(id)->get_name();
        }
        catch(const std::runtime_error& e)
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

std::ostream& operator<<(std::ostream& stream, file_system cont) noexcept;

#endif