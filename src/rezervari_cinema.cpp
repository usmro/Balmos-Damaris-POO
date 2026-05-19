#include <iostream>
#include "Film.h"
#include "Sala.h"
#include "Rezervare.h"
#include "Cinematograf.h"
using namespace std;

int main() {
    Cinematograf c("Cinema City");

    Film f1("Inception", "SciFi", 148, "2D", 25.0);
    Film f2("Avatar", "Actiune", 162, "3D", 35.0);

    c.adaugaFilm(f1);
    c.adaugaFilm(f2);

    Sala s1(1, 3, 4);
    c.adaugaSala(s1);

    c.afisareFilme();
    cout << endl;

    c.afisareLocuri(1);
    cout << endl;

    try {
        c.realizeazaRezervare(1, f1, 0, 0);
        c.realizeazaRezervare(1, f1, 0, 0); // loc deja ocupat
    } catch (runtime_error& e) {
        cout << "Eroare: " << e.what() << endl;
    } catch (out_of_range& e) {
        cout << "Eroare: " << e.what() << endl;
    }

    return 0;
}