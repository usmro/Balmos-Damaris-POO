#include <iostream>
#include <limits>
#include "film.h"
#include "sala.h"
#include "rezervare.h"
#include "cinematograf.h"
#include "RezervareOnline.h"


#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;


const string RESET   = "\033[0m";
const string ROSU    = "\033[31m";
const string VERDE   = "\033[32m";
const string GALBEN  = "\033[33m";
const string ALBASTRU = "\033[34m";
const string CYAN    = "\033[36m";
const string BOLD    = "\033[1m";

void activeazaCuloriWindows() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void afiseazaMeniu() {
    cout << CYAN << "\n========================================" << RESET << endl;
    cout << BOLD << ALBASTRU << "     SISTEM REZERVARI CINEMA - MENIU    " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << GALBEN << "1." << RESET << " Afisare filme disponibile" << endl;
    cout << GALBEN << "2." << RESET << " Afisare harta locuri sala" << endl;
    cout << GALBEN << "3." << RESET << " Realizeaza rezervare standard (In consola)" << endl;
    cout << GALBEN << "4." << RESET << " Realizeaza rezervare online (Cu email)" << endl;
    cout << GALBEN << "5." << RESET << " Calculeaza pret bilet estimativ" << endl;
    cout << ROSU << "0." << RESET << " Iesire aplicatie" << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << BOLD << "Introduceti optiunea dorita: " << RESET;
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

    int optiune;
    do {
        afiseazaMeniu();
        if (!(cin >> optiune)) {
            cout << ROSU << "Optiune invalida! Va rugam introduceti un numar." << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (optiune) {
            case 1: {
                cout << BOLD << ALBASTRU << "\n--- FILME DISPONIBILE ---" << RESET << endl;
                cinema.afisareFilme();
                break;
            }
            case 2: {
                int idSala;
                cout << "Introduceti ID-ul salii (ex: 1): ";
                cin >> idSala;
                cout << BOLD << ALBASTRU << "\n--- STARE LOCURI SALA " << idSala << " ---" << RESET << endl;
                cinema.afisareLocuri(idSala);
                break;
            }
            case 3: {
                int idSala, rand, col;
                cout << BOLD << CYAN << "\n--- REZERVARE LOC LA CINEMA ---" << RESET << endl;
                cout << "ID Sala: "; cin >> idSala;
                cout << "Rand: "; cin >> rand;
                cout << "Coloana: "; cin >> col;

                try {
                    cinema.realizeazaRezervare(idSala, f1, rand, col);
                    cout << VERDE << "Rezervare efectuata cu succes in sistem!" << RESET << endl;
                }
                catch (const exception &e) {
                    cout << ROSU << "Eroare la rezervare: " << e.what() << RESET << endl;
                }
                break;
            }
            case 4: {
                int rand, col;
                string email;
                cout << BOLD << CYAN << "\n--- REZERVARE ONLINE ---" << RESET << endl;
                cout << "Introduceti email-ul dvs: "; cin >> email;
                cout << "Rand dorit: "; cin >> rand;
                cout << "Coloana dorita: "; cin >> col;

                try {
                    s1.ocupaLoc(rand, col);
                    RezervareOnline ro(f2, s1, rand, col, email);
                    cout << VERDE << "\n[Bilet Generat]" << RESET << endl;
                    ro.afisare();
                }
                catch (const exception &e) {
                    cout << ROSU << "Eroare online: " << e.what() << RESET << endl;
                }
                break;
            }
            case 5: {
                string zi;
                cout << BOLD << GALBEN << "\n--- CALCULATOR PRET BILET ---" << RESET << endl;
                cout << "Introduceti ziua (ex: luni, sambata): ";
                cin >> zi;
                cout << "Pret estimativ Inception (2D): " << VERDE << f1.calculeazaPret(zi) << " lei" << RESET << endl;
                cout << "Pret estimativ Avatar (3D): " << VERDE << f2.calculeazaPret(zi) << " lei" << RESET << endl;
                break;
            }
            case 0:
                cout << BOLD << ALBASTRU << "\nVa multumim! O zi buna!" << RESET << endl;
                break;
            default:
                cout << ROSU << "Optiune inexistenta! Incercati din nou." << RESET << endl;
        }
    } while (optiune != 0);

    return 0;
}