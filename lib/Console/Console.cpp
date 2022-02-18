#include <windows.h>
#include <string>
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

Color Console::GetColor ( std::string colorName ) {
    if ( colorName == "BLACK" ) { return BLACK; }
    if ( colorName == "BLUE" ) { return BLUE; }
    if ( colorName == "GREEN" ) { return GREEN; }
    if ( colorName == "CYAN" ) { return CYAN; }
    if ( colorName == "RED" ) { return RED; }
    if ( colorName == "PURPLE" ) { return PURPLE; }
    if ( colorName == "YELLOW" ) { return YELLOW; }
    if ( colorName == "WHITE" ) { return WHITE; }
    if ( colorName == "BRIGHT_BLACK" ) { return BRIGHT_BLACK; }
    if ( colorName == "BRIGHT_BLUE" ) { return BRIGHT_BLUE; }
    if ( colorName == "BRIGHT_GREEN" ) { return BRIGHT_GREEN; }
    if ( colorName == "BRIGHT_CYAN" ) { return BRIGHT_CYAN; }
    if ( colorName == "BRIGHT_RED" ) { return BRIGHT_RED; }
    if ( colorName == "BRIGHT_PURPLE" ) { return BRIGHT_PURPLE; }
    if ( colorName == "BRIGHT_YELLOW" ) { return BRIGHT_YELLOW; }
    if ( colorName == "BRIGHT_WHITE" ) { return BRIGHT_WHITE; }

    throw Console::GetColor( "Console::GetColor: Nie znaleziono koloru z taką nazwą." );
}

int Console::originalAttributes = 0;
void* Console::hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
