#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class ConsoleColor {
private:
    HANDLE hConsole;
    WORD defaultAttributes;

    ConsoleColor();
public:
    static ConsoleColor& GetInstance();
    ConsoleColor(const ConsoleColor&) = delete;
    ConsoleColor& operator=(const ConsoleColor&) = delete;

    void SetColor(WORD color);
    void ResetColor();
    void red();
    void green();
    void yellow();
    void blue();
    void magenta();
    void cyan();
    void white();
    void gray();
};