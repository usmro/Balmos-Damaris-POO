#include <iostream>
#include <vector>
#include <string>
#include "Film.h"
#include "Sala.h"
#include "Cinematograf.h"
#include "RezervareOnline.h"


#ifdef _WIN32
#include <windows.h>
#include <conio.h> // Pentru _getch() pe Windows
#else
#include <termios.h>
#include <unistd.h>
// Implementare getch() custom pentru Linux în caz că rulezi pe Ubuntu
int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

using namespace std;

// Culori ANSI
const string RESET   = "\033[0m";
const string SELECTAT = "\033[44m\033[37m"; // Fundal Albastru, Text Alb pentru opțiunea curentă
const string CYAN    = "\033[36m";
const string BOLD    = "\033[1m";

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

    cinema.adaugaFilm(f1);
    Sala s1(1, 3, 4);
    cinema.adaugaSala(s1);

    int pozitie = 0;
    int tasta;

    while (true) {
        deseneazaMeniu(pozitie);
        tasta = _getch();

        // Gestionare taste W/S sau tastele direcționale standard
        if (tasta == 'w' || tasta == 'W' || tasta == 72) { // 72 este codul pentru sageata sus
            if (pozitie > 0) pozitie--;
        } 
        else if (tasta == 's' || tasta == 'S' || tasta == 80) { // 80 este codul pentru sageata jos
            if (pozitie < 5) pozitie++;
        } 
        else if (tasta == 13) { // 13 este codul pentru tasta ENTER
            curataEcranul();
            
            if (pozitie == 0) {
                cinema.afisareFilme();
            } 
            else if (pozitie == 1) {
                cinema.afisareLocuri(1);
            } 
            else if (pozitie == 5) {
                cout << "Iesire din aplicatie..." << endl;
                break;
            }
            
            cout << "\nApasati orice tasta pentru a reveni la meniu...";
            _getch();
        }
    }
    return 0;
}