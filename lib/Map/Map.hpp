#ifndef Map_HPP
#define Map_HPP
#include <iostream>
#include "../Console/Console.hpp"
#include "../MapPoint/MapPoint.hpp"

struct MapElementDefinition {
    char symbol;
    float weight;
    Color fgColor;
    Color bgColor;
};

class Map {
    private:
        /// @brief Tablica definicji elementów, z których składa się mapa
        MapElementDefinition mapElementDefinitions[ 16 ];

        /// @brief Ilość definicji elementów mapy
        int mapElementDefintionsCount;

        /// @brief Szerokość mapy
        int width;

        /// @brief Wysokość mapy
        int height;

        /// @brief Tablica punktów mapy
        MapPoint map[ 32 ][ 32 ];
    
    public:
        /**
         * @brief Konstruktor
         * 
         * @param width Szerokość mapy
         * @param height Wysokość mapy
         * @throw PathFinderException: Szerokość mapy jest mniejsza niż 1
         * @throw PathFinderException: Wysokość mapy jest mniejsza niż 1
         * @throw PathFinderException: Szerokość mapy jest większa niż 32
         * @throw PathFinderException: Wysokość mapy jest większa niż 32
         */
        Map ( int width, int height );

        /**
         * @brief Zwraca szerokość mapy
         * 
         * @return liczba z zakresu 1 od 32
         */
        int Width ();

        /** 
         * @brief Zwraca wysokość mapy
         * 
         * @return liczba z zakresu 1 od 32
         */
        int Height ();
        
        /**
         * @brief Zwraca mapę
         * 
         * @return MapPoint* Mapa w postaci tablicy dwuwymiarowej
         */
        MapPoint* GetMap ();

        /// @brief Wyświetla mapę
        void Print ();

        /* Definicje Elementów mapy */

        /**
         * @brief Dodaje definicję elementu mapy
         * 
         * @param mapElementDefinition Definicja elementu mapy
         */
        void AddMapElementDefinition ( MapElementDefinition mapElementDefinition );

        /**
         * @brief Dodaje definicję elementu mapy
         * 
         * @param symbol Symbol reprezentujący definicję
         * @param weight Waga elementów z tym symbolem
         * @param fgColor Kolor symbolu
         * @param bgColor Kolor tła symbolu
         * @throw PathFinderException: Liczba definicji mapy jest większa niż 16
         */
        void AddMapElementDefinition ( 
            char symbol, 
            float weight = 1.0, 
            Color fgColor = WHITE, 
            Color bgColor = BLACK 
        );

        /**
         * @brief Zwraca definicję elementu mapy po indeksie
         * 
         * @param index Indeks definicji
         * @return Definicja elementu mapy
         * @throw PathFinderException: Nie znaleziono definicji elementu mapy
         */
        MapElementDefinition GetMapElementDefinition ( int index );

        /**
         * @brief Zwraca definicję elementu mapy po symbolu
         * 
         * @param char Symbol definicji
         * @return Definicja elementu mapy
         * @throw PathFinderException: Nie znaleziono definicji elementu mapy
         */
        MapElementDefinition GetMapElementDefinition ( char symbol );

        /* Punkty mapy */

        /**
         * @brief Sprawdza czy punkt o podanych współrzędnych należy do mapy
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
         * @brief Sprawdza czy punkt należy do mapy
         * 
         * @param point Wskaźnik do obiektu punktu
         * @return true jeśli punkt należy do mapy
         */
        bool IsPointInMap ( MapPoint* point );
        
        /**
         * @brief Zwraca punkt z mapy
         * 
         * @param int Współrzędna X
         * @param int Współrzędna Y
         * @throw PathFinderException: Nieprawidłowe współrzędne punktu
         * @return Wskaźnik punktu z mapy
         */
        MapPoint* GetMapPoint ( int x, int y );

        /**
         * @brief Ustawia punkt mapy
         * 
         * @param mapPoint Obiekt Punktu mapy
         * @throw PathFinderException: Nieprawidłowe współrzędne punktu
         */
        void SetMapPoint ( MapPoint mapPoint );

        /**
         * @brief Ustawia punkt mapy o podanych współrzędnych i symbolu
         * 
         * @param x Współrzędna X
         * @param y Współrzędna Y
         * @param symbol Symbol reprezentujący definicję elementu mapy
         * @throw PathFinderException: Nieprawidłowe współrzędne punktu
         * @throw PathFinderException: Nie znaleziono definicji elementu mapy
         */
        void SetMapPoint ( int x, int y, char symbol );

        /**
         * @brief Ustawia punkt mapy o podanych współrzędnych i definicji
         * 
         * @param x Współrzędna X
         * @param y Współrzędna Y
         * @param definition Definicja elementu mapy
         * @throw PathFinderException: Nieprawidłowe współrzędne punktu
         */
        void SetMapPoint ( int x, int y, MapElementDefinition definition );

        /**
         * @brief Ustawia punkt mapy o podanych współrzędnych i parametrach
         * 
         * @param x Współrzędna X
         * @param y Współrzędna Y
         * @param symbol Symbol reprezentujący ten punkt mapy
         * @param weight Waga punktu
         * @param fgColor Kolor punktu
         * @param bgColor Kolor tła punktu
         * @throw PathFinderException: Nieprawidłowe współrzędne punktu
         */
        void SetMapPoint ( 
            int x, 
            int y, 
            char symbol, 
            float weight, 
            Color fgColor = WHITE, 
            Color bgColor = BLACK
        );

        /**
         * @brief Usuwa punkt mapy o podanych współrzędnych
         * 
         * @param x Współrzędna X
         * @param y Współrzędna Y
         * @throw PathFinderException: Nieprawidłowe współrzędne punktu
         */
        void RemoveMapPoint ( int x, int y );

        /**
         * @brief Usuwa punkt mapy
         * 
         * @param mapPoint Obiekt Punktu mapy
         * @throw PathFinderException: Nieprawidłowe współrzędne punktu
         */
        void RemoveMapPoint ( MapPoint mapPoint );
};

#endif