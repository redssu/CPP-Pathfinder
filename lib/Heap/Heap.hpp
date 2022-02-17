#ifndef Heap_HPP
#define Heap_HPP
#include <vector>

template <class T>
class Heap {
    private:
        /// @brief Sterta
        std::vector<T> heap;

        /**
         * @brief Zamienia miejscami dwa elementy w stercie
         * 
         * @param a Indeks pierwszego elementu
         * @param b Indeks drugiego elementu
         * @throw "Heap::Swap: Indeks elementu jest nieprawidłowy"
         */
        void Swap ( int index1, int index2 );

        /**
         * @brief Naprawa sterty
         * 
         * @param index Indeks elementu, od którego rozpocząć naprawę
         */
        void FixHeap ( int index );

    public:
        /**
         * @brief Dodaje nowy element do sterty
         * 
         * @param element Element do dodania
         */
        void Insert ( T element );

        /**
         * @brief Zwraca ze sterty najwyżej położony element
         * 
         * @note Tu fajnie byłoby mieć wskaźnik, ale nie wykryjemy zmiany zmiennej
         *     a poza tym vector często jest przenoszony w pamięci, więc wskaźniki
         *     często są nieaktualne
         * @return Najwyżej położony element
         */
        T GetTop ();

        /**
         * @brief Usuwa najwyższy element ze sterty
         */
        void Pop ();

        /**
         * @brief Sprawdza, czy element @p jest w stercie
         * 
         * @param element Element do sprawdzenia
         * @return true, jeśli element jest w stercie
         */
        bool Contains ( T element );

        /**
         * @brief Zwraca rozmiar sterty
         * 
         * @return Rozmiar sterty
         */
        int Size ();
};

#endif