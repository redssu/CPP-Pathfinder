#ifndef MapLoader_HPP
#define MapLoader_HPP
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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
        void Color ();

        /// @brief Przetwarza token typu NUMBER
        void Number ();

        /// @brief Przetwarza token typu CHAR
        void Char ();

        /// @brief Przetwarza token typu IDENTIFIER
        void Identifier ();

        /// @brief Przetwarza rysunek mapy
        void Map ();

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

        /// @brief Wyświetla listę tokenów
        void PrintTokens () {
            int size = this->tokens.size();

            for ( int i = 0; i < size; i++ ) {
                std::cout << this->tokens[ i ].type << ": " << this->tokens[i].value << std::endl;
            }
        }

};

#endif