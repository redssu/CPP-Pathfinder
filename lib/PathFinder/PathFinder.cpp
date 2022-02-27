#include <cmath>
#include <vector>
#include "../MapPoint/MapPoint.hpp"
#include "../Map/Map.hpp"
#include "../PathFinder/PathFinder.hpp"
#include "../PathFinderException/PathFinderException.hpp"

bool PathFinder::ALLOW_DIAGONAL_NEIGHBOURS = false;

int PathFinder::CalculateHCost ( MapPoint* point1, MapPoint* point2 ) {
    int horizontalDistance = abs( point1->X() - point2->X() );
    int verticalDistance = abs( point1->Y() - point2->Y() );

    int diagonalDistance = 
        ( horizontalDistance > verticalDistance ) 
        ? horizontalDistance 
        : verticalDistance;
    
    int flatDistance = ( horizontalDistance + verticalDistance - diagonalDistance );

    // 14 - bo poruszamy się po przekątnej kwadratu o boku 1 (sqrt(2)*10)
    // 10 - bo poruszamy się po boku kwadratu o boku 1
    return ( ( diagonalDistance * 14 ) + ( flatDistance * 10 ) );
}

int PathFinder::CalculateNeighbourGCost ( MapPoint* point1, MapPoint* point2 ) {
    // jeśli sąsiad znajduje się na tej samej linii X lub Y, to dystans 
    // do niego jest równy 10 (długość boku)
    if ( point1->X() == point2->X() || point1->Y() == point2->Y() ) {
        return 10;
    }

    // jeśli nie, to znaczy, że jest sąsiadem narożnym, a dystans do niego
    // jest równy 14 (długość przekątnej)
    return 14;
}

std::vector<MapPoint*> PathFinder::GetPointNeighbours ( MapPoint* point ) {
    std::vector<MapPoint*> neighbours;

    // originX i originY
    int ox = point->X();
    int oy = point->Y();

    // deltaX i deltaY
    for ( int dx = -1; dx <= 1; dx++ ) {
        for ( int dy = -1; dy <= 1; dy++ ) {
            // dx = 0 i dy = 0 to inaczej punkt dla którego
            // szukamy sąsiadów, więc go pomijamy
            if ( ( dx == 0 ) && ( dy == 0 )  ) {
                continue;
            }

            if ( !ALLOW_DIAGONAL_NEIGHBOURS && dx != 0 && dy != 0 ) {
                continue;
            }

            int x = ox + dx;
            int y = oy + dy;

            if ( !this->map->IsPointInMap( x, y ) ) {
                continue;
            }

            neighbours.push_back( this->map->GetMapPoint( x, y ) );
        } 
    }
    
    return neighbours;
}

int PathFinder::FindBestPointIndex ( std::vector<MapPoint*>* points ) {
    if ( points->size() == 0 ) {
        throw PathFinderException( "PathFinder::FindBestPoint", "Brak punktów do przeszukania." );
    }

    int size = points->size();
    int bestFCost = (*points)[ 0 ]->FCost();
    int bestIndex = 0;

    for ( int i = 0; i < size; i++ ) {
        if ( (*points)[ i ]->FCost() < bestFCost ) {
            bestIndex = i;
            bestFCost = (*points)[ i ]->FCost();
        }
    }

    return bestIndex;
}

bool PathFinder::IsPointInVector ( std::vector<MapPoint*>* points, MapPoint* point ) {
    int size = points->size();

    for ( int i = 0; i < size; i++ ) {
        if ( point->Is( (*points)[ i ] ) ) {
            return true;
        }
    }

    return false;
}

void PathFinder::AddOrUpdatePointInVector ( std::vector<MapPoint*>* points, MapPoint* point ) {
    int size = points->size();

    for ( int i = 0; i < size; i++ ) {
        if ( point->Is( (*points)[ i ] ) ) {
            (*points)[ i ] = point;
            return;
        }
    }

    points->push_back( point );
}

void PathFinder::RemovePointFromVector ( std::vector<MapPoint*>* points, MapPoint* point ) {
    int size = points->size();

    for ( int i = 0; i < size; i++ ) {
        if ( point->Is( (*points)[ i ] ) ) {
            points->erase( points->begin() + i );
            return;
        }
    }
}

