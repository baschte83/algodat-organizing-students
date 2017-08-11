/**
 * Created by Mikhail Slivinsky and Sebastian Baumann
 */

#ifndef TESTS_CELL_H
#define TESTS_CELL_H

#include "Student.h"
using namespace std;

class Cell {
    // Attribute einer Zelle
    int prev;    // Zeiger auf die vorhergehende Zelle in einer verketteten Liste
    int next;    // Zeiger auf eine nachfolgende Zelle in einer verketteten Liste

    // Zellenzaehler
    static int cell_counter;   // Cell-Zaehler

    // ID jeder einzelnen Zelle
    const int myCounter = cell_counter;

    // Konstanten -------------------------------
    const int defaultIndexNotSet = -2;
    const int defaultIndexStartStop = -1;

public:
    Student stud;       // Student in einer Zelle
    // Konstruktor ------------------------------
    Cell() {
        prev = defaultIndexNotSet;
        next = defaultIndexNotSet;
        ++cell_counter;
    }


    // Destruktor -------------------------------
    ~Cell() {
        --cell_counter;
    }

    // Getter und Setter ------------------------
    int getPrev() {
        return this->prev;
    }
    int getNext() {
        return this->next;
    }
    int getMatrikelnummer() {
        return this->stud.getMatrikelnummer();
    }
    void setPrev(int p) {
        prev = p;
    }
    void setNext(int n) {
        next = n;
    }
    int get_cell_counter() const{
        return myCounter;
    };

    // Sonstige Methoden ------------------------
    // Anzeigen der Werte jeder Zelle
    void printInfo() {
        // TODO Ausgabe für Abgabe überarbeiten
        cout << "Student " << get_cell_counter() << ": ";
        cout << stud;
        cout << " (prev: " << prev << ", next: " << next << ")" << endl;
    }
};

int Cell::cell_counter = 0;


#endif //TESTS_CELL_H
