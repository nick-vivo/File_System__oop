#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include "./source/exception"

namespace my

{
typedef unsigned int size_c; 

template<typename T>
class shared_ptr
{
private:
T* _data;
size_c* count;
public:
    shared_ptr(): _data(nullptr), _count(new size_c(0)) {}

    shared_ptr(shared_ptr& other): _data(other._data), count(other._data)
    {
        ++*count;
    }

    shared_ptr(T* data): _data(data)

    ~shared_ptr()
    {
        if( *count > 1 )
        {
            --*count;
        }
        else if( *count == 1 )
        {
            delete this->_data;
            delete this->count;
        }
    }
};
}
#endif