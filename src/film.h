#pragma once
#include <string>
using namespace std;

class Film {
private:
    string titlu;
    string gen;
    int durata;      
    string tip;      
    double pretBaza;

public:
    Film(string _titlu, string _gen, int _durata, string _tip, double _pret);
    string getTitlu();
    string getTip();
    double getPretBaza();
    void afisare(); 
};