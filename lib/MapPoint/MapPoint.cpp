#include "MapPoint.hpp"
#include "../Console/Console.hpp"

#define INFINITY 2147483647;

#ifndef NULL
#define NULL 0
#endif

/**
 * Prywatne
 */
int MapPoint::CompareTo ( MapPoint *other ) {
    if ( this->fCost < other->fCost ) {
        return -1;
    } 
    else if ( this->fCost > other->fCost ) {
        return 1;
    }
    
    if ( this->hCost < other->hCost ) {
        return -1;
    } 
    else if ( this->hCost > other->hCost ) {
        return 1;
    }

    if ( this->weight < other->weight ) {
        return -1;
    } 
    else if ( this->weight > other->weight ) {
        return 1;
    }

    return 0;
}

void MapPoint::calculateFCost () {
    this->fCost = this->gCost + this->hCost;
}


/**
 * Publiczne
 */
MapPoint::MapPoint () {
    this->x = -1;
    this->y = -1;
    this->weight = 1.0;
    this->symbol = ' ';
    this->fgColor = WHITE;
    this->bgColor = BLACK;
    this->gCost = 0;
    this->hCost = 0;
    this->fCost = 0;
    this->parent = NULL;
}

MapPoint::MapPoint ( 
    int x, 
    int y,
    float weight, 
    char symbol, 
    Color fgColor,
    Color bgColor
) {
    this->x = x;
    this->y = y;
    this->weight = weight;
    this->symbol = symbol;
    this->fgColor = fgColor;
    this->bgColor = bgColor;
    this->gCost = INFINITY;
    this->hCost = 0;
    this->fCost = INFINITY;
    this->parent = NULL;
}

int MapPoint::X () { return this->x; }
int MapPoint::Y () { return this->y; }
float MapPoint::Weight () { return this->weight; }
char MapPoint::Symbol () { return this->symbol; }

Color MapPoint::FGColor () { return this->fgColor; }
Color MapPoint::BGColor () { return this->bgColor; }

int MapPoint::GCost () { return this->gCost; }
int MapPoint::HCost () { return this->hCost; }
int MapPoint::FCost () { return this->fCost; }

void MapPoint::SetGCost ( int gCost ) { this->gCost = gCost; this->calculateFCost(); }
void MapPoint::SetHCost ( int fCost ) { this->hCost = fCost; this->calculateFCost(); }

void MapPoint::SetParent ( MapPoint *parent ) { this->parent = parent; }
MapPoint* MapPoint::GetParent () { return this->parent; }

bool MapPoint::Is ( MapPoint *other ) { return ( this->x == other->X() && this->y == other->Y() ); }

bool MapPoint::operator== ( MapPoint *other ) { return this->CompareTo( other ) == 0; }
bool MapPoint::operator== ( MapPoint other ) { return this->CompareTo( &other ) == 0; }

bool MapPoint::operator!= ( MapPoint *other ) { return this->CompareTo( other ) != 0; }
bool MapPoint::operator!= ( MapPoint other ) { return this->CompareTo( &other ) != 0; }

bool MapPoint::operator< ( MapPoint *other ) { return this->CompareTo( other ) < 0; }
bool MapPoint::operator< ( MapPoint other ) { return this->CompareTo( &other ) < 0; }

bool MapPoint::operator> ( MapPoint *other ) { return this->CompareTo( other ) > 0; }
bool MapPoint::operator> ( MapPoint other ) { return this->CompareTo( &other ) > 0; }

bool MapPoint::operator<= ( MapPoint *other ) { return this->CompareTo( other ) <= 0; }
bool MapPoint::operator<= ( MapPoint other ) { return this->CompareTo( &other ) <= 0; }

bool MapPoint::operator>= ( MapPoint *other ) { return this->CompareTo( other ) >= 0; }
bool MapPoint::operator>= ( MapPoint other ) { return this->CompareTo( &other ) >= 0; }