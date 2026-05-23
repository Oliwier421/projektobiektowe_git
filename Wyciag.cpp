#include "Wyciag.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

static std::string formatujCzas(int sekundy) {
    if (sekundy <= 0) 
        return "00:00:00";

    int h = sekundy / 3600;
    int m = (sekundy % 3600) / 60;
    int s = sekundy % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << h << ":"
        << std::setw(2) << std::setfill('0') << m << ":"
        << std::setw(2) << std::setfill('0') << s;

    return oss.str();
}

Wyciag::Wyciag(int Cw, int ID) 
    : czas_wjazdu(Cw), czyOtwarty(false), czyZatrzymany(false), czasWznowienia(0), id(ID) {}

void Wyciag::aktualizujStan(int czas_obecny) {
    if (czyZatrzymany && czas_obecny >= czasWznowienia) {
        czyZatrzymany = false;
        czyOtwarty = true;
        czasWznowienia = 0;
    }
}

void Wyciag::poczatekWjazdu(int czas_obecny, const std::string& klientLogin) {
    aktualizujStan(czas_obecny);
    koniecWjazdu(czas_obecny);
    
    if (czyOtwarty && !czyZatrzymany) {
        wjazdy.push_back(std::make_unique<Wjazd>(czas_obecny, czas_wjazdu, klientLogin));
    } else if (czyZatrzymany)
        std::cout << "Wyciag zatrzymany. Nie mozna rozpoczac wjazdu.\n";
    else std::cout << "Wyciag zamkniety. Nie mozna rozpoczac wjazdu.\n";
}

void Wyciag::koniecWjazdu(int czas_obecny) {
    wjazdy.erase(
        std::remove_if(
            wjazdy.begin(), wjazdy.end(),
            [czas_obecny](const std::unique_ptr<Wjazd>& w) {
                return w->getCzasKonca() <= czas_obecny;
            }
            ),
        wjazdy.end()
        );
}

void Wyciag::otworzWyciag() {
    if (czyOtwarty && !czyZatrzymany) {
        std::cout << "Wyciag jest juz otwarty.\n";
        return;
    }

    czyOtwarty = true;
    czyZatrzymany = false;
    czasWznowienia = 0;
}

void Wyciag::zamknijWyciag(int czas_obecny) {
    aktualizujStan(czas_obecny);
    koniecWjazdu(czas_obecny);

    if (wjazdy.empty()) {
        czyOtwarty = false;
        czyZatrzymany = false;
        czasWznowienia = 0;
    } else 
        std::cout << "Nie mozna zamknac wyciagu, bo sa na nim ludzie.\n";
}

void Wyciag::zatrzymajWyciag(int czas_obecny, int czas_zatrzymania) {
    if (czas_zatrzymania <= 0) 
        return;

    aktualizujStan(czas_obecny);

    if (!czyOtwarty) {
        std::cout << "Nie mozna zatrzymac zamknietego wyciagu.\n";
        return;
    }

    czyZatrzymany = true;
    czasWznowienia = czas_obecny + czas_zatrzymania;

    for (auto& w : wjazdy)
        w->wydluzWjazd(czas_zatrzymania);
}

int Wyciag::getId() const {return id;}
bool Wyciag::isOtwarty() const {return czyOtwarty;}
bool Wyciag::isZatrzymany(int czas_obecny){
    aktualizujStan(czas_obecny);
    return czyZatrzymany;
}
bool Wyciag::czyMoznaWsiasc(int czas_obecny) {
    aktualizujStan(czas_obecny);
    return czyOtwarty && !czyZatrzymany;
}
std::string Wyciag::getStatus(int czas_obecny) {
    aktualizujStan(czas_obecny);
    if (czyZatrzymany)  return "zatrzymany";
    if (czyOtwarty) return "otwarty";
    return "zamkniety";
}
int Wyciag::getCzasWjazdu() const {return czas_wjazdu;}
int Wyciag::getLiczbaAktywnychWjazdow(int czas_obecny){
    aktualizujStan(czas_obecny);
    koniecWjazdu(czas_obecny);
    return static_cast<int>(wjazdy.size());
}

bool Wyciag::czyKlientJedzie(const std::string& login, int czas_obecny) {
    aktualizujStan(czas_obecny);
    koniecWjazdu(czas_obecny);

    for (const auto& w : wjazdy) {
        if (w->getKlientLogin() == login) return true;
    }
    return false;
}

std::string Wyciag::getOpisAktywnychWjazdow(int czas_obecny) {
    aktualizujStan(czas_obecny);
    koniecWjazdu(czas_obecny);

    if (wjazdy.empty()) 
        return "brak osob na wyciagu";

    std::string opis;
    for (const auto& w : wjazdy) {
        opis += "   - ";
        opis += w->getKlientLogin();
        opis += " | wjazd zostalo: ";
        opis += formatujCzas(w->getPozostalyCzasWjazdu(czas_obecny));
        opis += "\n";
    }
    return opis;
}
