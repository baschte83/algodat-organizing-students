/**
 * Created by Mikhail Slivinsky and Sebastian Baumann
 */

#ifndef TESTS_CELL_H
#define TESTS_CELL_H

#include "Student.h"
using namespace std;

class Cell {

    // Pointer to the previous cell of this cell object in a linked list
    int prev;

    // Pointer to the next cell of this cell object in a linked list
    int next;

    // Counter to count cells
    static int cell_counter;

    // ID of every single cell
    const int myCounter = cell_counter;

    // Constant value to determine that a cell object has no previous or next cell yet
    const int defaultIndexNotSet = -2;

    // Constant value to determine whether this cell object is a start (or a stop) of the linked list or not
    const int defaultIndexStartStop = -1;

public:

    // Student stored in a cell
    Student stud;

    // Constructor
    // The constructor of a cell automatically sets prev and next to the default value -2.
    Cell() {
        prev = defaultIndexNotSet;
        next = defaultIndexNotSet;
        ++cell_counter;
    }


    // Destructor
    ~Cell() {
        --cell_counter;
    }

    // Returns the previous cell of this cell object
    int getPrev() {
        return this->prev;
    }

    // Returns the next cell of this cell object
    int getNext() {
        return this->next;
    }

    // Returns the matriculation number of this cell object
    int getMatrikelnummer() {
        return this->stud.getMatrikelnummer();
    }

    // Method sets the previous cell of this cell object
    void setPrev(int p) {
        prev = p;
    }

    // Method sets the next cell of this cell object
    void setNext(int n) {
        next = n;
    }

    // Returns the actual value of the cell counter
    int get_cell_counter() const{
        return myCounter;
    };

    // Method prints every value of this cell object to the screen
    void printInfo() {
        cout << "Student " << get_cell_counter() << ": ";
        cout << stud;
        cout << " (prev: " << prev << ", next: " << next << ")" << endl;
    }
};

int Cell::cell_counter = 0;


#endif //TESTS_CELL_H
