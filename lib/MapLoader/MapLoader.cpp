#include "../MapPoint/MapPoint.hpp"
#include "../Map/Map.hpp"
#include "./MapLoader.hpp"
#include <iostream>
#include <fstream>
#include <string>

MapLoader::MapLoader ( std::string fileName ) {
    this->file.open( fileName );

    if ( !this->file.good() ) {
        throw std::runtime_error( "MapLoader::MapLoader: Nie udało się otworzyć pliku." );
    }
}

void MapLoader::Tokenize () {
    if ( !this->file.good() ) {
        throw "MapLoader::Tokenize: Nie udało się otworzyć pliku mapy.";
    }

    do {
        char currentChar = file.peek();

        if ( currentChar == ':' ) {
            this->tokens.push_back( { COLON, ":" } );
            this->file.get();
            continue;
        }

        if ( currentChar == ',' ) {
            this->tokens.push_back( { COMMA, "," } );
            this->file.get();
            continue;
        }

        if ( currentChar == ';' ) {
            this->tokens.push_back( { SEMICOLON, ";" } );
            this->file.get();
            continue;
        }

        if ( currentChar == '#' ) {
            this->SkipComment();
            continue;
        }

        if ( currentChar == '@' ) {
            this->file.get();
            this->Color();
            continue;
        }

        if ( currentChar == '\'' ) {
            this->Char();
            continue;
        }

        if ( currentChar == '$' ) {
            this->Map();
            continue;
        }

        if ( IsNumeric( currentChar ) || currentChar == '-' ) {
            this->Number();
            continue;
        }

        if ( IsAlphabetic( currentChar ) ) {
            this->Identifier();
            continue;
        }

        if ( IsWhitespace( currentChar ) ) {
            this->SkipWhitespace();
            continue;
        }

        if ( currentChar == EOF ) {
            break;
        }

        std::streampos currentPosition = this->file.tellg();
        this->file.seekg( -1, std::ios::cur );
        char previousChar = this->file.get();

        throw "MapLoader::Tokenize: Nieoczekiwany znak '" + std::string( 1, currentChar ) + "' na pozycji " + std::to_string( currentPosition ) + " (obok: '" + std::string( 1, previousChar ) + "')";
    }
    while ( this->file.good() );

    this->tokens.push_back( { END, "END" } );
}

bool MapLoader::IsWhitespace ( char character ) {
    return ( character == ' ' || character == '\t' || character == '\n' || character == '\r' );
}

bool MapLoader::IsAlphabetic ( char character ) {
    return (  IsAlphabeticUppercase( character ) || IsAlphabeticLowercase( character ) );
}

bool MapLoader::IsAlphabeticUppercase ( char character ) {
    return ( character >= 'A' && character <= 'Z' );
}

bool MapLoader::IsAlphabeticLowercase ( char character ) {
    return ( character >= 'a' && character <= 'z' );
}

bool MapLoader::IsNumeric ( char character ) {
    return ( character >= '0' && character <= '9' );
}

void MapLoader::Color () {
    if ( !this->file.good() ) {
        return;
    }

    std::string color;

    // trzeba posłużyć się zmienną, bo są dwa warunki w While
    char character = this->file.peek();

    // sprawdź czy jest to znak, który wchodzi w skład nazw kolorów
    while ( this->file.good() && ( IsAlphabeticUppercase( character ) || character == '_' ) ) {
        // jeśli jest to dodaj i zjedz znak
        color += this->file.get();
        character = this->file.peek();
    }

    std::string tokenValue = std::to_string( Console::GetColor( color ) );

    this->tokens.push_back( { COLOR, tokenValue } );
}

