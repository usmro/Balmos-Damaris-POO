#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Film.h"
#include "Sala.h"
#include "Cinematograf.h"
#include "RezervareOnline.h"


#ifdef _WIN32
#include <windows.h>
#include <conio.h> 
#endif

using namespace std;


const string RESET   = "\033[0m";
const string SELECTAT = "\033[44m\033[37m"; 
const string CYAN    = "\033[36m";
const string BOLD    = "\033[1m";
const string ROSU    = "\033[31m";
const string VERDE   = "\033[32m"; 
const string GALBEN  = "\033[33m";
const string ALBASTRU = "\033[34m";

void curataEcranul() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void deseneazaMeniu(int selectieCurenta) {
    curataEcranul();
    cout << CYAN << "========================================" << RESET << endl;
    cout << BOLD << "     SISTEM REZERVARI CINEMA - MENIU    " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "Folositi tastele " << BOLD << "W (Sus)" << RESET << " si " << BOLD << "S (Jos)" << RESET << ", apoi apasati " << BOLD << "ENTER" << RESET << ".\n" << endl;

    string optiuni[] = {
        "1. Afisare filme disponibile",
        "2. Afisare harta locuri sala",
        "3. Realizeaza rezervare standard",
        "4. Realizeaza rezervare online",
        "5. Calculeaza pret bilet estimativ",
        "0. Iesire aplicatie"
    };

    for(int i = 0; i < 6; i++) {
        if(i == selectieCurenta) {
            cout << SELECTAT << " > " << optiuni[i] << " < " << RESET << endl;
        } else {
            cout << "   " << optiuni[i] << endl;
        }
    }
    cout << CYAN << "========================================" << RESET << endl;

}

int main() {
  
    
 Cinematograf cinema("Cinema City Suceava");
    
    Film f1("Inception", "SciFi", 148, "2D", 25.0);
    Film f2("Avatar", "Actiune", 162, "3D", 35.0);
    cinema.adaugaFilm(f1);
    cinema.adaugaFilm(f2);

    Sala s1(1, 3, 4); // ID 1, 3 rânduri, 4 coloane
    cinema.adaugaSala(s1);

    int pozitie = 0;
    int tasta;

    while (true) {
        deseneazaMeniu(pozitie);
        tasta = _getch();

        // Detectare taste direcționale sau W / S
        if (tasta == 'w' || tasta == 'W' || tasta == 72) { 
            if (pozitie > 0) pozitie--;
        } 
        else if (tasta == 's' || tasta == 'S' || tasta == 80) { 
            if (pozitie < 5) pozitie++;
        } 
        else if (tasta == 13) { // Tasta ENTER
            curataEcranul();
            
            // !!! LINIA MAGICĂ !!!
            // Curățăm complet orice Enter sau tastă rămasă în buffer înainte de a cere date prin cin
            cin.clear();
            
            // 1. Afisare filme disponibile
            if (pozitie == 0) {
                cout << BOLD << CYAN << "--- FILME DISPONIBILE ---\n" << RESET;
                cinema.afisareFilme();
            } 
            // 2. Afisare harta locuri sala
            else if (pozitie == 1) {
                int idSala;
                cout << "Introduceti ID-ul salii (ex: 1): ";
                if (cin >> idSala) {
                    cout << BOLD << CYAN << "\n--- STARE LOCURI SALA " << idSala << " ---\n" << RESET;
                    cinema.afisareLocuri(idSala);
                }
            } 
            // 3. Realizeaza rezervare standard
            else if (pozitie == 2) {
                int idSala, rand, col;
                cout << BOLD << CYAN << "--- REZERVARE STANDARD ---\n" << RESET;
                cout << "ID Sala (introduceti un numar): "; cin >> idSala;
                cout << "Rand: "; cin >> rand;
                cout << "Coloana: "; cin >> col;

                try {
                    cinema.realizeazaRezervare(idSala, f1, rand, col);
                    cout << VERDE << "\nRezervare efectuata cu succes in sistem!" << RESET << endl;
                }
                catch (const exception &e) {
                    cout << ROSU << "\nEroare la rezervare: " << e.what() << RESET << endl;
                }
            } 
            // 4. Realizeaza rezervare online
            else if (pozitie == 3) {
                int rand, col;
                string email;
                cout << BOLD << CYAN << "--- REZERVARE ONLINE ---\n" << RESET;
                cout << "Introduceti email client: "; cin >> email;
                cout << "Rand: "; cin >> rand;
                cout << "Coloana: "; cin >> col;

                try {
                    s1.ocupaLoc(rand, col);
                    RezervareOnline ro(f2, s1, rand, col, email);
                    cout << VERDE << "\n[Bilet Generat cu Succes]" << RESET << endl;
                    ro.afisare();
                }
                catch (const exception &e) {
                    cout << ROSU << "\nEroare online: " << e.what() << RESET << endl;
                }
            } 
            // 5. Calculeaza pret bilet estimativ
            else if (pozitie == 4) {
                string zi;
                cout << BOLD << GALBEN << "--- CALCULATOR PRET BILET ---\n" << RESET;
                cout << "Introduceti ziua saptamanii (ex: luni, sambata): "; cin >> zi;
                cout << "\nPret estimativ Inception (2D): " << VERDE << f1.calculeazaPret(zi) << " lei" << RESET << endl;
                cout << "\nPret estimativ Avatar (3D): " << VERDE << f2.calculeazaPret(zi) << " lei" << RESET << endl;
            } 
            // 0. Iesire aplicatie
            else if (pozitie == 5) {
                cout << BOLD << CYAN << "Iesire din aplicatie. O zi buna!" << RESET << endl;
                break;
            }
            
            // Ignorăm restul caracterelor din buffer înainte de a ne întoarce la meniul cu săgeți
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "\n" << GALBEN << "Apasati orice tasta pentru a reveni la meniu..." << RESET;
            _getch();
        }
    }
    return 0;
}