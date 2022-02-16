#ifndef Map_HPP
#define Map_HPP
#include "../Color/Color.hpp"
#include "../MapPoint/MapPoint.hpp"

struct MapElementDefinition {
    char symbol;
    float weight;
    color fgColor;
    color bgColor;
};

class Map {
    private:
        /// @brief Definicje elementów z których składa się mapa
        MapElementDefinition mapElementDefinitions[ 16 ];

        /// @brief Liczba elementów w definicji mapy
        int mapElementDefintionsCount;

        /// @brief Szerokość mapy
        int width;

        /// @brief Wysokość mapy
        int height;

        /// @brief Tablica elementów mapy
        MapPoint map[ 32 ][ 32 ];
    
    public:
        /**
         * @brief Konstruktor mapy
         * 
         * @param width Szerokość mapy
         * @param height Wysokość mapy
         * @throw "Map::Map: Szerokość mapy jest mniejsza niż 1"
         * @throw "Map::Map: Wysokość mapy jest mniejsza niż 1"
         * @throw "Map::Map: Szerokość mapy jest większa niż 32"
         * @throw "Map::Map: Wysokość mapy jest większa niż 32"
         */
        Map ( int width, int height );

        /// @brief Zwraca szerokość mapy 
        int Width ();

        /// @brief Zwraca wysokość mapy
        int Height ();
        
        /// @brief Zwraca mapę
        MapPoint* GetMap ();

        /* Definicje Elementów mapy */

        /**
         * @brief Ustawia definicję elementu mapy
         * 
         * @param mapElementDefinition Definicja elementu mapy
         */
        void AddMapElementDefinition ( MapElementDefinition mapElementDefinition );

        /**
         * @brief Ustawia definicję elementu mapy
         * 
         * @param symbol Symbol reprezentujący definicję
         * @param weight Waga elementów z tym symbolem
         * @param fgColor Kolor symbolu
         * @param bgColor Kolor tła symbolu
         * @throw "Map::AddMapElementDefinition: Liczba definicji mapy jest większa niż 16"
         */
        void AddMapElementDefinition ( 
            char symbol, 
            float weight = 1.0, 
            color fgColor = Color::WHITE, 
            color bgColor = Color::BLACK 
        );

        /**
         * @brief Zwraca definicję elementu mapy po indeksie
         * 
         * @param index Indeks definicji
         * @return [MapElementDefinition] Definicja elementu mapy
         * @throw "Map::GetMapElementDefinition: Nie znaleziono definicji elementu mapy"
         */
        MapElementDefinition GetMapElementDefinition ( int index );

        /**
         * @brief Zwraca Definicję elementu mapy po symbolu
         * 
         * @param char Symbol definicji
         * @return [MapElementDefinition] Definicja elementu mapy
         * @throw "Map::GetMapElementDefinition: Nie znaleziono definicji elementu mapy"
         */
        MapElementDefinition GetMapElementDefinition ( char symbol );

        /* Punkty mapy */

        /**
         * @brief Sprawdza czy punkt należy do mapy
         * 
         * @param x Współrzędna x punktu
         * @param y Współrzędna y punktu
         * @return true jeśli punkt należy do mapy
         */
        bool IsPointInMap ( int x, int y );

        /**
         * @brief Sprawdza czy punkt należy do mapy
         * 
         * @param point Obiekt punktu
         * @return true jeśli punkt należy do mapy
         */
        bool IsPointInMap ( MapPoint point );
        
        /**
         * @brief Zwraca punkt z mapy
         * 
         * @param int Współrzędna X
         * @param int Współrzędna Y
         * @throw "Map::GetMapPoint: Nieprawidłowe współrzędne punktu"
         * @return [MapPoint*] Wskaźnik punktu z mapy
         */
        MapPoint* GetMapPoint ( int x, int y );

        /**
         * @brief Ustawia punkt mapy
         * 
         * @param mapPoint Obiekt Punktu mapy
         * @throw "Map::SetMapPoint: Nieprawidłowe współrzędne punktu"
         */
        void SetMapPoint ( MapPoint mapPoint );

        /**
         * @brief Ustawia punkt mapy
         * 
         * @param x Współrzędna X
         * @param y Współrzędna Y
         * @param symbol Symbol reprezentujący definicję elementu mapy
         * @throw "Map::SetMapPoint: Nieprawidłowe współrzędne punktu"
         * @throw "Map::SetMapPoint: Nie znaleziono definicji elementu mapy"
         */
        void SetMapPoint ( int x, int y, char symbol );

        /**
         * @brief Ustawia punkt mapy
         * 
         * @param x Współrzędna X
         * @param y Współrzędna Y
         * @param definition Definicja elementu mapy
         * @throw "Map::SetMapPoint: Nieprawidłowe współrzędne punktu"
         */
        void SetMapPoint ( int x, int y, MapElementDefinition definition );

        /**
         * @brief Ustawia punkt mapy
         * 
         * @param x Współrzędna X
         * @param y Współrzędna Y
         * @param symbol Symbol reprezentujący ten punkt mapy
         * @param weight Waga punktu
         * @param fgColor Kolor punktu
         * @param bgColor Kolor tła punktu
         * @throw "Map::SetMapPoint: Nieprawidłowe współrzędne punktu"
         */
        void SetMapPoint ( 
            int x, 
            int y, 
            char symbol, 
            float weight, 
            color fgColor = Color::WHITE, 
            color bgColor = Color::BLACK
        );

        /**
         * @brief Usuwa punkt mapy
         * 
         * @param x Współrzędna X
         * @param y Współrzędna Y
         * @throw "Map::RemoveMapPoint: Nieprawidłowe współrzędne punktu"
         */
        void RemoveMapPoint ( int x, int y );

        /**
         * @brief Usuwa punkt mapy
         * 
         * @param mapPoint Obiekt Punktu mapy
         * @throw "Map::RemoveMapPoint: Nieprawidłowe współrzędne punktu"
         */
        void RemoveMapPoint ( MapPoint mapPoint );
};

#endif