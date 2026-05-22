#include "Admin.h"
#include "Operator.h"
#include "Kasjer.h"
#include <iostream>

Admin::Admin(std::string I, std::string N, std::string L, std::string H) :
    Osoba(I, N, L, H) {}

void Admin::dodajOperatora(Stacja& s, std::string I, std::string N, std::string L, std::string H) {
    s.pracownicy.push_back(std::make_unique<Operator>(I, N, L, H));}

void Admin::dodajKasjera(Stacja& s, std::string I, std::string N, std::string L, std::string H) {
    s.pracownicy.push_back(std::make_unique<Kasjer>(I, N, L, H));}

void Admin::sprawdzOsoby(Stacja& s) const{
    std::cout << "\n --- PRACOWNICY ---\n";
    for (auto& p : s.pracownicy) {std::cout << p->getImie() << " " << p->getNazwisko() << std::endl;}
    std::cout << "\n --- KLIENCI ---\n";
    for (auto& o : s.osoby) {std::cout << o->getImie() << " " << o->getNazwisko() << std::endl;}
}

void Admin::menu(Stacja& s) {
    int i, on = 1;
    while (on) {
        std::cout << "--- MENU ---\n";
        std::cout << "1. Dodaj operatora\n";
        std::cout << "2. Dodaj kasjera\n";
        std::cout << "3. Sprawdz liste osob\n";
        std::cout << "4. Zmien haslo\n";
        std::cout << "0. Wyloguj\n";
        std::cout << "Wybierz: ";
        std::cin >> i; std::cin.ignore();

        switch (i){
            case 1:{
            std::string imie, nazwisko;
            std::cout << "\nPodaj imie: ";
            std::cin >> imie; std::cin.ignore();
            std::cout << "\nPodaj nazwisko: ";
            std::cin >> nazwisko; std::cin.ignore();
            std::string login = imie + '_' + nazwisko + 'O';
            dodajOperatora(s, imie, nazwisko, login, "1234");
            break;
            }
            case 2:{
            std::string imie, nazwisko;
            std::cout << "\nPodaj imie: ";
            std::cin >> imie; std::cin.ignore();
            std::cout << "\nPodaj nazwisko: ";
            std::cin >> nazwisko; std::cin.ignore();
            std::string login = imie + '_' + nazwisko + 'K';
            dodajKasjera(s, imie, nazwisko, login, "1234");
            break;
            }
            case 3:
                sprawdzOsoby(s);
                break;
            case 4:{
                std::string h, nowe;
                std::cout << "\nWpisz haslo: ";
                std::cin >> h; std::cin.ignore();
                std::cout << "\nWpisz nowe haslo: ";
                std::cin >> nowe; std::cin.ignore();
                zmienHaslo(h, nowe);
                break;}
            case 0: on = 0; break;
        }
    }
    s.wyloguj();
}


