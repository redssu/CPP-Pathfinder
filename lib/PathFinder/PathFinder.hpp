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

        /**
         * @brief Znajduje najlepszy punkt w wektorze punktów.
         * 
         * @param points Wskaźnik do wektora ze wskaźnikami do punków
         * @return Indeks najlepszego punktu
         */
        static int FindBestPointIndex ( std::vector<MapPoint*>* points );

        /**
         * @brief Sprawdza czy punkt jest w wektorze punktów.
         * 
         * @param points Wskaźnik do wektora ze wskaźnikami do punktów
         * @param point Wskaźnik do szukanego punktu
         * @return true Jeśli punkt znajduje się w wektorze
         */
        static bool IsPointInVector ( std::vector<MapPoint*>* points, MapPoint* point );

        /**
         * @brief Dodaje punkt do wektoru jeśli nie znajduje go w wektorze, lub go aktualizuje jeśli znajduje.
         * 
         * @param points Wskaźnik do wektora ze wskaźnikami do punktów
         * @param point Wskaźnik do dodawanego punktu
         */
        static void AddOrUpdatePointInVector ( std::vector<MapPoint*>* points, MapPoint* point );

        /**
         * @brief Usuwa punkt z wektora.
         * 
         * @param points Wskaźnik do wektora ze wskaźnikami do punktów
         * @param point Wskaźnik do usuwanego punktu
         */
        static void RemovePointFromVector ( std::vector<MapPoint*>* points, MapPoint* point );

        /**
         * @brief Usuwa punkt z wektora.
         * 
         * @param points Wektor do wektora ze wskaźnikami do punktów
         * @param index Indeks punktu do usunięcia
         */
        static void RemovePointFromVector ( std::vector<MapPoint*>* points, int index );
        
    
    public:
        static bool ALLOW_DIAGONAL_NEIGHBOURS;
        /**
         * @brief Konstruktor
         * 
         * @param map Wskaźnik do mapy na której będzie wykonywany algorytm
         * @throw PathFinderException: Nie znaleziono punktu startowego
         * @throw PathFinderException: Nie znaleziono punktu końcowego
         */
        PathFinder ( Map* map );

        /**
         * @brief Wykonuje algorytm wyszukiwania drogi.
         * 
         * @return Wektor z trasą od punktu startowego do punktu końcowego
         * @throw PathFinderException: Nie udało się odtworzyć ścieżki
         * @throw PathFinderException: Nie udało się odnaleźć ścieżki
         */
        std::vector<MapPoint*> FindPath ();
};

#endif