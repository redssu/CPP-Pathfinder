#include <vector>
#include "../MapPoint/MapPoint.hpp"
#include "../Map/Map.hpp"
#include "../Console/Console.hpp"
#include "../PathFinder/PathFinder.hpp"
#include "PathDrawer.hpp"

void PathDrawer::DisplayMapWithPath ( Map* map, std::vector<MapPoint*> path ) {
    int pathSize = path.size();

    int mapWidth = map->Width();
    int mapHeight = map->Height();

    for ( int y = 0; y < mapHeight; y++ ) {
        for ( int x = 0; x < mapWidth; x++ ) {
            MapPoint* mapPoint = map->GetMapPoint( x, y );

            int pathPointIndex = 0;
            bool isStartOrEndPoint = mapPoint->Symbol() == 'E' || mapPoint->Symbol() == 'S';
            bool isPathPoint = !isStartOrEndPoint && IsPointInPath( path, mapPoint, &pathPointIndex );

            Color fgColor = isPathPoint ? RED : mapPoint->FGColor();
            Color bgColor = mapPoint->BGColor();

            std::string symbol = 
                isPathPoint 
                ? GetCharacterForPoint( path, pathPointIndex ) 
                : ( std::string( 1, mapPoint->Symbol() ) );

            Console::SetColor( fgColor, bgColor );
            std::cout << symbol;
            Console::ResetColor();
        }

        std::cout << std::endl;
    }
}

std::string PathDrawer::GetCharacterForPoint ( std::vector<MapPoint*> path, int pathPointIndex ) {
    int pathSize = path.size();

    if ( PathFinder::ALLOW_DIAGONAL_NEIGHBOURS ) {
        return "*";
    }

    MapPoint* point = path[ pathPointIndex ];
    MapPoint* prev = pathPointIndex > 0 ? path[ pathPointIndex - 1 ] : nullptr;
    MapPoint* next = pathPointIndex < pathSize - 1 ? path[ pathPointIndex + 1 ] : nullptr;    

    int relativeHorizontalPrev = GetRelativeHorizontalPosition( point, prev );
    int relativeHorizontalNext = GetRelativeHorizontalPosition( point, next );

    int relativeVerticalPrev = GetRelativeVerticalPosition( point, prev );
    int relativeVerticalNext = GetRelativeVerticalPosition( point, next );

    bool isSomethingUp = relativeVerticalPrev == -1 || relativeVerticalNext == -1;
    bool isSomethingDown = relativeVerticalPrev == 1 || relativeVerticalNext == 1;
    bool isSomethingLeft = relativeHorizontalPrev == -1 || relativeHorizontalNext == -1;
    bool isSomethingRight = relativeHorizontalPrev == 1 || relativeHorizontalNext == 1;

    if ( isSomethingUp && isSomethingLeft ) {
        return u8"╯";
    }

    if ( isSomethingUp && isSomethingRight ) {
        return u8"╰";
    }

    if ( isSomethingDown && isSomethingLeft ) {
        return u8"╮";
    }

    if ( isSomethingDown && isSomethingRight ) {
        return u8"╭";
    }

    if ( isSomethingUp && isSomethingDown ) {
        return u8"│";
    }

    if ( isSomethingLeft && isSomethingRight ) {
        return u8"─";
    }

    return u8"*";
}

int PathDrawer::GetRelativeHorizontalPosition ( MapPoint* absolute, MapPoint* relative ) {
    if ( absolute == nullptr || relative == nullptr ) {
        return false;
    }

    if ( absolute->X() == relative->X() ) {
        return 0;
    }

    if ( absolute->X() < relative->X() ) {
        return 1;
    }

    return -1;
}

int PathDrawer::GetRelativeVerticalPosition ( MapPoint* absolute, MapPoint* relative ) {
    if ( absolute == nullptr || relative == nullptr ) {
        return false;
    }

    if ( absolute->Y() == relative->Y() ) {
        return 0;
    }

    if ( absolute->Y() < relative->Y() ) {
        return 1;
    }

    return -1;
}

bool PathDrawer::IsPointInPath ( std::vector<MapPoint*> path, MapPoint* point ) {
    int pathSize = path.size();

    for ( int i = 0; i < pathSize; i++ ) {
        if ( point->Is( path[ i ] ) ) {
            return true;
        }
    }

    return false;
}

bool PathDrawer::IsPointInPath ( std::vector<MapPoint*> path, MapPoint* point, int* index ) {
    int pathSize = path.size();

    for ( int i = 0; i < pathSize; i++ ) {
        if ( point->Is( path[ i ] ) ) {
            *index = i;
            return true;
        }
    }

    return false;
}