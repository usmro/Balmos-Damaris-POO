# Sistem de Rezervări Cinema
  Proiect realizat în C++ pentru gestiunea sălilor, filmelor și rezervărilor într-un cinematograf.
## Cum se compilează

```bash
cd src
g++ rezervari_cinema.cpp film.cpp sala.cpp rezervare.cpp cinematograf.cpp RezervareOnline.cpp -o app.exe
./app.exe
```

## Cerințe bifate

### Obligatorii
- [x] Clasa `Film` — titlu, gen, durata, tip (2D/3D), preț bază
- [x] Clasa `Sala` — matrice de locuri (libere/ocupate)
- [x] Clasa `Rezervare` — leagă Film, Sala și loc
- [x] Clasa `Cinematograf` — agregă săli și filme
- [x] Metode: afișare filme, afișare locuri, realizare rezervare
- [x] Excepții: loc deja ocupat, index invalid

### Facultative
- [ ] Interfață `ICinemaService` cu metode pure virtuale
- [ ] Clasa `RezervareOnline` cu atribut `emailClient`
- [ ] Calcul automat preț bilet (zi + tip film)
- [ ] Teste unitare

## Descrierea claselor

**Film** — stochează informațiile unui film: titlu, gen, durată, tip (2D/3D) și prețul de bază.

**Sala** — reprezintă o sală de cinema cu o matrice de locuri. Fiecare loc poate fi liber (`[ ]`) sau ocupat (`[X]`).

**Rezervare** — leagă un film de un loc dintr-o sală. Aruncă excepție dacă locul e ocupat sau indexul e invalid.

**Cinematograf** — clasa principală care agregă săli și filme, și gestionează rezervările.

## Autor

Balmos Damaris








 

 


