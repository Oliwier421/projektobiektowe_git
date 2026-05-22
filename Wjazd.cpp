#include "Wjazd.h"

Wjazd::Wjazd(int czas_p, int czas_wjazdu) :
    czas_poczatku(czas_p), czas_konca(czas_p+czas_wjazdu) {}

void Wjazd::wydluzWjazd(int czas) {if (czas>0) czas_konca+=czas;}
int Wjazd::getCzasPoczatku() const {return czas_poczatku;}
int Wjazd::getCzasKonca() const {return czas_konca;}
