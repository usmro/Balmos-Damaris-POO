#include "cinematograf.h"
#include <iostream>
using namespace std;

Cinematograf::Cinematograf(string n) {
    nume = n;
}

void Cinematograf::adaugaFilm(Film f) {
    filme.push_back(f);
}

void Cinematograf::adaugaSala(Sala s) {
    sali.push_back(s);
}

void Cinematograf::afisareFilme() {
    cout << "Filme disponibile la " << nume << ":" << endl;
    for (int i = 0; i < filme.size(); i++) {
        filme[i].afisare();
    }
}

void Cinematograf::afisareLocuri(int idSala) {
    for (int i = 0; i < sali.size(); i++) {
        if (sali[i].getId() == idSala) {
            sali[i].afisareLocuri();
            return;
        }
    }
    cout << "Sala nu a fost gasita!" << endl;
}

void Cinematograf::realizeazaRezervare(int idSala, Film f, int rand, int col) {
    for (int i = 0; i < sali.size(); i++) {
        if (sali[i].getId() == idSala) {
            sali[i].ocupaLoc(rand, col);
            Rezervare r(f, sali[i], rand, col);
            rezervari.push_back(r);
            r.afisare();
            return;
        }
    }
}