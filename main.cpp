#include <iostream>
#include "lib/Console/Console.hpp"
#include "lib/MapPoint/MapPoint.hpp"
#include "lib/Map/Map.hpp"
#include "lib/PathFinder/PathFinder.hpp"
#include "lib/MapLoader/MapLoader.hpp"
#include "lib/PathFinderException/PathFinderException.hpp"

int main () {
    Console::Initialize();

    try {
        MapLoader mapLoader = MapLoader( "map.txt" );
        mapLoader.Tokenize();
        mapLoader.Interpret();
    }
    catch ( PathFinderException exception ) {
        Console::SetColor( BRIGHT_WHITE, BRIGHT_RED );
        std::cout << "Wystapil blad:";

        Console::SetColor( BRIGHT_RED, BLACK );
        std::cout << " " << exception.GetFunctionName();
        
        Console::SetColor( RED, BLACK );
        std::cout << ": " << exception.GetMessage();

        Console::ResetColor();
    }
    
    return 0;
}