#include <windows.h>
#include "Console.hpp"

void Console::SetColor ( Color foreground, Color background ) {
    SetConsoleTextAttribute( hConsole, ( background << 4 ) | foreground );
}

void Console::ResetColor () {
    SetConsoleTextAttribute( hConsole, originalAttributes );
}

void Console::Initialize () {
    // ustaw domyślne wartości atrybutów konsoli
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( hConsole, &csbi );
    originalAttributes = csbi.wAttributes;
}

int Console::originalAttributes = 0;
void* Console::hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
