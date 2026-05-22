#include "Wyciag.h"
#include <iostream>
#include <algorithm>

Wyciag::Wyciag(int Cw, int ID) :
    czas_wjazdu(Cw), czyOtwarty(false), id(ID) {}


void Wyciag::poczatekWjazdu(int czas_obecny) {
    if (czyOtwarty) wjazdy.push_back(std::make_unique<Wjazd>(czas_obecny, czas_wjazdu));
    else std::cout << "Wyciag zamkniety. Nie mozna rozpoczac wjazdu.\n";
}

void Wyciag::koniecWjazdu(int czas_obecny) {
    wjazdy.erase(
        std::remove_if(wjazdy.begin(), wjazdy.end(),
            [czas_obecny](const std::unique_ptr<Wjazd>& w){
                return w->getCzasKonca()<= czas_obecny;
                        }),
                wjazdy.end());
}

void Wyciag::otworzWyciag() {
    if (czyOtwarty) {
        std::cout << "Wyciag jest juz otwarty.\n";
        return;
    }
    czyOtwarty=true;
}

void Wyciag::zamknijWyciag(int czas_obecny) {
    koniecWjazdu(czas_obecny);
    if (wjazdy.empty()) czyOtwarty=0;
    else std::cout << "Ktos jeszcze wjezdza wyciagiem. Nie mozna zamknac.";
}

void Wyciag::zatrzymajWyciag(int czas) {
    if (czas<=0) return;
    for (auto& w : wjazdy) {w->wydluzWjazd(czas);}
}

int Wyciag::getId() const {return id;}
bool Wyciag::isOtwarty() const {return czyOtwarty;}
