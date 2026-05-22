#pragma once
#include "Osoba.h"

class Admin : public Osoba {
public:
    Admin(std::string I, std::string N, std::string L, std::string H);
    void dodajOperatora(Stacja& s, std::string I, std::string N, std::string L, std::string H);
    void dodajKasjera(Stacja& s, std::string I, std::string N, std::string L, std::string H);
    void sprawdzOsoby(Stacja& s) const;
    void menu(Stacja& s) override;
};
