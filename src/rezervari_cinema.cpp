#include <iostream>
#include <vector>
#include <string>
#include <limits>       
#include <stdexcept>
#include <conio.h>      

#ifdef _WIN32
#include <windows.h>
#endif

#include "Film.h"
#include "Sala.h"
#include "Cinematograf.h"
#include "RezervareOnline.h"

using namespace std;

#ifdef _WIN32
void activeazaCuloriWindows() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
void emiteSunet(int frecventa, int durata) {
    Beep(frecventa, durata);
}
#endif

// Constante pentru design profesional ANSI
const string RESET     = "\033[0m";
const string SELECTAT  = "\033[44m\033[1m\033[37m"; // Fundal Albastru, Text Alb Bold
const string CYAN      = "\033[36m";
const string BOLD      = "\033[1m";
const string ROSU      = "\033[31m";
const string VERDE     = "\033[32m";
const string GALBEN    = "\033[33m";
const string ALBASTRU  = "\033[34m";
const string LINIE     = "\033[38;5;244m"; // Gri pentru delimitatoare

void curataEcranul() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void deseneazaInterfataFixa(int selectieCurenta) {
    curataEcranul();
    cout << CYAN << "========================================================================" << RESET << endl;
    cout << BOLD << ALBASTRU << "                     SISTEM REZERVARI CINEMA - CONSOLA PRO" << RESET << endl;
    cout << CYAN << "========================================================================" << RESET << endl;
    cout << " Navigati cu " << BOLD << "Sagetile (Sus/Jos)" << RESET << " sau " << BOLD << "W/S" << RESET << ". Selectati cu tasta " << BOLD << "ENTER" << RESET << "." << endl;
    cout << LINIE << "------------------------------------------------------------------------" << RESET << endl;

    string optiuni[] = {
        "1. Afisare program complet filme",
        "2. Afisare harta interactiva locuri sala",
        "3. Realizeaza rezervare standard (La casierie)",
        "4. Realizeaza rezervare online (Cu confirmare email)",
        "5. Calculator dinamic pret bilet",
        "0. Iesire securizata aplicatie"
    };

    for(int i = 0; i < 6; i++) {
        if(i == selectieCurenta) {
            cout << SELECTAT << "  ► " << optiuni[i] << "   " << RESET << endl;
        } else {
            cout << "    " << optiuni[i] << endl;
        }
    }
    cout << CYAN << "========================================================================" << RESET << endl;
    cout << BOLD << " ZONA AFISARE REZULTATE: " << RESET << endl;
    cout << LINIE << "------------------------------------------------------------------------" << RESET << endl;
}

