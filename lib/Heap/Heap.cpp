#include <vector>
#include "Heap.hpp"
#include "../MapPoint/MapPoint.hpp"
#include "../PathFinderException/PathFinderException.hpp"

template<class T> void Heap<T>::Swap ( int index1, int index2 ) {
    if ( index1 < 0 || index1 >= heap.size() || index2 < 0 || index2 >= heap.size() ) {
        throw PathFinderException( "Heap::Swap", "Indeks elementu jest nieprawidłowy" );
    }

    T temp = this->heap[ index1 ];
    this->heap[ index1 ] = this->heap[ index2 ];
    this->heap[ index2 ] = temp;
}

template<class T> void Heap<T>::FixHeap ( int index ) {
    int lowestIndex = index;

    int leftChildIndex = lowestIndex * 2 + 1;
    int rightChildIndex = lowestIndex * 2 + 2;

    if ( leftChildIndex < this->heap.size() && heap[ lowestIndex ] > heap[ leftChildIndex ] ) {
        lowestIndex = leftChildIndex;
    }

    if ( rightChildIndex < this->heap.size() && heap[ lowestIndex ] > heap[ rightChildIndex ] ) {
        lowestIndex = rightChildIndex;
    }

    if ( lowestIndex != index ) {
        this->Swap( index, lowestIndex );
        this->FixHeap( lowestIndex );
    }
}

template<class T> void Heap<T>::Insert ( T element ) {
    this->heap.push_back( element );

    int index = this->heap.size() - 1;
    int parent = index / 2;

    while ( index > 0 && this->heap[ index ] < this->heap[ parent ] ) {
        this->Swap( parent, index );
        index = parent;
    }
}

template<> void Heap<MapPoint>::InsertOrChange ( MapPoint element ) {
    int index = -1;
    int size = this->heap.size();

    // szukamy indeksu elementu
    for ( int i = 0; i < size; i++ ) {
        if ( element.Is( &this->heap[ i ] ) ) {
            index = i;
            break;
        }
    }

    // jeżeli nie znaleziono takiego elementu, to dodajemy go
    if ( index == -1 ) {
        this->Insert( element );
        return;
    } 
    
    // jeżeli znaleziono taki element, to zamieniamy go i naprawiamy stertę
    this->heap[ index ] = element;
    this->FixHeap( index );
}

template<class T> void Heap<T>::InsertOrChange ( T element ) {
    int index = -1;
    int size = this->heap.size();

    // szukamy indeksu elementu
    for ( int i = 0; i < size; i++ ) {
        if ( this->heap[ i ] == element ) {
            index = i;
            break;
        }
    }

    // jeżeli nie znaleziono takiego elementu, to dodajemy go
    if ( index == -1 ) {
        this->Insert( element );
        return;
    } 
    
    // jeżeli znaleziono taki element, to zamieniamy go i naprawiamy stertę
    this->heap[ index ] = element;
    this->FixHeap( index );
}

template<class T> T Heap<T>::GetTop () {
    if ( this->heap.size() == 0 ) {
        throw PathFinderException( "Heap::GetTop", "Sterta jest pusta, lecz próbowano zdjąć z niej element" );
    }

    return this->heap[ 0 ];
}

template<class T> void Heap<T>::Pop () {
    if ( this->heap.size() == 0 ) {
        throw PathFinderException( "Heap::GetTop", "Sterta jest pusta, lecz próbowano usunąć z niej element" );
    }

    this->heap[ 0 ] = this->heap[ this->heap.size() - 1 ];
    this->heap.pop_back();

    FixHeap( 0 );
}

template<> bool Heap<MapPoint>::Contains ( MapPoint element ) {
    int size = this->heap.size();

    for ( int i = 0; i < size; i++ ) {
        if ( element.Is( &this->heap[ i ] ) ) {
            return true;
        }
    }

    return false;
}

template<class T> bool Heap<T>::Contains ( T element ) {
    int size = this->heap.size();

    for ( int i = 0; i < size; i++ ) {
        if ( this->heap[ i ] == element ) {
            return true;
        }
    }

    return false;
}

template<class T> int Heap<T>::Size () {
    return this->heap.size();
}

template class Heap<MapPoint*>;