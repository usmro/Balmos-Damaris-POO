#pragma once
#include <string>
#include "film.h"
using namespace std;

class ICinemaService {
public:
    virtual void afisareFilme() = 0;
    virtual void afisareLocuri(int idSala) = 0;
    virtual void realizeazaRezervare(int idSala, Film f, int rand, int col) = 0;
    virtual ~ICinemaService() {}
};