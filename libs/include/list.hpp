#ifndef __LIST_HPP__
#define __LIST_HPP__
#include "./source/exception"

namespace my
{
typedef int type_s; 

template<typename T>
class list
{
private:

template<typename N>
class node
{
public:
    node *_pNext;
    N _data;
    
    node(N data = N(), node* pNext= nullptr): _data(data), _pNext(pNext) {}
};

node<T> *_head;
type_s _size;

public:

    list(): _head(nullptr), _size(0) {}
    ~list();

    void push_back(T data) noexcept;

    inline type_s size() const noexcept
    {
        return this->_size;
    }

    inline T& operator[](const type_s index) noexcept;

    void pop_front();

    void push_front(T data);

    void clear() 
    {
        this->~list();
    }

    void insert(T data, type_s index);
    void removeAt(type_s index);

};

}

#endif