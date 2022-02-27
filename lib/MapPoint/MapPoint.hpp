#ifndef MapPoint_HPP
#define MapPoint_HPP
#include "../Console/Console.hpp"

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
        Color fgColor;

        /// @brief Kolor tła symbolu
        Color bgColor;

        /// @brief koszt dotarcia od startu do tego punktu
        long int gCost; 

        /// @brief (potencjalny) koszt dotarcia od tego punktu do celu
        long int hCost;

        /// @brief "opłacalność" punktu (mniej -> lepiej)
        long int fCost;

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
        MapPoint ();

        MapPoint ( 
            int x, 
            int y, 
            float weight = 1.0, 
            char symbol = '.', 
            Color fgColor = WHITE,
            Color bgColor = BLACK
        );

        // ? Dlaczego jako metody ?
        // Właściwości powinny być publicznie odczytywalne
        // ale nie powinny być modyfikowalne

        /// @returns Pozycja X punktu
        int X ();

        /// @returns Pozycja Y punktu
        int Y ();

        /// @returns Waga punktu
        float Weight ();

        /// @returns Symbol reprezentujący ten punkt
        char Symbol ();

        /// @brief Ustawia symbol reprezentujący ten punkt
        void SetSymbol ( char symbol );

        /// @returns Kolor symbolu
        Color FGColor ();

        /// @brief Ustawia kolor symbolu
        void SetFGColor ( Color fgColor );

        /// @returns Kolor tła symbolu
        Color BGColor ();

        /// @brief Ustawia kolor tła symbolu
        void SetBGColor ( Color bgColor );

        /// @returns Koszt dotarcia od startu do tego punktu.
        long int GCost ();

        /// @returns (potencjalny) koszt dotarcia od tego punktu do celu.
        long int HCost ();

        /// @returns "opłacalność" punktu (mniej -> lepiej).
        long int FCost ();

        /// @brief Ustawia koszt dotarcia od startu do tego punktu.
        void SetGCost ( long int gCost );

        /// @brief Ustawia koszt dotarcia od tego punktu do celu.
        void SetHCost ( long int fCost );

        /// @brief Ustawia punkt poprzedni w trasie do celu.
        void SetParent ( MapPoint *parent );

        /// @returns Punkt poprzedni w trasie do celu.
        MapPoint* GetParent ();

        /**
         * @brief Sprawdza czy inny punkt to ten sam punkt.
         * 
         * @details Sprawdzane jest równość pozycji X i Y.
         * @param other Punkt do porównania
         * @return bool
         */
        bool Is ( MapPoint *other );
        
        /**
         * @{ @name Przeciążenia operatorów
         */
        bool operator== ( MapPoint *other );
        bool operator== ( MapPoint other );

        bool operator!= ( MapPoint *other );
        bool operator!= ( MapPoint other );

        bool operator< ( MapPoint *other );
        bool operator< ( MapPoint other );

        bool operator> ( MapPoint *other );
        bool operator> ( MapPoint other );

        bool operator<= ( MapPoint *other );
        bool operator<= ( MapPoint other );

        bool operator>= ( MapPoint *other );
        bool operator>= ( MapPoint other );
        /**
         * @}
         */
};

#endif