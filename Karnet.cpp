#include "Karnet.h"

Karnet::Karnet(TypKarnetu T, bool U, int czas_obecny, int data_obecna, const Cennik& cennik)
    : ulga(U), aktywowany(false), typ(T) {
    cena = cennik.getCena(typ) * (1 - ulga * 0.25);

    data_poczatku = data_obecna;
    data_konca = data_obecna;
    czas_poczatku = 0;
    czas_konca = 0;
}

void Karnet::aktywuj(int czas_obecny, int data_obecna) {
    if (aktywowany) return;

    aktywowany = true;

    data_poczatku = data_obecna;
    czas_poczatku = czas_obecny;

    switch (typ) {
    case Czasowy3h:
        data_konca = data_obecna;

        if (czas_obecny + 3 * 3600 < 20 * 3600) czas_konca = czas_obecny + 3 * 3600;
        else czas_konca = 20 * 3600;
        break;

    case Dzienny1d:
        data_konca = data_obecna;
        czas_konca = 20 * 3600;
        break;

    case Dzienny3d:
        data_konca = data_obecna + 2;
        czas_konca = 20 * 3600;
        break;

    case Tygodniowy:
        data_konca = data_obecna + 6;
        czas_konca = 20 * 3600;
        break;

    case NocnaJazda:
        data_konca = data_obecna;
        czas_konca = 20 * 3600;
        break;
    }
}

bool Karnet::czyAktywowany() const {return aktywowany;}

bool Karnet::czyMoznaAktywowac(int czas_obecny) const {
    if (czas_obecny >= 20 * 3600) return false;
    if (typ == NocnaJazda && czas_obecny < 17 * 3600) return false;
    return true;
}

bool Karnet::czyAktywny(int czas_obecny, int data_obecna) const {
    if (!aktywowany)
        return false;
    if (data_obecna < data_poczatku || data_obecna > data_konca)
        return false;
    if (data_poczatku == data_konca)
        return czas_obecny >= czas_poczatku && czas_obecny <= czas_konca;
    if (data_obecna == data_poczatku)
        return czas_obecny >= czas_poczatku && czas_obecny <= 20 * 3600;
    if (data_obecna == data_konca) return czas_obecny >= 9 * 3600 && czas_obecny <= czas_konca;

    return czas_obecny >= 9 * 3600 && czas_obecny <= 20 * 3600;
}

bool Karnet::czyWygasl(int czas_obecny, int data_obecna) const {
    if (!aktywowany) return false;
    return getPozostaleSekundy(czas_obecny, data_obecna) <= 0;
}

int Karnet::getDataKonca() const {return data_konca;}
int Karnet::getCzasKonca() const {return czas_konca;}
int Karnet::getPozostaleSekundy(int czas_obecny, int data_obecna) const {
    if (!aktywowany) return 0;
    int pozostalo = (data_konca - data_obecna) * 24 * 3600 + (czas_konca - czas_obecny);
    if (pozostalo < 0) return 0;
    return pozostalo;
}


