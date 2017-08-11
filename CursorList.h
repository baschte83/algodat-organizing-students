/**
 * Created by Mikhail Slivinsky and Sebastian Baumann
 */

#ifndef TESTS_CURSORLIST_H
#define TESTS_CURSORLIST_H


#include "Student.h"

template <class T, int maxNumber> class CursorList {

public:
    typedef T value_type;

    /////////////////////////////////////////////////////////////////////////////////
    // Achtung: Hier beginnt die Klasse CursorIterator
    class CursorIterator {

        typedef CursorIterator iterator;

    private:
        int highestNumber;
        int start_freespace = 0;        // Zeigt auf den ersten freuen Platz
        int pointer;

    public:

        // Konstruktor ---------------------------------------------
        CursorIterator(int p){
            pointer = p;
        }

        // Getter und Setter ---------------------------------------
        int getHighestNumber() const{
            return highestNumber;
        }
        int getPointer() const{
            return pointer;
        }
        int getStart_Freespace() {
            return start_freespace;
        }
        void setHighestNumber(int hn) {
            this->highestNumber = hn;
        }
        void setPointer(int pn) {
            this->pointer = pn;
        }
        void setStart_Freespace(int fs) {
            start_freespace = fs;
        }


        // Operatorueberladungen ------------------------------------
        // Returns a reference to the current item. ????
        // TODO T& operator * () muss noch überöaden werden
        /*T& operator *(){
            return *array;
        }*/

        // Assigns other to this iterator.
        iterator operator = (const iterator rhs){
            setPointer(rhs.getPointer());
        }

        // Returns true if other points to a different item than this iterator; otherwise returns false.
        bool operator != (const iterator rhs) const{
            return (this->pointer != rhs.getPointer());
        }

        // Returns true if other points to the same item as this iterator; otherwise returns false.
        bool operator == (const iterator& rhs) const{
            return (this->pointer == rhs.getPointer());
        }

        // The prefix ++ operator (++it) advances the iterator to the next item in the set and returns an iterator to the new current item.
        iterator operator ++(){
            this->pointer+=1;
        }

        // The postfix ++ operator (it++) advances the iterator to the next item in the set and returns an iterator to the previously current item
        // TODO iterator operator ++(int) muss noch überladen werden
        /*iterator operator ++(int){
            ++(int)pointer;

            if(pointer> highestNumber){
                highestNumber = pointer;
            }
            return this;
        }*/
    };

    /////////////////////////////////////////////////////////////////////////////////
    // Achtung: Hier beginnt die Klasse CursorList

    typedef CursorIterator iterator;

private:

    /**
     * Struktur der Listeneinträge:
     * 1.) Leerer Eintrag: Mat-Nr.: 0 | Vorname: Max | Nachname: Muster | Geb-Dat.: 1012000 | prev: -2, next: -2
     * 2.) Erster Eintrag: Mat-Nr.: Number | Vorname: Name | Nachname: Surname | Geb-Dat.: Date | prev: -1, next: IndexNextCell
     * 3.) Letzte Eintrag: Mat-Nr.: Number | Vorname: Name | Nachname: Surname | Geb-Dat.: Date | prev: IndexPreviousCell, next: -1
     * 4.) Eintrag nach Löschen = leerer Eintrag
     */

    /**
     * ACHTUNG: für Suchen ist ein nicht gefundener Index IMMER -2. D.h. dass der Aufrufer
     * einer Suche immer per if-else abfragen muss, ob bei der Suche -2 als Ergebnis
     * zurückkommt!!
     */

    // Erzeugen eines Pointers zum durchlaufen der Liste "array"
    CursorIterator a = CursorIterator(0);

    // Erzeugen unserer Liste aus Cells zum Aufnehmen der Studenten
    T array[maxNumber];             // Erzeugung einer CursorList aus Cells

public:

    // Umsetzung geforderter Methoden ---------------------------
    bool empty() {
        bool ergebnis = false;
        // Suche nach einem Element mit prev ist -1 (also einem Start-Element)
        int indexOfEmptyElement = findNextCellIndex(-1);
        if (indexOfEmptyElement == -2) {
            // indexOfEmptyElement ist also -2
            // => es gibt kein Start-Element und damit ist die Liste leer
            ergebnis = true;
        }
        return ergebnis;
    }

    int size() {
        int numberOfEmptyElements = 0;
        int counter = 0;
        while (counter < maxNumber) {
            int tmp = array[a.getPointer()].getPrev();
            if (tmp == -2) {
                numberOfEmptyElements += 1;
            }
            ++a;
            counter++;
        }
        a.setPointer(0);    // Pointer-Reset nach Pointer-Operation
        return maxNumber - numberOfEmptyElements;
    }

    T& front() const{
        return array[0];
    }

    iterator begin() const{
        return CursorIterator(0);
    }

    iterator end() const{
        return CursorIterator(maxNumber);
    }

    // Einfügen von einem Studenten VOR dem Studenten mit der eingegebenen Matrikelnummer
    void insert(int insertBeforeMatNumber) {
        int tmp = findNextCellIndex(-1);
        if (tmp == -2) {
            // Falls die Liste leer ist, soll push_front mit dem Index des ersten leeren Elements aufgerufen werden.
            push_front(a.getStart_Freespace());
            // Versetzen des start_freespace-Indexes auf die nächste freie Cell
            int nextEmptyIndexForFree = findNextCellIndex(-2);
            a.setStart_Freespace(nextEmptyIndexForFree);

        } else {
            int indexToInsertBefore = findCellIndexOfMatNr(insertBeforeMatNumber); // Cell VOR der ich einfügen soll
            int indexOfFreeCell = a.getStart_Freespace();                       // Index einer freien Cell
            int indexOfCellBeforeFreeCell = array[indexToInsertBefore].getPrev(); // Index der Cell VOR der freien Cell

            // Falls der prev-Zeiger der Cell VOR der eingefügt werden soll -1 ist, ist die Cell VOR der eingefügt
            // werden soll die erste Cell in unserer Liste. Dann können wir einfach push_front aufrufen.
            if (array[indexToInsertBefore].getPrev() == -1) {
                push_front(a.getStart_Freespace());
                cout << "Sie haben erfolgreich einen neuen Studenten in die Liste eingefuegt." << endl;
            } else {
                array[indexOfCellBeforeFreeCell].setNext(indexOfFreeCell); // Der Next-Zeiger der Zelle VOR der freien Zelle zeigt auf freie Zelle
                array[indexOfFreeCell].setPrev(indexOfCellBeforeFreeCell); // Die freie Cell prev zeigt auf auf Cell davor
                array[indexOfFreeCell].setNext(indexToInsertBefore);       // Die freie Cell next auf auf Cell danach
                array[indexToInsertBefore].setPrev(indexOfFreeCell);       // Die Cell nach freie Cell zeigt auf freie Cell
                cout << "Bitte geben Sie Studentendaten in der Form MATRIKELNUMMER + Enter, Vorname + Enter, Nachname + Enter, Geburtsdatum + Enter ein:" << endl;
                cin >>  array[indexOfFreeCell].stud;    // Jetzt können Studentendaten in die freie Cell eingegeben werden
            }
            // Versetzen des start_freespace-Indexes auf die nächste freie Cell
            int nextEmptyIndexForFree = findNextCellIndex(-2);
            a.setStart_Freespace(nextEmptyIndexForFree);
        }
        cout << "Sie haben erfolgreich einen neuen Studenten in die Liste eingefuegt." << endl;
    }

    // Löschen mehrerer Studenten
    int erase(int start, int stop){

        int counter = 0;
        int n = start;
        while(counter<=stop-start){
            n = erase(n);
            counter++;
        }
        cout << "Sie haben die Studenten erfolgreich aus der Liste entfernt." << endl;
        return n;

    }


    // Löschen eines Studenten
    int erase(int adress){

        int result = 0;
        int prevElement =  array[adress].getPrev();
        int nextElement = array[adress].getNext();

        // unterscheiden in 3 Fälle Element ist am Anfang, am Ende oder mitten in der Liste

        if(prevElement == -1){

            array[array[adress].getNext()].setPrev(-1);
            result = array[adress].getPrev();

        } else if(nextElement == -1){
            array[array[adress].getPrev()].setNext(-1);
            result = array[adress].getPrev();

        } else {
            array[array[adress].getNext()].setPrev(prevElement);
            array[array[adress].getPrev()].setNext(nextElement);

            result = array[adress].getPrev();

        }

        array[adress].setPrev(-2);
        array[adress].setNext(-2);

        // Nun muss der Zeiger auf die erste leere Cell noch neu gesetzt werden => es muss eine neue leere Cell gefunden werden
        int nextEmptyIndexForFree = findNextCellIndex(-2);
        a.setStart_Freespace(nextEmptyIndexForFree);

        cout << "Sie haben den Studenten erfolgreich aus der Liste entfernt." << endl;
        return result;
    }


    // Push_Front fügt am Anfang der verketteten Liste einen neuen Studenten hinzu.
    void push_front(int emptyIndex) {

        int nextEmptyIndex = findNextCellIndex(-1);     // Findet die nächste Cell mit prev = -1 (also die ehemals erste Cell)
        if (nextEmptyIndex == -2) {
            // Es wurde keine Cell mit prev = -1 gefunden => die Liste ist noch leer und dieser Student hier ist der erste.
            array[emptyIndex].setNext(-1);              // aktuelle Cell ist letzte Cell => next = -1 (es gibt noch kein nächstes Element in der Liste
            array[emptyIndex].setPrev(-1);              // aktuelle Cell ist erste Cell => prev = -1 (es gibt kein vorheriges Element in der Liste)
        }
        else {
            // Es wurde ein ehemals erster Student gefunden => next muss auf den Index dieses Studenten gesetzt werden.
            array[nextEmptyIndex].setPrev(emptyIndex);  // Setzt prev vom alten ersten Element auf neues erstes Element
            array[emptyIndex].setNext(nextEmptyIndex);
        }
        // prev und next sind jetzt richtig gesetzt und es können die Studentendaten eingegeben werden.
        cout << "Bitte geben Sie Studentendaten in der Form ein:\nMATRIKELNUMMER + Enter, Vorname + Enter, Nachname + Enter, Geburtsdatum + Enter" << endl;
        cin >>  array[emptyIndex].stud;

        array[emptyIndex].setPrev(-1);
        // Nun muss der Zeiger auf die erste leere Cell noch neu gesetzt werden => es muss eine neue leere Cell gefunden werden
        int nextEmptyIndexForFree = findNextCellIndex(-2);
        a.setStart_Freespace(nextEmptyIndexForFree);

        cout << "Sie haben erfolgreich einen neuen Studenten zur Liste hinzugefuegt." << endl;

        /**
         * Sollte eine leere Cell gefunden werden, so wird start_freespace auf deren Index gestzt.
         * Wird keine leere Cell gefunden, so wird von findNextCell -2 zurückgeliefert und start_freespace
         * auch auf den Wert gesetzt, den findNextCell zurückliefert, in diesem Fall -2, was auch bedeutet,
         * dass es keine leere Cell mehr gibt.
         */
    }

    void pop_front(){
        bool findElement = false;
        int i = 0;
        // wenn Liste leer ist können wir auch keine Elemente entfernen
        if(!empty()){

            while(i<maxNumber && !findElement){
                // Anfangselement wurde gefunden
                if(array[i].getPrev() == -1){

                    // wir holen uns das nächste Element und initialisieren es als erstes Element
                    int next = array[i].getNext();
                    array[next].setPrev(-1);

                    // prev und next werden auf -2 gesetzt
                    array[i].setPrev(-2);
                    array[i].setNext(-2);

                    // Element wird als freier Punkt freigegeben
                    findElement = true;
                }
                i++;
            }
        }
        // Nun muss der Zeiger auf die erste leere Cell noch neu gesetzt werden => es muss eine neue leere Cell gefunden werden
        int nextEmptyIndexForFree = findNextCellIndex(-2);
        a.setStart_Freespace(nextEmptyIndexForFree);
        cout << "Sie haben den ersten Studenten erfolgreich aus der Liste entfernt." << endl;
    }


    // Sonstige Methoden ----------------------------------------
    // Anzeigen des Listeninhalts
    void printListContents(){
        for (int i = 0; i < maxNumber; ++i) {
            array[a.getPointer()].printInfo();
            ++a;
        }
        // Pointer-Reset nach Pointer-Operation
        a.setPointer(0);
    }

    // Anzeigen des Listeninhalts als verkettete Liste
    void printChainedList() {

        if (empty()) {
            cout << "\nDie Liste ist leer.\nEs kann leider nichts angezeigt werden." << endl;
        }
        else {
            cout << "\nDer Inhalt der verketteten Liste:" << endl;
            int startIndex = -1;
            bool atTheEnd = false;
            int counter = 0;
            a.setPointer(0); // Reset des Pointers
            int tmp = findNextCellIndex(startIndex);
            a.setPointer(tmp);
            while (!atTheEnd) {
                array[a.getPointer()].printInfo();
                a.setPointer(array[a.getPointer()].getNext());
                counter++;
                atTheEnd = a.getPointer() == -1;
            }
        }
        a.setPointer(0); // Reset des Pointers
    }


    //Such-Algorithmen ------------------------------------------

    // Gibt den Wert von start-freespace zurück. Darin ist der Index der naechsten freien Cell gespeichert.
    int findEmptyIndex() {
        return a.getStart_Freespace();
    }

    // Findet Cells, die einer bestimmten Matrikelnummer entsprechen. Liefert Index der Cell zurueck.
    int findCellIndexOfMatNr(int searchedValue) {
        bool found = false;
        int foundValue = 0;
        int result = -2;
        int counter = 0;
        while (!found && counter < maxNumber) {
            foundValue = array[a.getPointer()].getMatrikelnummer();
            if (foundValue == searchedValue) {
                result = a.getPointer();
                found = true;
            }
            else {
                found = false;
            }
            counter++;
            ++a;
        }
        a.setPointer(0);    // Reset des Iterators
        return result;
    }

    // Diese Suche findet die nächste Zelle, bei der in prev
    // der gesuchte Wert searchedValue steht
    int findNextCellIndex(int searchedValue) {
        bool found = false;
        int foundValue = 0;
        int result = -2;
        int counter = 0;
        while (!found && counter < maxNumber) {
            foundValue = array[a.getPointer()].getPrev();
            if (foundValue == searchedValue) {
                result = a.getPointer();
                found = true;
            }
            else {
                counter++;
                ++a;
            }
        }
        a.setPointer(0);    // Reset des Iterators
        return result;
    }

    /***
     * LÖSCHEN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     */
};

#endif //TESTS_CURSORLIST_H
