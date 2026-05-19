#include "Film.h"
#include <iostream>
using namespace std;

Film::Film(string _titlu, string _gen, int _durata, string _tip, double _pret) {
    titlu = _titlu;
    gen = _gen;
    durata = _durata;
    tip = _tip;
    pretBaza = _pret;
}

string Film::getTitlu() { return titlu; }
string Film::getTip()   { return tip; }
double Film::getPretBaza() { return pretBaza; }

void Film::afisare() {
    cout << "Film: " << titlu 
         << " | Gen: " << gen 
         << " | Durata: " << durata << " min"
         << " | Tip: " << tip 
         << " | Pret: " << pretBaza << " lei" << endl;
}