#pragma once
#include <string>
#include <vector>
using namespace std;

class Sala {
private:
    int id;
    int randuri;
    int coloane;
    vector<vector<int>> locuri;

public:
    Sala(int id, int r, int c);
    void afisareLocuri();
    bool esteLiber(int rand, int col);
    void ocupaLoc(int rand, int col);
    int getId();
};