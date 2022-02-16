#include "MapPoint.hpp"

#define INFINITY 2147483647;
#define NULL 0

/**
 * Publiczne
 */
MapPoint::MapPoint ( 
    int x, 
    int y,
    float weight, 
    char symbol, 
    color fgColor,
    color bgColor
) {
    this->x = x;
    this->y = y;
    this->weight = weight;
    this->symbol = symbol;
    this->fgColor = fgColor;
    this->bgColor = bgColor;
    this->gCost = INFINITY;
    this->hCost = 0;
    this->parent = NULL;

    this->calculateFCost();
}

int MapPoint::X () { return this->x; }
int MapPoint::Y () { return this->y; }
float MapPoint::Weight () { return this->weight; }
char MapPoint::Symbol () { return this->symbol; }

color MapPoint::FGColor () { return this->fgColor; }
color MapPoint::BGColor () { return this->bgColor; }

float MapPoint::GCost () { return this->gCost; }
float MapPoint::HCost () { return this->hCost; }
float MapPoint::FCost () { return this->fCost; }

void MapPoint::SetGCost ( float gCost ) { this->gCost = gCost; }
void MapPoint::SetHCost ( float fCost ) { this->hCost = fCost; }

void MapPoint::SetParent ( MapPoint *parent ) { this->parent = parent; }
MapPoint* MapPoint::getParent () { return this->parent; }

bool MapPoint::Is ( MapPoint *other ) { return ( this->x == other->X() && this->y == other->Y() ); }

bool MapPoint::operator== ( MapPoint *other ) { return this->CompareTo( other ) == 0; }
bool MapPoint::operator!= ( MapPoint *other ) { return this->CompareTo( other ) != 0; }
bool MapPoint::operator< ( MapPoint *other ) { return this->CompareTo( other ) < 0; }
bool MapPoint::operator> ( MapPoint *other ) { return this->CompareTo( other ) > 0; }
bool MapPoint::operator<= ( MapPoint *other ) { return this->CompareTo( other ) <= 0; }
bool MapPoint::operator>= ( MapPoint *other ) { return this->CompareTo( other ) >= 0; }

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
