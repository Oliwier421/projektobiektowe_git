#pragma once

#include "Cennik.h"

class Karnet {
private:
    bool ulga;
    bool aktywowany = false;

    TypKarnetu typ;
    double cena;

    int data_poczatku = 0;
    int data_konca = 0;
    int czas_poczatku = 0;
    int czas_konca = 0;

public:
    Karnet(TypKarnetu T, bool U, int czas_obecny, int data_obecna, const Cennik& cennik);

    void aktywuj(int czas_obecny, int data_obecna);

    bool czyAktywowany() const;
    bool czyMoznaAktywowac(int czas_obecny) const;
    bool czyAktywny(int czas_obecny, int data_obecna) const;
    bool czyWygasl(int czas_obecny, int data_obecna) const;

    int getDataKonca() const;
    int getCzasKonca() const;
    int getPozostaleSekundy(int czas_obecny, int data_obecna) const;
};
