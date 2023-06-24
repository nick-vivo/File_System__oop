#include <iostream>
#include "./include/source/container.cc"

int main()
{
    container cont;

    cont.create_file(0, "Nikita", 100, 0, 20);
    cont.create_cataloge(0, "Photo", 1, 0);
    cont.create_file(1, "program.cpp", 11, 1, 20);
    cont.create_file(2, "Pictures", 12, 1, 20);
    cont.create_cataloge(3, "Pictures", 2, 1);
    cont.create_file(4, "file", 21, 2, 20);

    std::cout << cont;
}