#include <iostream>
#include "lib/Console/Console.hpp"
#include "lib/MapPoint/MapPoint.hpp"
#include "lib/Map/Map.hpp"
#include "lib/PathFinder/PathFinder.hpp"
#include "lib/MapLoader/MapLoader.hpp"

int main () {
    Console::Initialize();

    try {
        MapLoader mapLoader = MapLoader( "map.txt" );
        mapLoader.Tokenize();
        mapLoader.Interpret();
    }
    catch ( std::string error ) {
        Console::SetColor( BRIGHT_WHITE, BRIGHT_RED );
        std::cout << "Wystapil blad:";
        Console::SetColor( BRIGHT_RED );
        std::cout << " " << error << "\n";
        Console::ResetColor();
    }
    catch ( const char* error ) {
        Console::SetColor( BRIGHT_WHITE, BRIGHT_RED );
        std::cout << "Wystapil blad:";
        Console::SetColor( BRIGHT_RED );
        std::cout << " " << error << "\n";
        Console::ResetColor();
    }
    
    return 0;
}