#include <vector>
#include "Heap.hpp"
#include "../MapPoint/MapPoint.hpp"

template <class T> void Heap<T>::Swap ( int index1, int index2 ) {
    if ( index1 < 0 || index1 >= heap.size() || index2 < 0 || index2 >= heap.size() ) {
        throw "Heap::Swap: Indeks elementu jest nieprawidłowy";
    }

    T temp = heap[ index1 ];
    heap[ index1 ] = heap[ index2 ];
    heap[ index2 ] = temp;
}

template <class T> void Heap<T>::FixHeap ( int index ) {
    int lowestIndex = index;

    int leftChildIndex = lowestIndex * 2 + 1;
    int rightChildIndex = lowestIndex * 2 + 2;


    if ( leftChildIndex < heap.size() && heap[ lowestIndex ] > heap[ leftChildIndex ] ) {
        lowestIndex = leftChildIndex;
    }

    if ( rightChildIndex < heap.size() && heap[ lowestIndex ] > heap[ rightChildIndex ] ) {
        lowestIndex = rightChildIndex;
    }

    if ( lowestIndex != index ) {
        Swap ( index, lowestIndex );
        FixHeap ( lowestIndex );
    }
}

template <class T> void Heap<T>::Insert ( T element ) {
    heap.push_back ( element );

    int index = heap.size() - 1;
    int parent = index / 2;

    while ( index > 0 && heap[ index ] < heap[ parent ] ) {
        Swap ( parent, index );
        index = parent;
    }
}

template <class T> T Heap<T>::GetTop () {
    if ( heap.size() == 0 ) {
        throw "Heap::GetTop: Pusta sterta";
    }

    return heap[ 0 ];
}

template <class T> void Heap<T>::Pop () {
    if ( heap.size() == 0 ) {
        throw "Heap::Pop: Pusta sterta";
    }

    heap[ 0 ] = heap[ heap.size() - 1 ];
    heap.pop_back();

    FixHeap ( 0 );
}

template <> bool Heap<MapPoint>::Contains ( MapPoint element ) {
    int size = heap.size();

    for ( int i = 0; i < size; i++ ) {
        if ( element.Is( &heap[ i ] ) ) {
            return true;
        }
    }

    return false;
}

template <class T> bool Heap<T>::Contains ( T element ) {
    int size = heap.size();

    for ( int i = 0; i < size; i++ ) {
        if ( heap[ i ] == element ) {
            return true;
        }
    }

    return false;
}

template <class T> int Heap<T>::Size () {
    return heap.size();
}