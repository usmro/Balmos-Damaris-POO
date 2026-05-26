#include "rezervare.h"
#include <iostream>
using namespace std;

Rezervare::Rezervare(Film f, Sala s, int r, int c) : film(f), sala(s) {
    rand = r;
    col = c;
}

void Rezervare::afisare() {
    cout << "Rezervare: ";
    film.afisare();
    cout << "Sala: " << sala.getId() 
         << " | Loc: rand " << rand 
         << ", coloana " << col << endl;
}