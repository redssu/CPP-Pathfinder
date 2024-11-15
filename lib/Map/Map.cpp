#include <iostream>
#include "Map.hpp"
#include "../Console/Console.hpp"
#include "../PathFinderException/PathFinderException.hpp"

Map::Map ( int width, int height ) {
    if ( width < 1 ) {
        throw PathFinderException( "Map::Map", "Szerokość mapy jest mniejsza niż 1" );
    }

    if ( height < 1 ) {
        throw PathFinderException( "Map::Map", "Wysokość mapy jest mniejsza niż 1" );
    }

    if ( width > 32 ) {
        throw PathFinderException( "Map::Map", "Szerokość mapy jest większa niż 32" );
    }

    if ( height > 32 ) {
        throw PathFinderException( "Map::Map", "Wysokość mapy jest większa niż 32" );
    }

    this->width = width;
    this->height = height;

    this->mapElementDefintionsCount = 0;
}

int Map::Width () { return this->width; }
int Map::Height () { return this->height; }

MapPoint* Map::GetMap () { return *this->map; }

void Map::Print () {
    int mapWidth = this->width;
    int mapHeight = this->height;

    for ( int y = 0; y < mapHeight; y++ ) {
        for ( int x = 0; x < mapWidth; x++ ) {
            Console::SetColor( this->map[ x ][ y ].FGColor(), this->map[ x ][ y ].BGColor() );
            std::cout << this->map[ x ][ y ].Symbol();
            Console::ResetColor();
        }

        std::cout << std::endl;
    }
}

/* Definicje Elementów mapy */

void Map::AddMapElementDefinition ( MapElementDefinition mapElementDefinition ) {
    if ( this->mapElementDefintionsCount >= 16 ) {
        throw PathFinderException( "Map::AddMapElementDefinition", "Liczba definicji mapy jest większa niż 16" );
    }

    this->mapElementDefinitions[ this->mapElementDefintionsCount++ ] = mapElementDefinition;
}

void Map::AddMapElementDefinition ( 
    char symbol, 
    float weight, 
    Color fgColor, 
    Color bgColor
) {
    if ( this->mapElementDefintionsCount >= 16 ) {
        throw PathFinderException( "Map::AddMapElementDefinition", "Liczba definicji mapy jest większa niż 16" );
    }

    this->mapElementDefinitions[ this->mapElementDefintionsCount++ ] = { 
        symbol, 
        weight, 
        fgColor, 
        bgColor 
    };
}

MapElementDefinition Map::GetMapElementDefinition ( int index ) {
    if ( index < 0 || index >= this->mapElementDefintionsCount ) {
        throw PathFinderException( "Map::GetMapElementDefinition", "Nie znaleziono definicji elementu mapy" );
    }

    return this->mapElementDefinitions[ index ];
}

MapElementDefinition Map::GetMapElementDefinition ( char symbol ) {
    for ( int i = 0; i < this->mapElementDefintionsCount; i++ ) {
        if ( this->mapElementDefinitions[ i ].symbol == symbol ) {
            return this->mapElementDefinitions[ i ];
        }
    }

    throw PathFinderException( "Map::GetMapElementDefinition", "Nie znaleziono definicji elementu mapy" );
}

/* Punkty */

bool Map::IsPointInMap ( int x, int y ) {
    return ( x >= 0 && x < this->width && y >= 0 && y < this->height );
}

bool Map::IsPointInMap ( MapPoint point ) {
    return this->IsPointInMap ( point.X(), point.Y() );
}

bool Map::IsPointInMap ( MapPoint* point ) {
    return this->IsPointInMap ( point->X(), point->Y() );
}

MapPoint* Map::GetMapPoint ( int x, int y ) {
    if ( !this->IsPointInMap( x, y ) ) {
        throw PathFinderException( "Map::GetMapPoint", "Nieprawidłowe współrzędne punktu" );
    }

    return &this->map[ x ][ y ];
}

void Map::SetMapPoint ( MapPoint mapPoint ) {
    if ( !this->IsPointInMap( mapPoint ) ) {
        throw PathFinderException( "Map::SetMapPoint", "Nieprawidłowe współrzędne punktu" );
    }

    this->map[ mapPoint.X() ][ mapPoint.Y() ] = mapPoint;
}

void Map::SetMapPoint ( int x, int y, char symbol ) {
    if ( !this->IsPointInMap( x, y ) ) {
        throw PathFinderException( "Map::SetMapPoint", "Nieprawidłowe współrzędne punktu" );
    }

    MapElementDefinition definition = this->GetMapElementDefinition( symbol );

    this->map[ x ][ y ] = MapPoint( 
        x, 
        y, 
        definition.weight, 
        definition.symbol, 
        definition.fgColor, 
        definition.bgColor 
    );
}

void Map::SetMapPoint ( int x, int y, MapElementDefinition definition ) {
    if ( !this->IsPointInMap( x, y ) ) {
        throw PathFinderException( "Map::SetMapPoint", "Nieprawidłowe współrzędne punktu" );
    }

    this->map[ x ][ y ] = MapPoint( 
        x, 
        y, 
        definition.weight, 
        definition.symbol, 
        definition.fgColor, 
        definition.bgColor 
    );
}

void Map::SetMapPoint ( int x, int y, char symbol, float weight, Color fgColor, Color bgColor ) {
    if ( !this->IsPointInMap( x, y ) ) {
        throw PathFinderException( "Map::SetMapPoint", "Nieprawidłowe współrzędne punktu" );
    }

    this->map[ x ][ y ] = MapPoint( 
        x, 
        y, 
        weight, 
        symbol, 
        fgColor, 
        bgColor 
    );
}

void Map::RemoveMapPoint ( int x, int y ) {
    if ( !this->IsPointInMap( x, y ) ) {
        throw PathFinderException( "Map::RemoveMapPoint", "Nieprawidłowe współrzędne punktu" );
    }

    this->map[ x ][ y ] = MapPoint();
}

void Map::RemoveMapPoint ( MapPoint mapPoint ) {
    if ( !this->IsPointInMap( mapPoint ) ) {
        throw PathFinderException( "Map::RemoveMapPoint", "Nieprawidłowe współrzędne punktu" );
    }

    this->map[ mapPoint.X() ][ mapPoint.Y() ] = MapPoint();
}