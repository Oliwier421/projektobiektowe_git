#pragma once
#include "Osoba.h"


class Operator : public Osoba {
    public:
        Operator(std::string I, std::string N, std::string L, std::string H);
        void otworzWyciagOP(Stacja& s, int id);
        void zamknijWyciagOP(Stacja& s, int idy);
        void zatrzymajWyciagOP(Stacja& s, int id, int czas); //zatrzymanie wyci¹gu na okreœlony czas, po którym uruchomi siê ponownie
        void dodajWyciag(Stacja& s, int id, int czas_wjazdu);
        void usunWyciag(Stacja& s, int id);
        void menu(Stacja& s) override;
};
