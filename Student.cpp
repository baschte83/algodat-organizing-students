/**
 * Created by Mikhail Slivinsky and Sebastian Baumann
 */

#include "Student.h"
#include <iostream>
#include <cstring>
using namespace std;

// Konstruktoren ----------------------------
// Initialisierung eines Stundenten mit Default-Werten
Student::Student(): matrikelnummer(0), vorname("Max"), nachname("Muster"), geburtsdatum(0) {}
// Initialisierung eines Stundenten mit übergebenen Werten
Student::Student(int mat_nr, char *name, char *surname, int geburtstag) {
    setMatrikelnummer(mat_nr);
    setVorname(name);
    setNachname(surname);
    setGeburtsdatum(geburtstag);
}


// Destruktor -------------------------------
Student::~Student() {};


// Getter -----------------------------------
int Student::getMatrikelnummer() const {
    return matrikelnummer;
}
char* Student::getVorname() {
    return this->vorname;
}
char* Student::getNachname() {
    return this->nachname;
}
int Student::getGeburtsdatum() const {
    return geburtsdatum;
}


// Setter -----------------------------------
void Student::setVorname(char *name){
    strcpy(this->vorname, name);
    /**
     * Funktionsweise:
     * strcpy(char * destination, const char * source)
     * Mit strcpy wird ein C String aus der Source in ein Array an der Adresse Destination
     * kopiert. Beides (vorname und nachname) muss so initialisiert werden.
     */
}
void Student::setNachname(char *surname) {
    strcpy(this->nachname, surname);
}
void Student::setMatrikelnummer(int nummer){
    this->matrikelnummer = nummer;
}
void Student::setGeburtsdatum(int gbd){
    this->geburtsdatum = gbd;
}


// Vergleich von Matrikelnummern ------------
bool Student::vergleicheMatrikelnummer(const Student &stud){
    return this->matrikelnummer == stud.matrikelnummer;
}


// Sonstige Methoden ------------------------
void Student::write(ostream &ostr) const {
    ostr << this->matrikelnummer << ", " << this->vorname << ", " << this->nachname << ", " << this->geburtsdatum;
}
void Student::read(istream &istr) {
    istr >> this->matrikelnummer >> this->vorname >> this->nachname >> this->geburtsdatum;
}


void printResult(Student student)
{
    cout << "Die Matrikelnummer ist: " << student.getMatrikelnummer() << std::endl;
    cout << "Der Nachname lautet:  "<< student.getNachname() << std::endl;
    cout << "DerVorname lautet: "  << student.getVorname() << std::endl;
    cout << "Das Geburtsdatum ist: " << student.getGeburtsdatum() << std::endl;
}