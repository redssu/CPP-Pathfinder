#ifndef Color_HPP
#define Color_HPP

typedef int color;

class Color {
    private:
        /// @brief Uchwyt do konsoli
        static void* hConsole;

        /// @brief Domyślne wartości kolorów w konsoli
        static int originalAttributes;

    public: 
        /**
         * @{ @name Numery kolorów, które mogą być użyte w konsoli 
         */
        static const color BLACK = 0;
        static const color BLUE = 1;
        static const color GREEN = 2;
        static const color CYAN = 3;
        static const color RED = 4;
        static const color PURPLE = 5;
        static const color YELLOW = 6;
        static const color WHITE = 7;
        static const color BRIGHT_BLACK = 8;
        static const color BRIGHT_BLUE = 9;
        static const color BRIGHT_GREEN = 10;
        static const color BRIGHT_CYAN = 11;
        static const color BRIGHT_RED = 12;
        static const color BRIGHT_PURPLE = 13;
        static const color BRIGHT_YELLOW = 14;
        static const color BRIGHT_WHITE = 15;
        /** 
         * @} 
         */

        /**
         * @brief Ustawia kolor tła i tekstu konsoli
         * 
         * @param fgColor [int] Kolor tekstu (0-15) 
         * @param bgColor [int] Kolor tła (0-15)
         */
        static void Set ( color foreground = WHITE, color background = BLACK );

        /// @brief Resetuje kolory do ustawień oryginalnych
        static void Reset ();

        /// @brief Inicjalizuje statyczną klasę
        static void Initialize ();
};

#endif