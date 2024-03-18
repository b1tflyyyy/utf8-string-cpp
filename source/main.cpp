#include <iostream>
#include <chrono>
#include <utf8_string.hpp>

int main()
{

#if 1
    utf8::ustring str{ "привет" };

    str.replace_char("s", 0);
    str.replace_char("g", 0);
    str.replace_char("п", 0);
    str.replace_char("s", 3);
    str.replace_char("g", 4);
    str.replace_char("п", 3);
    str.replace_char("\xf0\x92\x8d\x87", 2);
    str.replace_char("g", 2);
    str.replace_char("مرحبا", 2);

    std::cout << str << '\n';
#endif

    return 0;
}