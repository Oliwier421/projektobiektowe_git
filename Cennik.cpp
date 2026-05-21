#include "Cennik.h"

void Cennik::setCena(TypKarnetu typ, double cena) {
    if (cena<=0) return;
    switch (typ) {
        case Czasowy3h: cena3h=cena; break;
        case Dzienny1d: cena1d=cena; break;
        case Dzienny3d: cena3d=cena; break;
        case Tygodniowy: cena1tyg=cena; break;
        case NocnaJazda: cenaNoc=cena; break;
    }
}

double Cennik::getCena(TypKarnetu typ) const {
    switch (typ) {
        case Czasowy3h: return cena3h; break;
        case Dzienny1d: return cena1d; break;
        case Dzienny3d: return cena3d; break;
        case Tygodniowy: return cena1tyg; break;
        case NocnaJazda: return cenaNoc; break;
    }
    return 0;
}
