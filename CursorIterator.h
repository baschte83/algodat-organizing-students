//
// Created by sebas on 20.11.2016.
//

#ifndef TESTS_CURSORITERATOR_H
#define TESTS_CURSORITERATOR_H

#include <utility>  // benötigt für std::swap
#include <iostream>
using namespace std;

template <class T> class CursorIterator {

    typedef CursorIterator<T> iterator;
    // typedef T value_type; -> Muss noch eingefuegt werden in der Klasse, in der die Klasse CursorIterator Subklasse ist!

    T *itr; // generischer Pointer, der gespeichert werden soll


public:

    // Konstruktoren fuer Iteratoren ------------------------------------

    // Konstruktor
    CursorIterator(T& rhs) {
        itr = rhs;
    }
    // Kopier-Konstruktor
    CursorIterator(const CursorIterator& rhs) {
        itr = new T(rhs.getItr());
    }


    // Getter -----------------------------------------------------------

    // Ein Getter fuer die Zeiger-Variable *itr.
    // Diese muss const sein, damit der Getter nur lesend
    // auf die Variable zugreifen darf
    T* getItr() const {
        return itr;
    }

    // Dekonstruktor für einen Zeiger -----------------------------------
    ~CursorIterator() {
        delete[] itr;   // Loescht den Zeiger nach Verlassen des Scope
    };


    // Operatorueberladungen --------------------------------------------

    // Operatorüberladung der *: Dereferenzierung von Pointern
    T& operator *() {
        /*
         * Rueckgabetyp ist der Typ der Klasse, auf den Iterator zeigt,
         * deshalb T&.
         */
        return *itr;
    };

    // Operatorüberladung von des Zuweisungsoperator "="
    iterator& operator = (const iterator& rhs) {
        /*
         * Falls der uebergebene Pointer gleich diesem Pointer
         * ist, soll einfach dieser Pointer an den Aufrufer zurueck
         * gegeben werden. Sind die beiden Pointer aber nicht gleich,
         * so wird ein neues Pointer-Objekt per Kopie des uebergebenen
         * Pointer-Objekts erzeugt und die Werte des neuen Pointer-Objekts
         * per std:swap auf dieses Pointer-Objekt uebertragen/vertauscht.
         */
        if (this != &rhs) {
            iterator tmp(rhs);
            std::swap(itr, tmp.itr);
        }
        return *this;
    };

    // Operatorüberladung von !=
    /*bool operator != (const iterator& rhs) const {
        return (*this != rhs.getItr());    // Nutzt die Operator-Ueberladung "=="
    };*/

    // Operatorüberladung von ==
    bool operator == (const iterator& rhs) const {
        // Zeigt, ob die Adresse gespeichert in itr gleich
        // der Adresse gespeichert in rhs.getItr() ist.
        // Hier werden also zwei Adressen verglichen.
        return (itr == rhs.getItr());
    };

    /*
     * Inkrement eines Iterator-Zeigers als postfix Inkrement:
     * Die beiden Überladungen des Postfix-Inkrements ++
     * iterator& operator ++() und iterator& operator ++(int)
     * gehören zusammen. Dabei wird nur das zweite Inkrement
     * iterator& operator ++(int) implementiert. Das erste wird
     * nur definiert.
     */
    iterator& operator ++();
    iterator operator ++(int) {
        // TODO Implementierung Operatorüberladung postfix "++"
        // postfix operator, dummy parameter

        // Was muss passieren, damit der Zeiger per zeiger++
        // um eine Stelle nach vorne geschoben wird?
    };

    // Methoden in der Klasse CursorList
    void printIterator() {
        cout << itr;
    }

};

#endif //TESTS_CURSORITERATOR_H
