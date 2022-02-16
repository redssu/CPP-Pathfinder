#include <iostream>
#include <windows.h>
#include "Color.hpp"

void Color::set ( color foreground, color background ) {
    SetConsoleTextAttribute( hConsole, ( background << 4 ) | foreground );
}

void Color::reset () {
    SetConsoleTextAttribute( hConsole, originalAttributes );
}

void Color::Initialize () {
    // ustaw domyślne wartości atrybutów konsoli
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( hConsole, &csbi );
    originalAttributes = csbi.wAttributes;
}

int Color::originalAttributes = 0;
void* Color::hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
