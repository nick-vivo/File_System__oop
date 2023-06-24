#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include "./source/string"

namespace my
{
class exception
{
private:
    my::string _message;
public:
    exception() = delete;
    exception(const char* message);
    inline const char * what() const noexcept;
    ~exception() = default;
};

}
#endif