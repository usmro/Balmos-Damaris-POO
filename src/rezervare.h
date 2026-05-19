#pragma once
#include "Film.h"
#include "Sala.h"
using namespace std;

class Rezervare {
private:
    Film film;
    Sala sala;
    int rand;
    int col;

public:
    Rezervare(Film f, Sala s, int r, int c);
    void afisare();
};