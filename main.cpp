#include <iostream>
#include "lib/Console/Console.hpp"
#include "lib/MapPoint/MapPoint.hpp"
#include "lib/Map/Map.hpp"
#include "lib/PathFinder/PathFinder.hpp"
#include "lib/MapLoader/MapLoader.hpp"

int main () {
    try {
        Console::Initialize();

        MapLoader mapLoader = MapLoader( "map.txt" );
        mapLoader.Tokenize();

        mapLoader.PrintTokens();
    }
    catch ( std::string error ) {
        std::cout << "BLAD: " << error << std::endl;
    }
    
    return 0;
}