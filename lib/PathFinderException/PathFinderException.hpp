#ifndef PATHFINDEREXCEPTION_HPP
#define PATHFINDEREXCEPTION_HPP
#include <string>

class PathFinderException {
    private:
        /// @brief Treść wyjątku
        std::string message;

        /// @brief Funkcja wyrzucająca wyjątek
        std::string fnName;

    public:
        /**
         * Konstruktor wyjątku
         * 
         * @param fnName Nazwa funkcji wywołującej wyjątek
         * @param message Treść wyjątku
         */
        PathFinderException ( const char* fnName, const char* message );
        PathFinderException ( const std::string& fnName, const std::string& message );

        /**
         * @brief Zwraca treść wyjątku
         * 
         * @return Treść wyjątku
         */
        std::string GetMessage ();

        /**
         * @brief Zwraca nazwę funkcji wywołującej wyjątek
         * 
         * @return Nazwa funkcji wywołującej wyjątek
         */
        std::string GetFunctionName ();
};

#endif