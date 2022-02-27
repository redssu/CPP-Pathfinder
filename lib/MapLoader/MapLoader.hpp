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

        /// @brief Wskaźnik do mapy
        Map* map;

        /**
         * Sprawdza czy podany znak jest znakiem białym
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest biały
         */
        static bool IsWhitespace ( char character );

        /**
         * Sprawdza czy podany znak jest alfabetyczny
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest alfabetyczny
         */
        static bool IsAlphabetic ( char character );

        /**
         * Sprawdza czy podany znak jest alfabetyczny (tylko duże litery)
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest alfabetyczny 
         */
        static bool IsAlphabeticUppercase ( char character );

        /**
         * Sprawdza czy podany znak jest alfabetyczny (tylko małe litery)
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest alfabetyczny
         */
        static bool IsAlphabeticLowercase ( char character );

        /**
         * Sprawdza czy podany znak jest cyfrą
         * 
         * @param character Znak do sprawdzenia
         * @return true jeśli znak jest cyfrą
         */
        static bool IsNumeric ( char character );

        /// @brief Przetwarza token typu COLOR
        void ParseColor ();

        /// @brief Przetwarza token typu NUMBER
        void ParseNumber ();

        /// @brief Przetwarza token typu CHAR
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
         * @brief Sprawdza czy podana sekwencja jest poprawna
         * 
         * @param sequence Sekwencja do sprawdzenia
         * @throw MapLoader::ExpectSequence: Oczekiwano znaku '%s'
         */
        void ExpectSequence ( std::string sequence );


        /// @brief Pozycja w wektorze tokenów
        int currentIndex;
        
        /**
         * @brief Funkcja pobierająca obecny token
         * 
         * @return Token Token
         * @throw MapLoader::GetToken: Nieoczekiwany koniec listy tokenów.
         */
        Token GetToken ();

        /**
         * @brief Funkcja zwracająca liczbę pozostałych tokenów
         * 
         * @return int
         */
        int TokensLeft ();

        /**
         * @brief Funkcja sprawdzająca, czy token jest konkretnego typu. Jeśli nie, wyrzuca wyjątek
         * 
         * @param type Typ tokena
         * @throw MapLoader::ExpectToken: Nieoczekiwany token '%s'. Oczekiwano tokena typu '%s'.
         */
        void ExpectToken ( TokenType type );

        /**
         * @brief Funkcja podglądająca typ następnego tokena
         * 
         * @return TokenType
         * @throw MapLoader::PeekTokenType: Nieoczekiwany koniec listy tokenów.
         */
        TokenType PeekTokenType ();

        /**
         * @brief Funkcja zjadająca obecny token
         * 
         * @throw MapLoader::ConsumeToken: Nieoczekiwany koniec listy tokenów.
         */
        void ConsumeToken ();

        /**
         * @brief Funkcja interpretująca zmienną
         * 
         * @param name Nazwa zmiennej
         * @param variables Wskaźnik do mapy zmiennych
         */
        void InterpretVariable ( std::string name, std::map<std::string, float>* variables );

        /**
         * @brief Funkcja interpretująca definicję
         * 
         * @param definitions Tablica definicji
         * @param definitionCount Wskaźnik do licznika definicji
         */
        void InterpretDefinition ( MapElementDefinition* definitions, int* definitionCount );

        /**
         * @brief Funkcja interpretująca mapę
         * 
         * @param variables Mapa zmiennych
         * @param definitions Tablica definicji
         * @param definitionCount Licznik definicji
         * @return Obiekt mapy
         */
        Map InterpretMap ( std::map<std::string, float> variables, MapElementDefinition* definitions, int definitionCount );

    public:
        /**
         * @brief Konstruktor, ładuje plik
         * 
         * @param fileName Nazwa pliku
         * @throw MapLoader::MapLoader: Nie udało się otworzyć pliku.
         */
        MapLoader ( std::string fileName ); 

        /**
         * @brief Tokenizuje plik
         * 
         * @throw Dużo...
         */
        void Tokenize ();

        /**
         * @brief Interpretuje listę tokenów
         * 
         * expression = variable | map | definition
         * variable = identifier, colon, number, semicolon
         * map = mapstart, char, mapend
         * definition = identifier, colon, char, comma, number, comma, color, comma, color, semicolon
         */
        Map Interpret ();

        static std::string TokenTypeToStr ( TokenType type );
};

#endif