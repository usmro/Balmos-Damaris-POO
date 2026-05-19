#pragma once
#include "Rezervare.h"
#include <string>
using namespace std;

class RezervareOnline : public Rezervare {
private:
    string emailClient;

public:
    RezervareOnline(Film f, Sala s, int r, int c, string email);
    void afisare();
};