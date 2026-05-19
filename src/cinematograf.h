#pragma once
#include <vector>
#include "Film.h"
#include "Sala.h"
#include "Rezervare.h"
using namespace std;

class Cinematograf {
private:
    string nume;
    vector<Film> filme;
    vector<Sala> sali;
    vector<Rezervare> rezervari;

public:
    Cinematograf(string n);
    void adaugaFilm(Film f);
    void adaugaSala(Sala s);
    void afisareFilme();
    void afisareLocuri(int idSala);
    void realizeazaRezervare(int idSala, Film f, int rand, int col);
};