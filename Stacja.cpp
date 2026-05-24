#include "Stacja.h"
#include <iostream>
#include <sstream>
#include "Klient.h"

Stacja::Stacja (int h, int m, int s, int D, int M, int R) : z(h, m, s, D, M, R) {
    z.start();
}

void Stacja::zalozKonto() {
    std::string imie, nazwisko, haslo;
    std::cout << "\nPodaj imie: ";
    std::cin >> imie; std::cin.ignore();
    std::cout << "\nPodaj nazwisko: ";
    std::cin >> nazwisko; std::cin.ignore();
    std::cout << "\nPodaj haslo: ";
    std::cin >> haslo; std::cin.ignore();
    std::string login = imie + '_' + nazwisko;
    osoby.push_back(std::make_unique<Klient>(imie, nazwisko, login, haslo));
}

Osoba* Stacja::zaloguj(std::string login, std::string haslo) {
    for (int i = 0; i < osoby.size(); i++) {
        if (osoby[i]->getLogin() == login && osoby[i]->sprawdzHaslo(haslo)) {
            std::cout << "Zalogowano pomyslnie.\n";
            aktualnyUzytkownik = osoby[i].get();
            return aktualnyUzytkownik;
        }
    }
    for (int i = 0; i < pracownicy.size(); i++) {
        if (pracownicy[i]->getLogin() == login && pracownicy[i]->sprawdzHaslo(haslo)) {
            std::cout << "Zalogowano pomyslnie.\n";
            aktualnyUzytkownik = pracownicy[i].get();
            return aktualnyUzytkownik;
        }
    }
    std::cout << "Niepoprawny login lub haslo.\n";
    return nullptr;
}

void Stacja::wyloguj() {
 if (aktualnyUzytkownik != nullptr) {
    std::cout << "Wylogowano uzytkownika: " << aktualnyUzytkownik->getLogin() << "\n";
    aktualnyUzytkownik = nullptr;
    }
}

void Stacja::listaWyciagow() const{
    std::cout << "\n--- LISTA WYCIAGOW ---\n";
    for(auto& w : wyciagi) {
        std::cout << "ID: " << w->getId() << " | " << (w->isOtwarty() ? "otwarty\n" : "zamkniety\n");
    }
}

bool Stacja::wczytajDateCzas(const std::string& input, int& h, int& m, int& s,int& D, int& M, int& R) {
    std::stringstream ss(input);
    char c1, c2, c3, bar;
    // format: h:m:s | D.M.R
    if (!(ss >> h >> c1 >> m >> c2 >> s))
        return false;
    if (c1 != ':' || c2 != ':')
        return false;
    if (!(ss >> bar >> D >> c1 >> M >> c2 >> R))
        return false;
    if (bar != '|')
        return false;
    if (c1 != '.' || c2 != '.')
        return false;

    if (h < 0 || h > 23) return false;
    if (m < 0 || m > 59) return false;
    if (s < 0 || s > 59) return false;
    if (M < 1 || M > 12) return false;
    if (D < 1 || D > 31) return false;
    if (R < 2020 || R > 2100) return false;

    return true;
}

void Stacja::sprawdzGodzine() const{
    std::cout << z.getTime() << " | " << z.getDate() << std::endl;
}

void Stacja::ustawGodzineDate(int h, int m, int s, int D, int M, int R) {
    z.ustawCzas(h, m, s, D, M, R);
}
