#include "Wjazd.h"

Wjazd::Wjazd(int czas_p, int czas_wjazdu, const std::string& login)
    : czas_poczatku(czas_p), czas_konca(czas_p + czas_wjazdu), klientLogin(login) {}

void Wjazd::wydluzWjazd(int czas) {if (czas > 0) czas_konca += czas;}

int Wjazd::getCzasPoczatku() const {return czas_poczatku;}
int Wjazd::getCzasKonca() const {return czas_konca;}
std::string Wjazd::getKlientLogin() const {return klientLogin;}
int Wjazd::getPozostalyCzasWjazdu(int czas_obecny) const {
    int pozostalo = czas_konca - czas_obecny;
    if (pozostalo < 0) {return 0;}
    return pozostalo;
}
