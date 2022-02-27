#ifndef MapLoader_HPP
#define MapLoader_HPP
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "../Map/Map.hpp"

enum TokenType {
    IDENTIFIER,
    COMMA,
    COLON,
    SEMICOLON,
    CHAR,
    NUMBER,
    COLOR,
    MAPSTART,
    MAPEND,
    END
};

struct Token {
    TokenType type;
    std::string value;
};

class MapLoader {
    private:
        /// @brief Uchwyt do pliku
        std::fstream file;

        /// @brief Lista tokenów
        std::vector<Token> tokens;

        /**
         * @brief Sprawdza czy podany znak jest znakiem białym
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest biały
         */
        static bool IsWhitespace ( char character );

        /**
         * @brief Sprawdza czy podany znak jest alfabetyczny
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest alfabetyczny
         */
        static bool IsAlphabetic ( char character );

        /**
         * @brief Sprawdza czy podany znak jest alfabetyczny (tylko duże litery)
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest alfabetyczny 
         */
        static bool IsAlphabeticUppercase ( char character );

        /**
         * @brief Sprawdza czy podany znak jest alfabetyczny (tylko małe litery)
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest alfabetyczny
         */
        static bool IsAlphabeticLowercase ( char character );

        /**
         * @brief Sprawdza czy podany znak jest cyfrą
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest cyfrą
         */
        static bool IsNumeric ( char character );

        /// @brief Przetwarza token typu COLOR
        void ParseColor ();

        /// @brief Przetwarza token typu NUMBER
        void ParseNumber ();

        /**
         * @brief Przetwarza token typu CHAR
         * 
         * @throw PathFinderException: Oczekiwano zamykającego ' na pozycji %s.
         */
        void ParseChar ();

        /// @brief Przetwarza token typu IDENTIFIER
        void ParseIdentifier ();

        /// @brief Przetwarza rysunek mapy
        void ParseMap ();

        /// @brief Pomija wszelkie znaki białe od obecnej pozycji w pliku
        void SkipWhitespace ();

        /// @brief Pomija komentarz
        void SkipComment ();

        /**
         * @brief Sprawdza, czy podana sekwencja jest poprawna
         * 
         * @param sequence Sekwencja do sprawdzenia
         * @throw PathFinderException: Oczekiwano znaku '%s'
         */
        void ExpectSequence ( std::string sequence );


        /// @brief Pozycja w wektorze tokenów
        int currentIndex;
        
        /**
         * @brief Pobiera obecny token
         * 
         * @return Token Token
         * @throw PathFinderException: Nieoczekiwany koniec listy tokenów.
         */
        Token GetToken ();

        /**
         * @brief Zwraca liczbę pozostałych tokenów
         * 
         * @return int
         */
        int TokensLeft ();

        /**
         * @brief Sprawdza, czy token jest konkretnego typu. Jeśli nie, wyrzuca wyjątek
         * 
         * @param type Typ tokena
         * @throw PathFinderException: Nieoczekiwany token '%s'. Oczekiwano tokena typu '%s'.
         */
        void ExpectToken ( TokenType type );

        /**
         * @brief podgląda typ następnego tokena
         * 
         * @return TokenType
         * @throw PathFinderException: Nieoczekiwany koniec listy tokenów.
         */
        TokenType PeekTokenType ();

        /**
         * @brief Zjadaja obecny token
         * 
         * @throw PathFinderException: Nieoczekiwany koniec listy tokenów.
         */
        void ConsumeToken ();

        /**
         * @brief Interpretuje zmienną
         * 
         * @param name Nazwa zmiennej
         * @param variables Wskaźnik do mapy zmiennych
         * @throw PathFinderException
         */
        void InterpretVariable ( std::string name, std::map<std::string, float>* variables );

        /**
         * @brief Interpretuje definicję
         * 
         * @param definitions Tablica definicji
         * @param definitionCount Wskaźnik do licznika definicji
         * @throw PathFinderException: Za dużo definicji elementów mapy.
         * @throw PathFinderException
         */
        void InterpretDefinition ( MapElementDefinition* definitions, int* definitionCount );

        /**
         * @brief Interpretuje mapę
         * 
         * @param variables Mapa zmiennych
         * @param definitions Tablica definicji
         * @param definitionCount Licznik definicji
         * @return Obiekt mapy
         * @throw PathFinderException: Brak zmiennej 'width'.
         * @throw PathFinderException: Brak zmiennej 'height'.
         * @throw PathFinderException: Nie znaleziono definicji punktu startowego o symbolu 'S'.
         * @throw PathFinderException: Nie znaleziono definicji punktu końcowego o symbolu 'E'.
         * @throw PathFinderException: Nieoczekiwany token znaku '%s'. Oczekiwano tokena znaku nowej linii.
         */
        Map InterpretMap ( std::map<std::string, float> variables, MapElementDefinition* definitions, int definitionCount );

    public:
        /**
         * @brief Konstruktor, ładuje plik
         * 
         * @param fileName Nazwa pliku
         * @throw PathFinderException: Nie udało się otworzyć pliku.
         */
        MapLoader ( std::string fileName ); 

        /**
         * @brief Tokenizuje plik
         * 
         * @throw PathFinderException
         */
        void Tokenize ();

        /**
         * @brief Interpretuje listę tokenów
         * 
         * @return Zinterpretowana mapa
         * @throw PathFinderException: Nieoczekiwany token '%s'. Oczekiwano tokena typu '%s'.
         * @throw PathFinderException: Nieoczekiwany koniec listy tokenów.
         * @throw PathFinderException
         */
        Map Interpret ();

        /**
         * @brief Przetwarza typ tokenu na nazwę typu tokenu przyjazną człowiekowi
         * 
         * @param type Typ tokena
         * @return Nazwa tokenu przyjazna człowiekowi
         */
        static std::string TokenTypeToStr ( TokenType type );
};

#endif