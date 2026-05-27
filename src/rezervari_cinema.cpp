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
    
    // Setam consola pe UTF-8 pentru a randa perfect marginile duble (grafica ASCII)
    SetConsoleOutputCP(65001); 
}
void emiteSunet(int frecventa, int durata) {
    Beep(frecventa, durata);
}
#else
void activeazaCuloriWindows() {}
void emiteSunet(int frecventa, int durata) {} 
#endif

// Constante pentru culori ANSI
const string RESET     = "\033[0m";
const string SELECTAT  = "\033[44m\033[1m\033[37m"; // Fundal Albastru, Text Alb Bold
const string CYAN      = "\033[36m";
const string BOLD      = "\033[1m";
const string ROSU      = "\033[31m";
const string VERDE     = "\033[32m";
const string GALBEN    = "\033[33m";
const string ALBASTRU  = "\033[34m";

// Funcție care redesenează DOAR meniul, lăsând restul ecranului intact!
void deseneazaMeniuPersistent(int selectieCurenta, const string& status) {
    cout << "\033[H"; // Magia: Mută cursorul stânga-sus FĂRĂ să șteargă ecranul!
    
    cout << CYAN << "╔══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║" << BOLD << ALBASTRU << "               SISTEM REZERVARI CINEMA - DASHBOARD PRO                " << RESET << CYAN << "║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════╣\n";
    cout << "║" << RESET << " Navigare: W/S sau Sageti | Selectare: ENTER                          " << CYAN << "║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════╣\n" << RESET;

    string optiuni[] = {
        "1. Afisare program complet filme",
        "2. Afisare harta interactiva locuri sala",
        "3. Realizeaza rezervare standard (La casierie)",
        "4. Realizeaza rezervare online (Cu confirmare email)",
        "5. Calculator dinamic pret bilet",
        "0. Iesire securizata aplicatie"
    };

    // Desenăm opțiunile aliniate perfect în cutie
    for(int i = 0; i < 6; i++) {
        cout << CYAN << "║ ";
        if(i == selectieCurenta) {
            string text = "  > " + optiuni[i];
            cout << SELECTAT << text << string(66 - text.length(), ' ') << RESET << CYAN << " ║\n";
        } else {
            string text = "    " + optiuni[i];
            cout << RESET << text << string(66 - text.length(), ' ') << CYAN << " ║\n";
        }
    }
    cout << "╠══════════════════════════════════════════════════════════════════════╣\n";
    
    // Afișăm statusul dinamic la baza meniului
    string statusText = " STATUS: " + status;
    if(statusText.length() < 68) statusText.append(68 - statusText.length(), ' ');
    else statusText = statusText.substr(0, 68);
    
    cout << "║" << GALBEN << BOLD << statusText << RESET << CYAN << "║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════╝\n" << RESET;
}

