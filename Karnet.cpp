#include "Karnet.h"

Karnet::Karnet(TypKarnetu T, bool U, int czas_obecny, int data_obecna, const Cennik& cennik) : typ(T), ulga(U) {
    cena = cennik.getCena(typ)*(1-ulga*0.25);
    switch (typ) {
        case Czasowy3h:
            data_poczatku = data_obecna;
            data_konca = data_obecna;
            czas_poczatku = czas_obecny;
            if (czas_obecny+3600*3 < 20*3600) czas_konca = czas_obecny+3600*3;
            else czas_konca = 20*3600;
            break;
       case Dzienny1d:
            data_poczatku = data_obecna;
            data_konca = data_obecna;
            czas_poczatku = 9*3600;
            czas_konca = 20*3600;
            break;
        case Dzienny3d:
            data_poczatku = data_obecna;
            data_konca = data_obecna+2;
            czas_poczatku = 9*3600;
            czas_konca = 20*3600;
            break;
        case Tygodniowy:
            data_poczatku = data_obecna;
            data_konca = data_obecna+6;
            czas_poczatku = 9*3600;
            czas_konca = 20*3600;
            break;
        case NocnaJazda:
            data_poczatku = data_obecna;
            data_konca = data_obecna;
            czas_poczatku = 17*3600;
            czas_konca = 20*3600;
            break;
    }

}

bool Karnet::czyAktywny(int czas_obecny, int data_obecna) const {
if (data_obecna>=data_poczatku && data_obecna<=data_konca && czas_obecny>=czas_poczatku && czas_obecny<=czas_konca)
    return true;
else return false;
}

int Karnet::getDataKonca() const {return data_konca;}
int Karnet::getCzasKonca() const {return czas_konca;}

