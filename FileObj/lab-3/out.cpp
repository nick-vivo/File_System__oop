#include <iostream>
#include "./menu/menu.cc"
#include "./include/source/container.cc"
#include "../../libs/include/source/string"

#define music std::cout<<'\a';
void playposition(char &key, int &now_button, bool &flag)
{
    switch(key)
    {
        case 'w':
        {
            music
            --now_button;
            if (now_button == -1)
            {
                now_button = 4;
            }
            break;
        }
        case 's':
        {
            music
            ++now_button;
            if (now_button == 5)
            {
                now_button = 0;
            }
            break;
        }
        case 'q':
        {
            music
            flag = 0;
        }

    }
}

int main()
{
    container cont;

    char key;
    my::menu menu_1(6);
    menu_1.create_button("1. Вставить элемент по индексу");
    menu_1.create_button("2. Удалить элемент по индексу");
    menu_1.create_button("3. Вывести список на экран");
    menu_1.create_button("4. Поиск по критерию(см...)");
    menu_1.create_button("5. Вывести путь");
    menu_1.create_button("Выход - q, Нажать - d");

    menu_1.settings();
    menu_1.hide_touch_on();
    menu_1.cursor_off();

    bool fl = true;

    type_a i;
    my::string name;
    type_i id;
    type_i id_parent;
    my::string type;
    type_s bytes;
    item* b;

    cont.create_cataloge(0, "Cataloge 1", 1, 1000);
    cont.create_cataloge(1, "Cataloge 2", 2, 1000);
    cont.create_cataloge(2, "Cataloge 3", 3, 2);

    cont.create_file(3, "File 1000", 10, 1000, 20);
    cont.create_file(4, "File 1", 11, 1, 20);
    cont.create_file(5, "File 2", 12, 2, 20);
    cont.create_file(6, "File 3", 13, 3, 20);

    while(fl)
    {
        menu_1.print(menu_1.now_button());
        key = getchar();

        playposition(key, menu_1.now_button(), fl);

        if (key == 'd' || key == ' ')
        {
            music
            menu_1.clear();
            menu_1.hide_touch_off();
            menu_1.cursor_on();
            gotoxy(0,0);
            switch(menu_1.now_button())
            {
                case 0:
                {     
                    std::cout << "Введи индекс обьекта(от 0 до " << menu_1.get_size() << "): ";
                    std::cin >> i;
                    std::cout << "\nВведи имя обьекта: ";
        
                    std::cin >> name;
                    std::cout << "\nВведи id обьекта: ";
                    std::cin >> id;
                    std::cout << "\nВведи id_parent обьекта: ";
                    std::cin >> id_parent;
                    std::cout << "\n\"file\" или \"cataloge\"?: ";
                    std::cin >> type;

                    if (type == "file")
                    {
                        std::cout << "\nРазмер в байтах:  ";
                        std::cin >> bytes;
                        cont.create_file(i, name, id, id_parent, bytes);
                    }
                    else if(type == "cataloge")
                    {
                        cont.create_cataloge(i, name, id, id_parent);
                    }
                    else
                    {
                        menu_1.clear();
                        std::cout << "\nОшибка в указании типа! Обьект не создался";
                        std::cout << std::endl << "Enter for contine...";
                        getchar();
                        getchar();
                    }
                    break;
                }
                case 1:
                {
                    std::cout << "Введи индекс обьекта(от 0 до " << cont.get_size() << "): ";
                    std::cin >> i;
                    cont.remove_all(i);
                    break;
                }
                case 2:
                {
                    cont.print(std::cout);
                    std::cout << std::endl << "Enter for contine...";
                    getchar();
                    getchar();
                    break;
                }
                case 3:
                {
                    std::cout << "Введи id для поиска: ";
                    std::cin >> id;
                    std::cout << std::endl; 
                    cont.search_id(id)->print(std::cout);
                    std::cout << std::endl << "\nEnter for contine...";
                    getchar();
                    getchar();
                    break;
                }
                case 4:
                {
                    std::cout << "Введи айди: ";
                    std::cin >> id;
                    std::cout << std::endl;
                    std::cout << cont.path(id);
                    std::cout << std::endl << "Enter for contine...";
                    getchar();
                    getchar();
                    break;
                }

            }
            menu_1.hide_touch_on();
            menu_1.cursor_off();
        } 
    }
    menu_1.clear();
    menu_1.hide_touch_off();
    menu_1.cursor_on();
    
}