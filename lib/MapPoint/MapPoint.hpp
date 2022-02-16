#include "../Color/Color.hpp"

#ifndef MapPoint_HPP
#define MapPoint_HPP

class MapPoint {
    private:
        /// @brief Pozycja X punktu
        int x;

        /// @brief Pozycja Y punktu
        int y;

        /// @brief Waga punktu
        float weight;

        /// @brief Symbol reprezentujący ten punkt
        char symbol;

        /// @brief Kolor symbolu
        color fgColor;

        /// @brief Kolor tła symbolu
        color bgColor;

        /// @brief koszt dotarcia od startu do tego punktu
        float gCost; 

        /// @brief (potencjalny) koszt dotarcia od tego punktu do celu
        float hCost;

        /// @brief "opłacalność" punktu (mniej -> lepiej)
        float fCost;

        /// @brief Poprzedni punkt w drodze do punktu startowego
        MapPoint* parent;

        /**
         * @brief Porównuje ten punkt z innym punktem.
         * 
         * @details Porównywane jest fCost, a w przypadku równości - hCost, 
         *      a w przypadku kolejnej równości równości - weight.
         * 
         * @private
         * @param other Punkt do porównania
         * @return -1, 0, 1 
         */
        int CompareTo ( MapPoint *other );

        /// @brief Przelicza fCost na podstawie gCost i hCost
        void calculateFCost ();

    public:
        MapPoint();

        MapPoint( 
            int x, 
            int y, 
            float weight = 1.0, 
            char symbol = '.', 
            color fgColor = Color::WHITE,
            color bgColor = Color::BLACK
        );

        // ? Dlaczego jako metody ?
        // Właściwości powinny być publicznie odczytywalne
        // ale nie powinny być modyfikowalne

        /// @returns Pozycja X punktu
        inline int X();

        /// @returns Pozycja Y punktu
        inline int Y();

        /// @returns Waga punktu
        inline float Weight();

        /// @returns Symbol reprezentujący ten punkt
        inline char Symbol();

        /// @returns Kolor symbolu
        inline color FGColor();

        /// @returns Kolor tła symbolu
        inline color BGColor();

        /// @returns Koszt dotarcia od startu do tego punktu.
        inline float GCost();

        /// @returns (potencjalny) koszt dotarcia od tego punktu do celu.
        inline float HCost();

        /// @returns "opłacalność" punktu (mniej -> lepiej).
        inline float FCost();

        /// @brief Ustawia koszt dotarcia od startu do tego punktu.
        inline void SetGCost( float gCost );

        /// @brief Ustawia koszt dotarcia od tego punktu do celu.
        inline void SetHCost( float fCost );

        /// @brief Ustawia punkt poprzedni w trasie do celu.
        inline void SetParent ( MapPoint *parent );

        /// @returns Punkt poprzedni w trasie do celu.
        inline MapPoint* getParent();

        /**
         * @brief Sprawdza czy @p other to ten sam punkt.
         * 
         * @details Sprawdzane jest równość pozycji X i Y.
         * @param other Punkt do porównania
         * @return true | false
         */
        inline bool Is ( MapPoint *other );
        
        /**
         * @{ @name Przeciążenia operatorów
         */
        inline bool operator==( MapPoint *other );
        inline bool operator!=( MapPoint *other );
        inline bool operator< ( MapPoint *other );
        inline bool operator> ( MapPoint *other );
        inline bool operator<=( MapPoint *other );
        inline bool operator>=( MapPoint *other );
        /**
         * @}
         */
};

#endif