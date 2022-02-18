#include <cmath>
#include <vector>
#include "../MapPoint/MapPoint.hpp"
#include "../Map/Map.hpp"
#include "../Heap/Heap.hpp"
#include "../PathFinder/PathFinder.hpp"

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
            if ( ( dx == 0 ) && ( dy == 0 ) ) {
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

PathFinder::PathFinder ( Map* map, MapPoint* start, MapPoint* end ) {
    this->map = map;
    this->start = start;
    this->end = end;
}

void PathFinder::SetStart ( MapPoint* point ) {
    this->start = point;
}

void PathFinder::SetEnd ( MapPoint* point ) {
    this->end = point;
}

std::vector<MapPoint*> PathFinder::FindPath () {
    if ( !this->map->IsPointInMap( this->start ) ) {
        throw "PathFinder::FindPath: Punkt startowy nie znajduje się na mapie";
    }

    if ( !this->map->IsPointInMap( this->end ) ) {
        throw "PathFinder::FindPath: Punkt końcowy nie znajduje się na mapie";
    }

    // wierzchołki odwiedzone
    Heap<MapPoint*> closedList = Heap<MapPoint*>();

    // wierzchołki nieodwiedzone
    Heap<MapPoint*> openList = Heap<MapPoint*>();

    openList.Insert( this->start );

    // koszt dotarcia do startu jest równy zero
    this->start->SetGCost( 0 );

    while ( openList.Size() > 0 ) {
        MapPoint* current = openList.GetTop();

        // jeśli trafiliśmy na punkt końcowy, zakończ
        if ( current->Is( this->end ) ) {
            std::vector<MapPoint*> path;
            path.push_back( current );

            while ( !current->Is( this->start ) ) {
                current = current->GetParent();

                if ( !this->map->IsPointInMap( current ) ) {
                    throw "PathFinder::FindPath: Nie udało się odtworzyć ścieżki";
                }

                path.push_back( current );
            }

            return path;
        }
        
        // sprawdzamy teraz ten wierzchołek, więc przenosimy go 
        // z listy nieodwiedzonych do listy odwiedzonych
        openList.Pop();
        closedList.Insert( current );

        std::vector<MapPoint*> neighbours = this->GetPointNeighbours( current );

        int neighboursSize = neighbours.size();
        
        for ( int i = 0; i < neighboursSize; i++ ) {
            // jeśli ten wierzchołek już przeglądaliśmy to go pomijamy
            MapPoint* neighbour = neighbours[ i ];

            if ( closedList.Contains( neighbour ) ) {
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
            if ( newNeighbourGCost < neighbour->GCost() || !openList.Contains( neighbour ) ) {
                neighbour->SetGCost( newNeighbourGCost );
                neighbour->SetHCost( this->CalculateHCost( neighbour, this->end ) );
                neighbour->SetParent( current );

                // dodajemy go do kandydatów następnej iteracji
                openList.InsertOrChange( neighbour );
            }
        }
    }

    throw "PathFinder::FindPath: Nie udało się odnaleźć ścieżki";
}