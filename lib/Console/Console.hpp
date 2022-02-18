#ifndef Console_HPP
#define Console_HPP
#include <string>

/// @brief Enum zawierający kolory konsoli
enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    PURPLE = 5,
    YELLOW = 6,
    WHITE = 7,
    BRIGHT_BLACK = 8,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_PURPLE = 13,
    BRIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15,
};

class Console {
    private:
        /// @brief Uchwyt do konsoli
        static void* hConsole;

        /// @brief Domyślne wartości kolorów w konsoli
        static int originalAttributes;

    public: 
        /**
         * @brief Ustawia kolor tła i tekstu konsoli
         * 
         * @param foreground Kolor tekstu
         * @param background Kolor tła
         */
        static void SetColor ( Color foreground = WHITE, Color background = BLACK );

        /// @brief Resetuje kolory do ustawień oryginalnych
        static void ResetColor ();

        /// @brief Inicjalizuje statyczną klasę
        static void Initialize ();

        /**
         * @brief Zamienia nazwę koloru @p na wartość Enum
         * 
         * @param colorName Nazwa koloru
         * @return Color Wartość Enum
         * @throw Console::GetColor: Nie znaleziono koloru z taką nazwą.
         */
        static Color GetColor ( std::string colorName );
};

#endif