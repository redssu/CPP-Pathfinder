#include "../Console/Console.hpp"
#include "../MapPoint/MapPoint.hpp"
#include "../Map/Map.hpp"
#include "./MapLoader.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

MapLoader::MapLoader ( std::string fileName ) {
    this->file.open( fileName );

    if ( !this->file.good() ) {
        throw std::runtime_error( "MapLoader::MapLoader: Nie udało się otworzyć pliku." );
    }
}

std::string MapLoader::TokenTypeToStr ( TokenType type ) {
    switch ( type ) {
        case TokenType::IDENTIFIER: return "Identifier";
        case TokenType::COMMA: return "Comma";
        case TokenType::COLON: return "Colon";
        case TokenType::SEMICOLON: return "Semicolon";
        case TokenType::CHAR: return "Char";
        case TokenType::NUMBER: return "Number";
        case TokenType::COLOR: return "Color";
        case TokenType::MAPSTART: return "MapStart";
        case TokenType::MAPEND: return "MapEnd";
        case TokenType::END: return "End";
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
            this->ParseColor();
            continue;
        }

        if ( currentChar == '\'' ) {
            this->ParseChar();
            continue;
        }

        if ( currentChar == '$' ) {
            this->ParseMap();
            continue;
        }

        if ( IsNumeric( currentChar ) || currentChar == '-' ) {
            this->ParseNumber();
            continue;
        }

        if ( IsAlphabetic( currentChar ) ) {
            this->ParseIdentifier();
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

    this->tokens.push_back( { END, "FILE_END" } );
}

bool MapLoader::IsWhitespace ( char character ) {
    return ( character == ' ' || character == '\t' || character == '\n' || character == '\r' );
}

bool MapLoader::IsAlphabetic ( char character ) {
    return ( IsAlphabeticUppercase( character ) || IsAlphabeticLowercase( character ) );
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

void MapLoader::ParseColor () {
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

void MapLoader::ParseNumber () {
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

void MapLoader::ParseChar () {
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

void MapLoader::ParseIdentifier () {
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

void MapLoader::ParseMap () {
    // zacznij od sprawdzenia czy sekwencja znaków jest prawidłowa
    this->ExpectSequence( "$map:" );
    // pomiń wszelkie znaki białe
    this->SkipWhitespace();

    // dodaj token rozpoczynający mapę
    this->tokens.push_back( { MAPSTART, "$$MAP_START$$" } );

    // dodawaj i zjadajmy znaki tak długo, aż to możliwe
    while ( this->file.good() ) {
        char character = this->file.get();

        if ( (int) character == -1 ) {
            break;
        }

        this->tokens.push_back( { CHAR, std::string( 1, character ) } );
    }

    // dodaj token kończący mapę
    this->tokens.push_back( { MAPEND, "$$MAP_END$$" } );
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



Token MapLoader::GetToken () {
    // jeśli nie ma już tokenów, to zwróć pusty token
    if ( this->TokensLeft() == 0 ) {
        throw "MapLoader::GetToken: Nieoczekiwany koniec listy tokenów.";
    }

    // zwróć token z obecnej pozycji
    Token token = this->tokens[ this->currentIndex ];

    return token;
}

int MapLoader::TokensLeft () {
    return this->tokens.size() - this->currentIndex;
}

void MapLoader::ExpectToken ( TokenType type ) {
    Token token = this->GetToken();

    if ( token.type != type ) {
        throw "MapLoader::ExpectToken: Nieoczekiwany token '" + TokenTypeToStr( token.type ) + "'. Oczekiwano tokena typu '" + TokenTypeToStr( type ) + "'.";
    }
}

TokenType MapLoader::PeekTokenType () {
    if ( this->TokensLeft() < 2 ) {
        throw "MapLoader::PeekTokenType: Nieoczekiwany koniec listy tokenów.";
    }

    return this->tokens[ this->currentIndex + 1 ].type;
}

void MapLoader::ConsumeToken () {
    if ( this->TokensLeft() == 0 ) {
        throw "MapLoader::ConsumeToken: Nieoczekiwany koniec listy tokenów.";
    }

    this->currentIndex++;
}

Map MapLoader::Interpret () {
    Token currentToken = this->GetToken();

    std::map<std::string, float> variables;

    MapElementDefinition mapElementDefinitions[ 16 ];
    int mapElementDefinitionsCount = 0;

    while ( currentToken.type != END ) {
        if ( currentToken.type == IDENTIFIER ) {
            // Jest to albo ustawienie zmiennej, albo stworzenie definicji
            std::string name = currentToken.value;
            this->ConsumeToken();
            this->ExpectToken( COLON );
            
            if ( name == "def" ) {
                this->InterpretDefinition( mapElementDefinitions, &mapElementDefinitionsCount );
            }
            else {
                // Jest to ustawienie zmiennej
                this->InterpretVariable( name, &variables );
            }
        }
        else if ( currentToken.type == MAPSTART ) {
            // Jest to rozpoczęcie mapy
            return this->InterpretMap( variables, mapElementDefinitions, mapElementDefinitionsCount );
        }
        else {
            throw "MapLoader::Interpret: Nieoczekiwany token '" + TokenTypeToStr( currentToken.type ) + "'. Oczekiwano tokena typu '" + TokenTypeToStr( IDENTIFIER ) + "'.";
        }

        currentToken = this->GetToken();
    }

    throw "MapLoader::Interpret: Nieoczekiwany koniec pliku.";
}

void MapLoader::InterpretVariable ( std::string name, std::map<std::string, float>* variables ) {
    this->ConsumeToken();

    this->ExpectToken( NUMBER );
    float value = std::stof( this->GetToken().value );
    this->ConsumeToken();

    this->ExpectToken( SEMICOLON );
    this->ConsumeToken();

    ( *variables )[ name ] = value;
}

void MapLoader::InterpretDefinition ( MapElementDefinition* definitions, int* definitionCount ) {
    this->ConsumeToken();

    this->ExpectToken( CHAR );
    char symbol = this->GetToken().value[ 0 ];
    this->ConsumeToken();
    
    this->ExpectToken( COMMA );
    this->ConsumeToken();
    
    this->ExpectToken( NUMBER );
    float weight = std::stof( this->GetToken().value );
    this->ConsumeToken();
    
    this->ExpectToken( COMMA );
    this->ConsumeToken();

    this->ExpectToken( COLOR );
    Color color = (Color) std::stoi( this->GetToken().value );
    this->ConsumeToken();

    this->ExpectToken( COMMA );
    this->ConsumeToken();

    this->ExpectToken( COLOR );
    Color bgColor = (Color) std::stoi( this->GetToken().value );
    this->ConsumeToken();

    this->ExpectToken( SEMICOLON );
    this->ConsumeToken();

    if ( *definitionCount > 15 ) {
        throw "MapLoader::InterpretDefinition: Za dużo definicji elementów mapy.";
    }

    definitions[ (*definitionCount)++ ] = { symbol, weight, color, bgColor };
}

Map MapLoader::InterpretMap ( 
    std::map<std::string, float> variables, 
    MapElementDefinition* definitions,  
    int definitionCount
) {
    this->ConsumeToken();
    
    if ( variables.count( "width" ) == 0 ) {
        throw "MapLoader::InterpretMap: Brak zmiennej 'width'.";
    }

    if ( variables.count( "height" ) == 0 ) {
        throw "MapLoader::InterpretMap: Brak zmiennej 'height'.";
    }

    int width = (int) variables[ "width" ];
    int height = (int) variables[ "height" ];

    Map map = Map( width, height );

    for ( int i = 0; i < definitionCount; i++ ) {
        map.AddMapElementDefinition( definitions[ i ] );
    }

    try {
        map.GetMapElementDefinition( 'S' );
    }
    catch ( std::string error ) {
        throw "MapLoader::InterpretMap: Nie znaleziono definicji punktu startowego o symbolu 'S'.";
    }

    try {
        map.GetMapElementDefinition( 'E' );
    }
    catch ( std::string error ) {
        throw "MapLoader::InterpretMap: Nie znaleziono definicji punktu koncowego o symbolu 'E'.";
    }

    for ( int row = 0; row < height; row++ ) {
        for ( int col = 0; col < width; col++ ) {
            this->ExpectToken( CHAR );
            char symbol = this->GetToken().value[ 0 ];
            this->ConsumeToken();

            map.SetMapPoint( col, row, symbol );
        }

        // jeżeli to ostatni wiersz, to nie oczekujemy końca linii
        if ( row == height - 1 ) {
            break;
        }

        this->ExpectToken( CHAR );
        char newline = this->GetToken().value[ 0 ];

        if ( newline != '\n' ) {
            throw "MapLoader::InterpretMap: Nieoczekiwany token znaku '" + std::to_string( newline ) + "'. Oczekiwano tokena znaku nowej linii.";
        }

        this->ConsumeToken();
    }

    this->ExpectToken( MAPEND );
    this->ConsumeToken();
    this->ExpectToken( END );
    this->ConsumeToken();

    return map;
}