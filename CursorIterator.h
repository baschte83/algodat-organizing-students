/**
 * Created by Sebastian Baumann on 20.11.2016.
 */

#ifndef TESTS_CURSORITERATOR_H
#define TESTS_CURSORITERATOR_H

#include <utility>  // benötigt für std::swap
#include <iostream>
using namespace std;

template <class T> class CursorIterator {

    // Definition of a new CursorIterator object
    typedef CursorIterator<T> iterator;

    // Generic pointer, which should be stored
    T *itr;


public:

    // Constructor
    CursorIterator(T& rhs) {
        itr = rhs;
    }
    // Copy constructor
    CursorIterator(const CursorIterator& rhs) {
        itr = new T(rhs.getItr());
    }

    // Returns the pointer variable *itr
    T* getItr() const {
        return itr;
    }

    // Deconstructor for a pointer
    ~CursorIterator() {
        delete[] itr;
    };

    // Operator overloading for *: dereferencing pointers
    T& operator *() {
        return *itr;
    };

    // Operator overloading of =
    iterator& operator = (const iterator& rhs) {
        if (this != &rhs) {
            iterator tmp(rhs);
            std::swap(itr, tmp.itr);
        }
        return *this;
    };

    // Operator overloading of ==
    bool operator == (const iterator& rhs) const {
        return (itr == rhs.getItr());
    };

    // Incrementing of an iterator
    iterator& operator ++();
    iterator operator ++(int) {
        // TODO Implementierung Operatorüberladung postfix "++"
        // postfix operator, dummy parameter
    };

    // Method to print this iterator to the screen
    void printIterator() {
        cout << itr;
    }

};

#endif //TESTS_CURSORITERATOR_H
