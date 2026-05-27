#include <iostream>
#include <cassert>
#include "Sala.h"
#include "Film.h"

using namespace std;

void ruleazaTesteAutomate() {
    cout << "--- SE PORNESTE TESTAREA AUTOMATA ---" << endl;
    
    Sala testSala(99, 3, 4);
    
    assert(testSala.esteLiber(0, 0) == true);
    cout << "[OK] Test 1: Locul este liber initial." << endl;
    
    testSala.ocupaLoc(0, 0);
    assert(testSala.esteLiber(0, 0) == false);
    cout << "[OK] Test 2: Locul s-a ocupat cu succes." << endl;
    
    try {
        testSala.ocupaLoc(5, 5); // indexul 5,5 nu există într-o sală de 3x4
        cout << "[FAIL] Test 3: Nu s-a aruncat exceptie pentru index invalid!" << endl;
    } catch (const out_of_range& e) {
        cout << "[OK] Test 3: Exceptia out_of_range a fost prinsa corect." << endl;
    }
    
    cout << "--- TOATE TESTELE AUTOMATE AU TRECUT CU SUCCES! ---" << endl;
}


int main() {
    ruleazaTesteAutomate();
    return 0;
}