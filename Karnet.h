#pragma once
//#include "TypKarnetu.h"
#include "Cennik.h"

class Karnet {
    private:
        bool ulga;
        TypKarnetu typ;
        double cena;
        int data_poczatku, data_konca;
        int czas_poczatku, czas_konca;
    public:
        Karnet(TypKarnetu T, bool U, int czas_obecny, int data_obecna, const Cennik& cennik);
        bool czyAktywny(int czas_obecny, int data_obecna) const;
        int getDataKonca() const;
        int getCzasKonca() const;
};
