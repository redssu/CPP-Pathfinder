#ifndef PathDrawer_HPP
#define PathDrawer_HPP
#include <vector>
#include <string>
#include "../MapPoint/MapPoint.hpp"
#include "../Map/Map.hpp"

class PathDrawer {
    private:
        /**
         * @brief Zwraca znak, który ma być wstawiony na mapie w miejscu punktu drogi
         * 
         * @param point Punkt drogi
         * @param prev Poprzedni punkt drogi
         * @param next Następny punkt drogi
         */
        static std::string GetCharacterForPoint ( std::vector<MapPoint*> path, int pathPointIndex );

        /**
         * @brief Zwraca relatywną pozycję punktu względem poprzedniego punktu w linii poziomej
         * 
         * @param point1 Punkt 1
         * @param point2 Punkt 2
         * @return -1, 0, 1
         */
        static int GetRelativeHorizontalPosition ( MapPoint* point1, MapPoint* point2 );

        /**
         * @brief Zwraca relatywną pozycję punktu względem poprzedniego punktu w linii pionowej
         * 
         * @param point1 Punkt 1
         * @param point2 Punkt 2
         * @return -1, 0, 1
         */
        static int GetRelativeVerticalPosition ( MapPoint* point1, MapPoint* point2 );

        /**
         * @brief Sprawdza, czy punkt należy do ścieżki
         * 
         * @param path Ścieżka
         * @param point Punkt do sprawdzenia
         * @return true Jeśli punkt należy do ścieżki
         */
        static bool IsPointInPath ( std::vector<MapPoint*> path, MapPoint* point );

        /**
         * @brief Sprawdza, czy punkt należy do ścieżki i uzupełnia wskaźnik indeksem punktu w ścieżce
         * 
         * @param path Ścieżka
         * @param point Punkt do sprawdzenia
         * @param index Wskaźnik do zmiennej ze wskaźnikiem
         * @return true Jeśli punkt należy do ścieżki
         */
        static bool IsPointInPath ( std::vector<MapPoint*> path, MapPoint* point, int* index );

    public:
        /**
         * @brief Rysuje drogę na mapie
         * 
         * @param map Mapa na której narysować drogę
         * @param path Wektor z wskaźnikami do punktów na mapie, które stanowią drogę
         */
        static void DisplayMapWithPath ( Map* map, std::vector<MapPoint*> path );
};

#endif