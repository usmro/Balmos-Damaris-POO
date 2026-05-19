#include "RezervareOnline.h"
#include <iostream>
using namespace std;

RezervareOnline::RezervareOnline(Film f, Sala s, int r, int c, string email)
    : Rezervare(f, s, r, c) {
    emailClient = email;
}

void RezervareOnline::afisare() {
    Rezervare::afisare();
    cout << "Email client: " << emailClient << endl;
}