void MapLoader::Number () {
    if ( !this->file.good() ) {
        return;
    }

    std::string number;

    // sprawdź czy jest minus przed liczbą
    if ( this->file.good() && this->file.peek() == '-' ) {
        // jeśli tak, to go po prostu dodaj i zjedz
        number += this->file.get();
    }

    // część całkowita
    // dodawaj i zjadaj kolejne znaki do liczby jeśli są cyframi
    while ( this->file.good() && IsNumeric( this->file.peek() ) ) {
        number += this->file.get();
    }

    // sprawdź czy następny znak to kropka
    if ( this->file.good() && this->file.peek() == '.' ) {
        number += this->file.get(); // <-- jeśli tak to dodaj ją do liczby i zjedz

        // sprawdź czy po kropce jest część ułamkowa
        if ( this->file.good() && IsNumeric( this->file.peek() ) ) {
            // jeśli tak to rozpocznij na nowo cykl dodawania cyfr
            while ( this->file.good() && IsNumeric( this->file.peek() ) ) {
                number += this->file.get(); // <-- dodaj cyfrę i zjedz
            }
        }
        else {
            // jeśli nie, to dodaj zero do liczby (by była prawidłowa)
            number += '0';
        }
    }

    this->tokens.push_back( { NUMBER, number } );
}

void MapLoader::Char () {
    if ( !this->file.good() ) {
        return;
    }

    std::string character;
    this->file.get(); // <-- zjedz otwierający '
    character = this->file.get(); // <-- zjedz potencjalny znak

    // jeśli po znaku następuje zamykający ' to wszystko jest ok
    if ( this->file.peek() == '\'' ) {
        this->file.get(); // <-- zjedz zamykający '
        this->tokens.push_back( { CHAR, character } ); // <-- dodaj token
    }
    else {
        throw "MapLoader::Char: Oczekiwano zamykającego ' na pozycji " + std::to_string( this->file.tellg() );
    }
}

void MapLoader::Identifier () {
    if ( !this->file.good() ) {
        return;
    }

    std::string identifier;

    // sprawdź czy jest to znak, który jest alfabetyczny [A-Za-z]
    while ( this->file.good() && IsAlphabetic( this->file.peek() ) ) {
        // jeśli tak, to dodaj go do nazwy i zjedz
        identifier += this->file.get();
    }

    this->tokens.push_back( { IDENTIFIER, identifier } );
}

void MapLoader::Map () {
    // zacznij od sprawdzenia czy sekwencja znaków jest prawidłowa
    this->ExpectSequence( "$map:" );
    // pomiń wszelkie znaki białe
    this->SkipWhitespace();

    // dodaj token rozpoczynający mapę
    this->tokens.push_back( { MAPSTART, "" } );

    // dodawaj i zjadajmy znaki tak długo, aż to możliwe
    while ( this->file.good() ) {
        this->tokens.push_back( { CHAR, std::string( 1, this->file.get() ) } );
    }

    // dodaj token kończący mapę
    this->tokens.push_back( { MAPEND, "" } );
} 

void MapLoader::SkipWhitespace () {
    // sprawdź czy jest to znak, który jest białym znakiem lub końcem pliku
    while ( this->file.good() && this->file.peek() != EOF && IsWhitespace( this->file.peek() ) ) {
        // jeśli tak, to zjedz go
        this->file.get();
    }
}

void MapLoader::SkipComment () {
    // zjadaj wszystkie znaki tak długo aż nie trafisz na nową linię lub koniec pliku
    while ( this->file.good() && !( this->file.peek() == '\n' || this->file.peek() == EOF ) ) {
        this->file.get();
    }
} 

void MapLoader::ExpectSequence ( std::string sequence ) {
    for ( std::string::size_type i = 0; i < sequence.size(); i++ ) {
        // sprawdź, czy znak na obecnej pozycji pliku to obecny znak w sekwencji
        if ( !this->file.good() || this->file.peek() != sequence[ i ] ) {
            throw "MapLoader::ExpectSequence: Oczekiwano znaku '" + std::to_string( sequence[ i ] ) + "'.";
        }

        // jeśli tak, to zjedz go
        this->file.get();
    }
}