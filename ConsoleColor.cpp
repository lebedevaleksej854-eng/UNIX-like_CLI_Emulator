#include "ConsoleColor.h"

ConsoleColor::ConsoleColor() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    defaultAttributes = consoleInfo.wAttributes;
}
ConsoleColor& ConsoleColor::GetInstance() {
    static ConsoleColor instance;
    return instance;
}
void ConsoleColor::SetColor(WORD color) {
    SetConsoleTextAttribute(hConsole, color);
}
void ConsoleColor::ResetColor() {
    SetConsoleTextAttribute(hConsole, defaultAttributes);
}
void ConsoleColor::red() {
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void ConsoleColor::green() {
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void ConsoleColor::yellow() {
    SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void ConsoleColor::blue() {
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleColor::magenta() {
    SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleColor::cyan() {
    SetColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleColor::white() {
    SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void ConsoleColor::gray() {
    SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}