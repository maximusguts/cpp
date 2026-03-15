#include <iostream>
#include <windows.h>

int main() {
    // Устанавливаем кодировку UTF-8 для консоли Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "C++ setup is complete!" << std::endl;
    std::cout << "Привет, Владислав! Все работает корректно." << std::endl;

    return 0;
}