void PathFinder::RemovePointFromVector ( std::vector<MapPoint*>* points, int index ) {
    points->erase( points->begin() + index );
}

PathFinder::PathFinder ( Map* map ) {
    this->map = map;

    int mapWidth = this->map->Width();
    int mapHeight = this->map->Height();

    for ( int row = 0; row < mapHeight; row++ ) {
        for ( int col = 0; col < mapWidth; col++ ) {
            char symbol = this->map->GetMapPoint( col, row )->Symbol();

            if ( symbol == 'S' ) {
                this->start = this->map->GetMapPoint( col, row );
            } 
            else if ( symbol == 'E' ) {
                this->end = this->map->GetMapPoint( col, row );
            }
        }
    }

    if ( !this->map->IsPointInMap( this->start ) ) {
        throw PathFinderException( "PathFinder::PathFinder", "Nie znaleziono punktu startowego." );
    }

    if ( !this->map->IsPointInMap( this->end ) ) {
        throw PathFinderException( "PathFinder::PathFinder", "Nie znaleziono punktu końcowego." );
    }
}

std::vector<MapPoint*> PathFinder::FindPath () {
    // wierzchołki odwiedzone
    std::vector<MapPoint*> closedList;

    // wierzchołki nieodwiedzone
    std::vector<MapPoint*> openList;

    openList.push_back( this->start );

    // koszt dotarcia do startu jest równy zero
    this->start->SetGCost( 0 );

    while ( openList.size() > 0 ) {
        int bestPointIndex = FindBestPointIndex( &openList );
        MapPoint* current = openList[ bestPointIndex ];

        // jeśli trafiliśmy na punkt końcowy, zakończ
        if ( current->Is( this->end ) ) {
            std::vector<MapPoint*> path;
            path.push_back( current );

            // rekonstruujemy ścieżkę
            while ( !current->Is( this->start ) ) {
                current = current->GetParent();

                if ( !this->map->IsPointInMap( current ) ) {
                    throw PathFinderException( "PathFinder::FindPath", "Nie udało się odtworzyć ścieżki" );
                }

                path.push_back( current );
            }

            return path;
        }
        
        // sprawdzamy teraz ten wierzchołek, więc przenosimy go 
        // z listy nieodwiedzonych do listy odwiedzonych
        RemovePointFromVector( &openList, bestPointIndex );
        AddOrUpdatePointInVector( &closedList, current );

        std::vector<MapPoint*> neighbours = this->GetPointNeighbours( current );

        int neighboursSize = neighbours.size();
        
        for ( int i = 0; i < neighboursSize; i++ ) {
            // jeśli ten wierzchołek już przeglądaliśmy to go pomijamy
            MapPoint* neighbour = neighbours[ i ];

            if ( IsPointInVector( &closedList, neighbour ) ) {
                continue;
            }

            // koszt dotarcia od startu do tego sąsiada
            // jest równy kosztowi dotarcia do obecnego wierzchołka
            // + koszt dotarcia od obecnego wierzchołka do tego sąsiada
            // pomnożony przez wagę sąsiada
            int localGCost = this->CalculateNeighbourGCost( current, neighbour ) * neighbour->Weight();
            int newNeighbourGCost = current->GCost() + localGCost;

            // jeżeli koszt dotarcia sąsiada jest mniejszy niż wyliczony ostatnim razem
            // to znaczy że znaleźliśmy do niego lepszą drogę
            // lub jeśli sąsiad nie był jeszcze odwiedzony
            // to jest to jego pierwsza optymalna droga
            bool isNeighbourInOpenList = IsPointInVector( &openList, neighbour );

            if ( newNeighbourGCost < neighbour->GCost() || !isNeighbourInOpenList ) {
                neighbour->SetParent( current );
                neighbour->SetGCost( newNeighbourGCost );

                if ( !isNeighbourInOpenList ) {
                    neighbour->SetHCost( this->CalculateHCost( neighbour, this->end ) );
                    openList.push_back( neighbour );
                }
            }
        }
    }

    throw PathFinderException( "PathFinder::FindPath", "Nie udało się odnaleźć ścieżki" );
}