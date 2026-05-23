#pragma once
#include "Osoba.h"
#include "Karnet.h"

class Kasjer : public Osoba {
    public:
        Kasjer(std::string I, std::string N, std::string L, std::string H);
        void sprzedajKarnet(Stacja& s, std::string imie, std::string nazwisko, TypKarnetu typ, bool ulga);
        void ustawCene (Stacja& s, TypKarnetu typ, double cena);
        double sprawdzCene (Stacja& s, TypKarnetu typ) const;
        void menu(Stacja& s) override;
};

