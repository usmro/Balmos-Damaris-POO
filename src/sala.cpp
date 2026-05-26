#include "sala.h"
#include <iostream>
using namespace std;

Sala::Sala(int id, int r, int c) {
    this->id = id;
    randuri = r;
    coloane = c;
    locuri = vector<vector<int>>(r, vector<int>(c, 0));
}

void Sala::afisareLocuri() {
    cout << "Sala " << id << ":" << endl;
    for (int i = 0; i < randuri; i++) {
        for (int j = 0; j < coloane; j++) {
            if (locuri[i][j] == 0)
                cout << "[ ] ";
            else
                cout << "[X] ";
        }
        cout << endl;
    }
}

bool Sala::esteLiber(int rand, int col) {
    return locuri[rand][col] == 0;
}

void Sala::ocupaLoc(int rand, int col) {
    if (rand < 0 || rand >= randuri || col < 0 || col >= coloane) {
        throw out_of_range("Index invalid! Randul sau coloana nu exista.");
    }
    if (locuri[rand][col] == 1) {
        throw runtime_error("Locul este deja ocupat!");
    }
    locuri[rand][col] = 1;
}
int Sala::getId() { return id; }