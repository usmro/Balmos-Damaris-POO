#include <iostream>
#include "Film.h"
#include "Sala.h"
#include "Rezervare.h"
#include "Cinematograf.h"
#include "RezervareOnline.h"
using namespace std;

int main()
{
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

   try
   {
      c.realizeazaRezervare(1, f1, 0, 0);
      c.realizeazaRezervare(1, f1, 0, 0); // loc deja ocupat
   }
   catch (runtime_error &e)
   {
      cout << "Eroare: " << e.what() << endl;
   }
   catch (out_of_range &e)
   {
      cout << "Eroare: " << e.what() << endl;
   }
   cout << "\n--- Rezervare Online ---" << endl;
   try
   {
      RezervareOnline ro(f2, s1, 1, 1, "damaris@email.com");
      s1.ocupaLoc(1, 1);
      ro.afisare();
   }
   catch (runtime_error &e)
   {
      cout << "Eroare: " << e.what() << endl;
   }
   cout << "\n--- Calcul Pret ---" << endl;
   cout << "Pret Inception (2D, luni): " << f1.calculeazaPret("luni") << " lei" << endl;
   cout << "Pret Avatar (3D, sambata): " << f2.calculeazaPret("sambata") << " lei" << endl;

   return 0;
}