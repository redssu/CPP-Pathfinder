#ifndef PathFinder_HPP
#define PathFinder_HPP
#include <vector>
#include "../MapPoint/MapPoint.hpp"
#include "../Map/Map.hpp"

class PathFinder {
    private:
        /// @brief Wskaźnik do punktu startowego
        MapPoint* start;

        /// @brief Wskaźnik do punktu końcowego
        MapPoint* end;

        /// @brief Wskaźnik do mapy
        Map* map;

        /**
         * @brief Oblicza heurystyczną wartość drogi między dwoma punktami.
         * 
         * @param point1 Wskaźnik do punktu startowego
         * @param point2 Wskaźnik do punktu końcowego
         * @return int Wartość heurystyczna
         */
        int CalculateHCost ( MapPoint* point1, MapPoint* point2 );

        /**
         * @brief Oblicza koszt przejścia między dwoma sąsiadami.
         * 
         * @param point1 Wskaźnik do punktu startowego
         * @param point2 Wskaźnik do punktu końcowego
         * @return int Koszt przejścia
         */
        int CalculateNeighbourGCost ( MapPoint* point1, MapPoint* point2 );

        /**
         * @brief Zwraca wektor z wskaźnikami do sąsiadów punktu. 
         * 
         * @param point Wskaźnik do punktu
         * @return std::vector<MapPoint*> Wektor z wskaźnikami do sąsiadów
         */
        std::vector<MapPoint*> GetPointNeighbours ( MapPoint* point );
    
    public:
        /**
         * @brief Konstruktor
         * 
         * @param map Wskaźnik do mapy na której będzie wykonywany algorytm
         * @param start Wskaźnik do punktu startowego
         * @param end Wskaźnik do punktu końcowego
         */
        PathFinder ( Map* map, MapPoint* start, MapPoint* end );

        /**
         * @brief Ustawia punkt startowy.
         * 
         * @param point Wskaźnik do punktu startowego
         */
        void SetStart ( MapPoint* point );

        /**
         * @brief Ustawia punkt końcowy.
         * 
         * @param point Wskaźnik do punktu końcowego
         */
        void SetEnd ( MapPoint* point );

        /**
         * @brief Wykonuje algorytm wyszukiwania drogi.
         * 
         * @return Wektor z trasą od punktu startowego do punktu końcowego
         * @throw PathFinderException: Punkt startowy nie znajduje się na mapie
         * @throw PathFinderException: Punkt końcowy nie znajduje się na mapie
         * @throw PathFinderException: Nie udało się odtworzyć ścieżki
         * @throw PathFinderException: Nie udało się odnaleźć ścieżki
         */
        std::vector<MapPoint*> FindPath ();
};

#endif