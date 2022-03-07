#include <iostream>
#include <vector>
#include "lib/Console/Console.hpp"
#include "lib/MapPoint/MapPoint.hpp"
#include "lib/Map/Map.hpp"
#include "lib/PathFinder/PathFinder.hpp"
#include "lib/MapLoader/MapLoader.hpp"
#include "lib/PathDrawer/PathDrawer.hpp"
#include "lib/PathFinderException/PathFinderException.hpp"

int main () {
    Console::Initialize();

    std::string fileName;

    std::cout << "Podaj nazwę pliku do wczytania (wraz z rozszerzeniem): ";
    std::cin >> fileName;

    try {
        MapLoader mapLoader = MapLoader( fileName );
        mapLoader.Tokenize();
        Map map = mapLoader.Interpret();

        PathFinder pathFinder = PathFinder( &map );

        std::vector<MapPoint*> path = pathFinder.FindPath();

        PathDrawer::DisplayMapWithPath( &map, path ); 
    }
    catch ( PathFinderException exception ) {
        Console::SetColor( BRIGHT_WHITE, BRIGHT_RED );
        std::cout << "Wystąpił błąd:";

        Console::SetColor( BRIGHT_RED, BLACK );
        std::cout << " " << exception.GetFunctionName();
        
        Console::SetColor( RED, BLACK );
        std::cout << ": " << exception.GetMessage();

        Console::ResetColor();
    }
    
    return 0;
}