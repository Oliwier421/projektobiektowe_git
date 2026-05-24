#pragma once
#include "Wyciag.h"
#include "Osoba.h"
#include "Zegar.h"
#include "Cennik.h"
#include <vector>
#include <memory>
class Osoba;

class Stacja {
public:
    int data, czas;
    Zegar z; //trzeba lepiej zainicjalizowac
    std::vector <std::unique_ptr<Wyciag>> wyciagi;
    std::vector <std::unique_ptr<Osoba>> osoby; //klienci
    std::vector <std::unique_ptr<Osoba>> pracownicy;
    Cennik cennik;
    Osoba* aktualnyUzytkownik = nullptr;

    Stacja (int h, int m, int s, int D, int M, int R);

    void zalozKonto();
    Osoba* zaloguj(std::string login, std::string haslo);
    void wyloguj();
    void listaWyciagow() const;
    bool wczytajDateCzas(const std::string& input, int& h, int& m, int& s,int& D, int& M, int& R);
    void sprawdzGodzine() const;
    void ustawGodzineDate(int h, int m, int s, int D, int M, int R) ;
};
