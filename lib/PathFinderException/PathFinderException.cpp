#include "PathFinderException.hpp"

PathFinderException::PathFinderException ( const char* fnName, const char* message ) {
    this->message = message;
    this->fnName = fnName;
}

PathFinderException::PathFinderException ( const std::string& fnName, const std::string& message ) {
    this->message = message;
    this->fnName = fnName;
}

std::string PathFinderException::GetFunctionName () {
    return this->fnName;
}

std::string PathFinderException::GetMessage () {
    return this->message;
}