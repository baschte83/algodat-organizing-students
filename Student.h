/**
 * Created by Mikhail Slivinsky and Sebastian Baumann
 */

#ifndef TESTS_STUDENT_H
#define TESTS_STUDENT_H


#include <iostream>
using namespace std;

class Student {

    // Definition der Attribute von Student
    int matrikelnummer;
    char vorname[10];
    char nachname[10];
    int geburtsdatum;

    // Definition der benötigten default-Werte
    int defaultMatrikelnummer = 0;

public:
    // Konstruktoren ----------------------------
    Student();
    Student(int mat_nr, char* name, char* surname, int geburtstag);


    // Destruktor -------------------------------
    ~Student();


    // Getter -----------------------------------
    int getMatrikelnummer() const;
    char* getVorname();
    char* getNachname();
    int getGeburtsdatum() const;


    // Setter -----------------------------------
    void setMatrikelnummer(int matrikelnummer);
    void setVorname(char *name);
    void setNachname(char *surname);
    void setGeburtsdatum(int geburtsdatum);


    // Vergleich von Matrikelnummern ------------
    bool vergleicheMatrikelnummer(const Student &stud);


    // Sonstige Methoden ------------------------
    virtual void write(ostream& ostr) const;
    virtual void read(istream& istr);

    // read wird constant definiert weil stud Constant ist -.-
    friend ostream& operator<<(ostream& ostr, const Student& stud) {
        stud.write(ostr);
        return ostr;
    }

    friend istream& operator>>(istream& istr, Student& stud ) {
        stud.read(istr);
        return istr;
    }
};


#endif //TESTS_STUDENT_H