int main() {
    activeazaCuloriWindows();

    Cinematograf cinema("Cinema City Suceava");
    Film f1("Inception", "SciFi", 148, "2D", 25.0);
    Film f2("Avatar", "Actiune", 162, "3D", 35.0);
    cinema.adaugaFilm(f1);
    cinema.adaugaFilm(f2);

    Sala s1(1, 3, 4); 
    cinema.adaugaSala(s1);

    int pozitie = 0;
    int tasta;
    string zonaRezultate = " Selectati o optiune din meniul de mai sus pentru a genera date active.";

    while (true) {
        deseneazaInterfataFixa(pozitie);
        cout << zonaRezultate << endl;
        cout << LINIE << "------------------------------------------------------------------------" << RESET << endl;
        
        tasta = _getch();


        if (tasta == 'w' || tasta == 'W' || tasta == 72) { 
            if (pozitie > 0) {
                pozitie--;
                emiteSunet(600, 30); // Sunet click discret la navigare
            }
        } 
        else if (tasta == 's' || tasta == 'S' || tasta == 80) { 
            if (pozitie < 5) {
                pozitie++;
                emiteSunet(600, 30);
            }
        } 
        else if (tasta == 13) { // Tasta ENTER
            emiteSunet(800, 50); // Sunet de selectie
            cin.clear();
            
            if (pozitie == 0) {
                // Pentru a prelua output-ul functiilor fara a rescrie clasele, mutam executia direct sub meniu
                deseneazaInterfataFixa(pozitie);
                cout << BOLD << CYAN << " [PROGRAM FILME ACTIVE]\n" << RESET;
                cinema.afisareFilme();
                cout << "\n" << GALBEN << "Apasati orice tasta pentru a debloca meniul...";
                _getch();
            } 

            else if (pozitie == 1) {
                deseneazaInterfataFixa(pozitie);
                int idSala;
                cout << " Introduceti ID-ul salii (ex: 1): ";
                if (cin >> idSala) {
                    deseneazaInterfataFixa(pozitie);
                    cout << BOLD << CYAN << " [STARE LOCURI SALA " << idSala << "]\n" << RESET;
                    cinema.afisareLocuri(idSala);
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n" << GALBEN << "Apasati orice tasta pentru a debloca meniul...";
                _getch();
            } 

            else if (pozitie == 2) {
                deseneazaInterfataFixa(pozitie);
                int idSala, rand, col;
                cout << BOLD << CYAN << " [REZERVARE STANDARD]\n" << RESET;
                cout << " ID Sala: "; cin >> idSala;
                cout << " Rand: "; cin >> rand;
                cout << " Coloana: "; cin >> col;

                deseneazaInterfataFixa(pozitie);
                try {
                    cinema.realizeazaRezervare(idSala, f1, rand, col);
                    zonaRezultate = VERDE + " [SUCCES] Scaunul de la casierie a fost ocupat si confirmat în baza de date!" + RESET;
                    emiteSunet(1000, 200); // Sunet de succes
                }
                catch (const exception &e) {
                    zonaRezultate = ROSU + " [EROARE] " + e.what() + RESET;
                    emiteSunet(400, 300); // Sunet grav de eroare
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } 

            else if (pozitie == 3) {
                deseneazaInterfataFixa(pozitie);
                int rand, col;
                string email;
                cout << BOLD << CYAN << " [REZERVARE ONLINE]\n" << RESET;
                cout << " Introduceti email client: "; cin >> email;
                cout << " Rand: "; cin >> rand;
                cout << " Coloana: "; cin >> col;

                deseneazaInterfataFixa(pozitie);
                try {
                    s1.ocupaLoc(rand, col);
                    RezervareOnline ro(f2, s1, rand, col, email);
                    cout << VERDE << " [BILET ONLINE GENERAT]\n" << RESET;
                    ro.afisare();
                    zonaRezultate = VERDE + " [SUCCES] Confirmarea a fost expediata pe adresa: " + email + RESET;
                    emiteSunet(1000, 200);
                }
                catch (const exception &e) {
                    zonaRezultate = ROSU + " [EROARE ONLINE] " + e.what() + RESET;
                    emiteSunet(400, 300);
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n" << GALBEN << "Apasati orice tasta pentru a debloca meniul...";
                _getch();
            } 

            else if (pozitie == 4) {
                deseneazaInterfataFixa(pozitie);
                string zi;
                cout << BOLD << GALBEN << " [CALCULATOR DINAMIC PRET]\n" << RESET;
                cout << " Introduceti ziua saptamanii (ex: luni, duminica): "; cin >> zi;
                
                deseneazaInterfataFixa(pozitie);
                cout << BOLD << GALBEN << " [TARIFE ESTIMATE PENTRU ZIUA: " << zi << "]\n" << RESET;
                cout << "  • Inception (Tehnologie 2D): " << VERDE << f1.calculeazaPret(zi) << " lei" << RESET << endl;
                cout << "  • Avatar (Tehnologie 3D):    " << VERDE << f2.calculeazaPret(zi) << " lei" << RESET << endl;
                zonaRezultate = GALBEN + " [INFO] Tariful include automat taxele de weekend si optiunile 3D." + RESET;
                
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n" << GALBEN << "Apasati orice tasta pentru a debloca meniul...";
                _getch();
            } 
            else if (pozitie == 5) {
                curataEcranul();
                cout << BOLD << ALBASTRU << "Sistemul s-a inchis securizat. O zi buna!" << RESET << endl;
                emiteSunet(500, 100);
                break;
            }
        }
        
    }
    return 0;
}