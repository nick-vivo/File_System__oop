#ifndef __MENU_HPP__
#define __MENU_HPP__

#include "../../../libs/include/source/string"
#include "../../../libs/include/source/exception"
#include <iostream>
#include <stdio.h>
//Для работы с терминалом
#include <sys/ioctl.h>
#include <unistd.h>
#include <termio.h>

//EXAMPLE FOR TERMINAL

#define ESC "\033"

//Format text
#define RESET 		0
#define BRIGHT 		1
#define DIM			2
#define UNDERSCORE	3
#define BLINK		4
#define REVERSE		5
#define HIDDEN		6

//Foreground Colours (text)

#define F_BLACK 	30
#define F_RED		31
#define F_GREEN		32
#define F_YELLOW	33
#define F_BLUE		34
#define F_MAGENTA 	35
#define F_CYAN		36
#define F_WHITE		37

//Background Colours
#define B_BLACK 	40
#define B_RED		41
#define B_GREEN		42
#define B_YELLOW	44
#define B_BLUE		44
#define B_MAGENTA 	45
#define B_CYAN		46
#define B_WHITE		47

#define gotoxy(x,y)		printf(ESC "[%d;%dH", y, x);
#define visible_cursor() printf(ESC "[?251");
//Set Display Attribute Mode	<ESC>[{attr1};...;{attrn}m
#define resetcolor() printf(ESC "[0m")
#define set_display_atrib(color) 	printf(ESC "[%dm",color)

//END EXAMPLE

namespace my
{
template<typename T>
class point
{
protected:
T _x, _y;
public:

    point(): _x(0), _y(0) {}
    point(point& other): _x(other._x), _y(other._y) {}
    point(point&& other): _x(other._x), _y(other._y)
    {
        other._x = 0;
        other._y = 0;
    };
    point(T x, T y): _x(x), _y(y) {}
    
    point& operator=(point& other)
    {
        this->_x = other._x;
        this->_y = other._y;
    }

    void set(T x, T y) noexcept
    {
        this->_x = x;
        this->_y = y;
    }

    void set_x(T x) noexcept
    {
        this->_x = x;
    }

    void set_y(T y) noexcept
    {
        this->_y = y;
    }
    
    T get_x() const noexcept
    {
        return this->_x;
    }

    T get_y() const noexcept
    {
        return this->_y;
    }

    T& x() noexcept
    {
        return this->_x;
    }

    T& y() noexcept
    {
        return this->_y;
    }
};

typedef unsigned short type_p; // position
class button
{
protected:
    my::string name;
    point<type_p> _position;
public:
    button() {};

    button(my::button& other): name(other.name), _position(other._position) {}

    button(my::string name, point<type_p> position): name(name), _position(position) {}
    
    my::string get_name() const noexcept
    {
        return name;
    }

    point<type_p> get_position() noexcept
    {
        return _position;
    }

    point<type_p>& position() noexcept
    {
        return _position;
    }

    void set_name(my::string name) noexcept
    {
        this->name = name;
    }

    type_p& x()
    {
        return _position.x();
    }

    type_p& y()
    {
        return _position.y();
    }
};

//Перемещает кнопку по внутренним координатам и выписывает её
std::ostream& operator<<(std::ostream& stream, button butt)
{
    gotoxy(butt.get_position().get_x(),butt.get_position().get_y());
    stream << butt.get_name();
    return stream;
}

typedef unsigned short type_c; //count
class menu
{
private:
    type_c _capacity;
    button* _buttons;
    winsize _win;
    type_c size;
    termios _orig_term, _new_term;
    int _now_button;
public:

    menu() = delete;

    menu& operator=(menu& other) = delete;

    menu(type_c capacity): _capacity(capacity), _buttons(new button[this->_capacity]), size(0), _now_button(0)
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &(this->_win));
        for(type_c i = 0; i < _capacity; ++i)
        {
            this->_buttons[i].y() = this->_win.ws_row * (i + 1) / _capacity ;
        }
    }

    ~menu()
    {
        if(this->_buttons)
            delete[] this->_buttons;
    }

    type_c get_size()
    {
        return this->size;
    }

    int& now_button()
    {
        if(this->_now_button >= this->size || this->_now_button < 0)
            throw my::exception("now_button is fail");
        return this->_now_button;
    }

    void create_button(my::string name)
    {
        if(size + 1 > this->_capacity)
        {
            throw my::exception("array is full");
        }
        this->_buttons[size].set_name(name);
        this->_buttons[size].x() = this->_win.ws_col/2 - _buttons[this->size].get_name().size()/2;
        ++size;
    }

    void print(type_c index_button_on)
    {
        std::cout << "\e[1J";

        if(index_button_on >= size || index_button_on < 0)
        {
            throw my::exception("bad index");
        }

        for(type_c i = 0; i < this->size; ++i)
        {
            gotoxy(this->_buttons[i].get_position().get_x(),this->_buttons[i].get_position().get_y());
            if(index_button_on == i)
            {
                set_display_atrib(47);
                set_display_atrib(30);
                gotoxy(this->_buttons[i].get_position().get_x()-3,this->_buttons[i].get_position().get_y());
                std::cout << ">> ";
            }
            std::cout << this->_buttons[i].get_name();
            if(index_button_on == i)
            {
                resetcolor();
            }
        }
    }

    void settings()
    {
        tcgetattr(STDIN_FILENO, &_orig_term);
        menu::_new_term = menu::_orig_term;
        cfmakeraw(&_new_term);
    }
    void hide_touch_on()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &_new_term);        
    }
    void hide_touch_off()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &_orig_term);
    }

    static void cursor_off()
    {
        std::cout << "\e[?25l";
    }

    static void cursor_on()
    {
        std::cout << "\e[?25h";
    }

    static void clear()
    {
        std::cout << "\e[1J";
        std::cout << "\e[0;0H";
    }

};

}

#endif