int main() {
    activeazaCuloriWindows();

    // Curățăm tot ecranul o singură dată la pornirea aplicației
    cout << "\033[2J\033[H"; 

    Cinematograf cinema("Cinema City Suceava");
    Film f1("Inception", "SciFi", 148, "2D", 25.0);
    Film f2("Avatar", "Actiune", 162, "3D", 35.0);
    cinema.adaugaFilm(f1);
    cinema.adaugaFilm(f2);

    Sala s1(1, 3, 4); 
    cinema.adaugaSala(s1);

    int pozitie = 0;
    int tasta;
    string status = "Sistem initializat. Asteptare comenzi.";

    while (true) {
        deseneazaMeniuPersistent(pozitie, status);
        tasta = _getch();


        if (tasta == 'w' || tasta == 'W' || tasta == 72) { 
            if (pozitie > 0) {
                pozitie--;
                status = "Navigare...";
                emiteSunet(600, 30); 
            }
        } 
        else if (tasta == 's' || tasta == 'S' || tasta == 80) { 
            if (pozitie < 5) {
                pozitie++;
                status = "Navigare...";
                emiteSunet(600, 30);
            }
        } 
        else if (tasta == 13) { // Când se apasă ENTER
            emiteSunet(800, 50); 
            cin.clear();
            
            // Această comandă șterge DOAR ce este sub meniu (linia 15 în jos) pregătind zona pentru date noi
            cout << "\033[15;1H\033[0J"; 
            
            if (pozitie == 0) {
                status = "Lista filmelor a fost generata.";
                deseneazaMeniuPersistent(pozitie, status); // Actualizăm bara de status
                cout << "\033[15;1H\033[0J"; // Ne asigurăm că zona e curată
                
                cout << BOLD << CYAN << "\n [PROGRAM FILME ACTIVE]\n\n" << RESET;
                cinema.afisareFilme();

            } 

            else if (pozitie == 1) {
                status = "Asteptare introducere ID sala...";
                deseneazaMeniuPersistent(pozitie, status);
                cout << "\033[15;1H\033[0J";
                
                int idSala;
                cout << "\n Introduceti ID-ul salii (ex: 1): ";
                if (cin >> idSala) {
                    cout << BOLD << CYAN << "\n [STARE LOCURI SALA " << idSala << "]\n\n" << RESET;
                    cinema.afisareLocuri(idSala);
                    status = "Harta a fost generata cu succes.";
                } else {
                    status = "Eroare la citire ID.";
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            } 

            else if (pozitie == 2) {
                status = "Se proceseaza rezervarea standard...";
                deseneazaMeniuPersistent(pozitie, status);
                cout << "\033[15;1H\033[0J";
                
                int idSala, rand, col;
                cout << BOLD << CYAN << "\n [REZERVARE STANDARD]\n\n" << RESET;
                cout << " ID Sala: "; cin >> idSala;
                cout << " Rand: "; cin >> rand;
                cout << " Coloana: "; cin >> col;


                try {
                    cinema.realizeazaRezervare(idSala, f1, rand, col);
                    status = "SUCCES: Rezervare confirmata in sistem!";
                    cout << VERDE << "\n [CONFIRMARE] Locul a fost rezervat cu succes!\n" << RESET;
                    emiteSunet(1000, 200); 
                }
                catch (const exception &e) {
                    status = "EROARE: Tranzactie respinsa.";
                    cout << ROSU << "\n [EROARE SISTEM] " << e.what() << "\n" << RESET;
                    emiteSunet(400, 300); 
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } 

            else if (pozitie == 3) {
                status = "Se proceseaza rezervarea online...";
                deseneazaMeniuPersistent(pozitie, status);
                cout << "\033[15;1H\033[0J";
                
                int rand, col;
                string email;
                cout << BOLD << CYAN << "\n [REZERVARE ONLINE]\n\n" << RESET;
                cout << " Introduceti email client: "; cin >> email;
                cout << " Rand: "; cin >> rand;
                cout << " Coloana: "; cin >> col;


                try {
                    s1.ocupaLoc(rand, col);
                    RezervareOnline ro(f2, s1, rand, col, email);
                    status = "SUCCES: Bilet trimis pe email!";
                    cout << VERDE << "\n [BILET ONLINE GENERAT]\n\n" << RESET;
                    ro.afisare();

                    emiteSunet(1000, 200);

                }
                catch (const exception &e) {
                    status = "EROARE: Generare bilet online esuata.";
                    cout << ROSU << "\n [EROARE SISTEM] " << e.what() << "\n" << RESET;
                    emiteSunet(400, 300);
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            } 

            else if (pozitie == 4) {
                status = "Asteptare introducere zi...";
                deseneazaMeniuPersistent(pozitie, status);
                cout << "\033[15;1H\033[0J";
                
                string zi;
                cout << BOLD << GALBEN << "\n [CALCULATOR DINAMIC PRET]\n\n" << RESET;
                cout << " Introduceti ziua saptamanii (ex: luni, duminica): "; cin >> zi;
                
                cout << BOLD << GALBEN << "\n [TARIFE ESTIMATE PENTRU ZIUA: " << zi << "]\n\n" << RESET;
                cout << "  - Inception (Tehnologie 2D): " << VERDE << f1.calculeazaPret(zi) << " lei\n" << RESET;
                cout << "  - Avatar (Tehnologie 3D):    " << VERDE << f2.calculeazaPret(zi) << " lei\n" << RESET;
                
                status = "Calculator pret actualizat cu succes.";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            } 
            else if (pozitie == 5) {
                cout << "\033[2J\033[H"; // Curăță tot pentru ieșire
                cout << BOLD << ALBASTRU << "Sistemul s-a inchis securizat. O zi buna!" << RESET << endl;
                emiteSunet(500, 100);
                break;
            }
        }
        
    }
    return 0;
}