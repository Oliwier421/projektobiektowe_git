#include "Osoba.h"
#include <iostream>

Osoba::Osoba(std::string& I, std::string& N, std::string& L, std::string& H) :
    imie(I), nazwisko(N), login(L), haslo (H) {}

std::string Osoba::getImie() const {return imie;}
std::string Osoba::getNazwisko() const {return nazwisko;}
std::string Osoba::getLogin() const {return login;}
bool Osoba::sprawdzHaslo(std::string h) const {return h==haslo;}

void Osoba::zmienHaslo(std::string stare, std::string nowe) {
    if (stare==haslo) {
        haslo = nowe;
        std::cout << "Haslo zostalo zmienione.\n";
    } else std::cout << "Niepoprawne haslo!\n";
}

void Osoba::menu(Stacja& s) {std::cout << "--- MENU ---\n";}
void Osoba::kupKarnet(Stacja& s, TypKarnetu T, bool U) {std::cout << "Ta osoba nie moze kupic karnetu.\n";}


int Osoba::znajdzWyciag(std::vector <std::unique_ptr<Wyciag>>& W, int id){
    for (int i = 0; i < W.size(); i++)
        if (W[i]->getId() == id)
            return i;
    return -1;
}

int Osoba::znajdzOsobe(std::vector <std::unique_ptr<Osoba>>& o, std::string imie, std::string nazwisko){
    for (int i = 0; i < o.size(); i++)
        if (o[i]->getImie() == imie && o[i]->getNazwisko() == nazwisko)
            return i;
    return -1;
}


TypKarnetu Osoba::wybierzTyp() {
    int n;
    std::cout << "\nWybierz typ karnetu\n";
    std::cout << "1. 3h\n";
    std::cout << "2. 1 dzien\n";
    std::cout << "3. 3 dni\n";
    std::cout << "4. 1 tydzien\n";
    std::cout << "5. Nocna jazda\n";
    std::cout << "Wybierz: ";
    std::cin >> n; std::cin.ignore();

    switch (n) {
        case 1: return Czasowy3h; break;
        case 2: return Dzienny1d; break;
        case 3: return Dzienny3d; break;
        case 4: return Tygodniowy; break;
        case 5: return NocnaJazda; break;
        default:
            std::cout << "Nieprawidlowy typ karnetu. Ustawiono domyslnie 3h.";
            return Czasowy3h;
            break;
        }
}
