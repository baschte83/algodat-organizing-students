/**
 * Created by Mikhail Slivinsky and Sebastian Baumann
 */

#include <iostream>
#include "CursorList.h"
#include "Cell.h"
#include <vector>
using namespace std;

int main(int argc, char*argv[]) {

    /**
     * Funktionsweise unseres Programms:
     * Wir erzeugen eine Liste aus "Cells". Jeder dieser Cells ist ein Student
     * und zwei Zeiger, einer, der in der verketteten Liste auf die Vorgänger-Cell
     * zeigt (prev) und einen, der auf die Nachfolger-Cell zeigt (next). Um sinnvoll
     * durch unsere Liste navigieren zu können, haben wir uns Default-Werte einfallen
     * lassen.
     * Default-Werte für leere Cell:
     * - prev = -2
     * - next = -2
     *
     * Default-Werte für erste und letzte Cell in der verketteten Liste:
     * - Erste Cell:
     *      * prev = -1
     *      * next = Zeigt auf nächste Cell
     *
     * - Zweite Cell:
     *      * prev = Zeigt auf vorherige Cell
     *      * next = -1
     *
     * Unsere Liste wird automatisch beim Aufrufen des Programms mit 10 Cells erzeugt.
     * Jede Cell hat von Haus aus einen Studenten.
     * Default-Werte für einen leeren Studenten:
     * - Matriklenummer: 0
     * - Vorname: Max
     * - Nachname: Muster
     * - Geburtsdatum: 0
     *
     * Aus irgendwelchen Gründen, die wir nicht herausfinden konnten, können wir keine
     * Integer-Werte mit einer führenden 0 (Null) eingeben, da diese Werte sofort als
     * Octa-Werte interpretiert werden. Auch war es uns leider nicht möglich, deutsche
     * Umlaute auszugeben. Daher haben wir bei allen Ausgaben die Umlaute umgeschrieben:
     * ä -> ae, ö -> oe, ü -> ue.
     *
     * Ausgabe: // Beispiel: Student 8: 999, Max, Muster, 0 (prev: -1, next: 7)
     * Objekt: Student, Objekt-ID: 8, Matrikelnummer 999, Name Max, Nachname Muster, Geburtsdatum 0.
     */


    // Initialsierung unserer Liste
    CursorList<Cell, 10> myList;

    // Ausgabe der Menüoptionen
    cout << "Bitte waehlen Sie eine der folgenden Optionen:\n" << endl;
    cout << "add        :   Neuen Studenten hinzufuegen" << endl;
    cout << "pop        :   Ersten Studenten in der Liste loeschen" << endl;
    cout << "remove     :   Studenten entfernen" << endl;
    cout << "erase      :   Studenten von bis entfernen" << endl;
    cout << "show       :   Gesamte Liste anzeigen" << endl;    // entfernen vor Abgabe
    cout << "showc      :   Gesamte Liste als verkette Liste anzeigen" << endl;
    cout << "empty      :   Ist die Liste leer?" << endl;
    cout << "size       :   Groesser der Liste anzeigen" << endl;
    cout << "insert     :   Einen Studenten einfuegen" << endl;
    cout << "help       :   Menue-Punkte anzeigen" << endl;
    cout << "quit       :   Programm beenden\n" << endl;
    cout << "BITTE BEACHTEN SIE: Geben Sie Nummern bitte immer\nohne fuehrende 0 ein. Dankeschoen." << endl;


    // Einlesen des Menuewunsches aus der Konsole
    string commando = "e";
    int menue = 0;


    // Unser Menue laeuft in einer "endlosen" do-while-Schleife, in der eine switch-Anweisung läuft,
    // die nur unterbrochen wird, wenn man per "quit" Anweisung die Bedingung der do-while-Schleife
    // auf false setzt.
    do {
        // Eingabeaufforderung an den Benutzer
        cout << "\nBitte geben Sie ein Kommando ein: " << endl;
        cin >> commando;

        // Umwandlung der Strings in int-Nummern, um diese dann im switch unten verwenden zu können.
        if (commando == "add") {
            menue = 1;
        } else if (commando == "remove") {
            menue = 2;
        } else if (commando == "show") {
            menue = 3;
        } else if (commando == "insert") {
            menue = 4;
        } else if (commando == "help") {
            menue = 5;
        } else if (commando == "quit") {
            menue = 6;
        } else if (commando == "empty") {
            menue = 7;
        } else if (commando == "size") {
            menue = 8;
        } else if (commando == "showc") {
            menue = 9;
        } else if (commando == "pop") {
            menue = 10;
        } else if (commando == "erase") {
            menue = 11;
        } else {
            menue = 666;
        }

        // Hier beginnt die switch-Anweisung, über die in die richtige Methode gesprungen wird.
        switch (menue) {
            case 1:
            {
                int indexFound = myList.findEmptyIndex();
                if (indexFound != -2) {
                    myList.push_front(indexFound);
                }
                else {
                    cout << "Leider ist in der Liste kein freier Platz zum hinzufuegen.\nBitte loeschen Sie erst einen Studenten." << endl;
                }
                menue = 10000;
                break;
            }
            case 2:
            {
                int mat_nr;
                cout << "Geben Sie bitte die Matrikelnummer des zu loeschenden Studenten an." << endl;
                cin >> mat_nr;
                mat_nr = myList.findCellIndexOfMatNr(mat_nr);
                myList.erase(mat_nr);
                menue = 10000;
                break;
            }
            case 3:
            {
                myList.printListContents();
                menue = 10000;
                break;
            }
            case 4:
            {
                int indexFound = myList.findEmptyIndex();
                if (indexFound != -2) {
                    cout << "Bitte geben Sie eine Matrikelnummer ein, vor der der neue Student eingefuegt werden soll:" << endl;
                    int mat_nr;
                    cin >> mat_nr;
                    myList.insert(mat_nr);
                }
                else {
                    cout << "Leider ist in der Liste kein freier Platz zum einfuegen.\nBitte loeschen Sie erst einen Studenten." << endl;
                }
                menue = 10000;
                break;
            }
            case 5:
            {
                cout << "\nBitte waehlen Sie eine der folgenden Optionen:\n" << endl;
                cout << "add        :   Neuen Studenten hinzufuegen" << endl;
                cout << "pop        :   Ersten Studenten in der Liste loeschen" << endl;
                cout << "remove     :   Studenten entfernen" << endl;
                cout << "erase      :   Studenten von bis entfernen" << endl;
                cout << "show       :   Gesamte Liste anzeigen" << endl;    // entfernen vor Abgabe
                cout << "showc      :   Gesamte Liste als verkette Liste anzeigen" << endl;
                cout << "empty      :   Ist die Liste leer?" << endl;
                cout << "size       :   Groesser der Liste anzeigen" << endl;
                cout << "insert     :   Einen Studenten einfuegen" << endl;
                cout << "help       :   Menue-Punkte anzeigen" << endl;
                cout << "quit       :   Programm beenden\n" << endl;
                cout << "BITTE BEACHTEN SIE: Geben Sie Nummern bitte immer\nohne fuehrende 0 ein. Dankeschoen." << endl;
                menue = 10000;
                break;
            }
            case 6:
            {
                menue = -1;
                break;
            }
            case 7:
            {
                bool result = myList.empty();
                if (result) {
                    cout << "Die Liste ist leer." << endl;
                } else {
                    cout << "Die Liste ist nicht leer." << endl;
                }
                menue = 10000;
                break;
            }
            case 8:
            {
                int sizeOfList = myList.size();
                cout << "Die Liste hat " << sizeOfList << " Elemente." << endl;
                menue = 10000;
                break;
            }
            case 9:
            {
                myList.printChainedList();
                menue = 10000;
                break;
            }
            case 10:
            {
                int indexFound = myList.findNextCellIndex(-1);
                if (indexFound != -2) {
                    myList.pop_front();
                }
                else {
                    cout << "Leider ist die Liste leer uns es kann nichts daraus geloescht werden.\nBitte fuegen Sie erst Studenten zur Liste hinzu." << endl;
                }

                menue = 10000;
                break;
            }
            case 11:
            {
                int start_mat_nr;
                int end_mat_nr;
                cout << "Geben Sie bitte eine Start-Matrikelnummer zum loeschen an." << endl;
                cin >> start_mat_nr;
                cout << "Geben Sie bitte eine End-Matrikelnummer zum loeschen an." << endl;
                cin >> end_mat_nr;
                start_mat_nr = myList.findCellIndexOfMatNr(start_mat_nr);
                end_mat_nr = myList.findCellIndexOfMatNr(end_mat_nr);
                myList.erase(start_mat_nr, end_mat_nr);
                menue = 10000;
                break;
            }
            case 666:
            {
                cout << "\nUngueltige Eingabe.\nBitte geben Sie ein gueltiges Kommando ein.\nMit <h> koennen Sie sich die moeglichen Kommandos nochmals anzeigen lassen.\n" << endl;
                menue = 10000;
            }
        }
    } while (menue != -1);

    cout << "\nDas Program wurde erfolgreich beendet." << endl;

    return 0;
}
