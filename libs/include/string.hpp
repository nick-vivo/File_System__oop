#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iostream>

namespace my
{

typedef unsigned long int size_t;

size_t strlen(const char *const str);

#define _STEP_STRING 5

class string
{
private:
    size_t _capacity;
    size_t _length;
    char* _data;
public:

    string();

    string(const char* const str);

    string(const string& other);

    string(string&& other);

    ~string();

    inline char& operator[](const size_t index) const noexcept;

    string& operator=(const string& other) noexcept;

    string& operator=(const char* const str) noexcept;

    void operator=(string&& other) noexcept;

    string operator+(const string& other) const noexcept;

    string& operator+=(const string& other) noexcept;

    string& operator+=(const char* const str) noexcept;

    bool operator!=(const string& other) const noexcept;
    bool operator!=(const char* const other) const noexcept;
    bool operator==(const string& other) const noexcept;
    bool operator==(const char* const other) const noexcept;

//1,2.Выписывает размер строки
    inline size_t size() const noexcept;

//3.Проверяет пуста ли строка (_length == 0)
    inline bool empty() const noexcept;

//4.Делает строку пустой, но размер в динамической памяти остается таким же(все заменяется на '\0')
    inline void clear() const noexcept;
    
//13. Возвращает указатель на массив символов, представляющий строку
    inline char const * c_str() const noexcept;

//14.Бросает исключение если index выходит за пределы
    inline char& at(size_t index) noexcept(false);
//capacity
    size_t capacity();
//Бета версия ресерва, закидывают исключение
    void reserve(size_t new_capacity) noexcept(false);
//Бета версия резайса, закидывают исключение
    void resize(size_t new_size) noexcept(false);
//swap
    void swap(string& other) noexcept(false);

friend my::string operator+(const char* const str_2, const my::string& str_1) noexcept;
friend my::string operator+( const my::string& str_1, const char* const str_2) noexcept;
};

my::string operator+(const char* const str_2, const my::string& str_1) noexcept;

my::string operator+(const my::string& str_1, const char* const str_2) noexcept;

std::istream& operator>>(std::istream &stream, my::string& str);

std::ostream& operator<<(std::ostream &stream, const my::string& str);
}

#endif