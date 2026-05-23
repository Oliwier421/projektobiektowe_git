#include "Kasjer.h"
#include "Klient.h"
#include <iostream>

Kasjer::Kasjer(std::string I, std::string N, std::string L, std::string H) :
    Osoba(I, N, L, H) {}

void Kasjer::sprzedajKarnet(Stacja& s, std::string imie, std::string nazwisko, TypKarnetu typ, bool ulga) {
    int id = znajdzOsobe(s.osoby, imie, nazwisko);
    if (id == -1) {
        s.osoby.push_back(std::make_unique<Klient>(imie, nazwisko, imie+'_'+nazwisko, "1234"));
        id = znajdzOsobe(s.osoby, imie, nazwisko);
    }
    s.osoby[id]->kupKarnet(s, typ, ulga);
    std::cout << "Karnet zostal sprzedany.\n";
}

void Kasjer::ustawCene (Stacja& s, TypKarnetu typ, double cena){
    if (cena<=0) {
        std::cout << "Cena musi byc wieksza od 0!\n";
        return;
    }
    s.cennik.setCena(typ, cena);}
double Kasjer::sprawdzCene (Stacja& s, TypKarnetu typ) const {return s.cennik.getCena(typ);}

void Kasjer::menu(Stacja& s) {
    int i, on = 1;
    while (on) {
        std::cout << "--- MENU ---\n";
        std::cout << "1. Sprzedaj karnet\n";
        std::cout << "2. Ustaw cene\n";
        std::cout << "3. Sprawdz cene\n";
        std::cout << "4. Zmien haslo\n";
        std::cout << "0. Wyloguj\n";
        std::cout << "Wybierz: ";
        std::cin >> i; std::cin.ignore();

        switch (i){
            case 1:{
                std::string imie, nazwisko;
                bool ulga;
                std::cout << "\nWpisz imie klienta: ";
                std::cin >> imie; std::cin.ignore();
                std::cout << "\nWpisz nazwisko klienta: ";
                std::cin >> nazwisko; std::cin.ignore();

                TypKarnetu typ = wybierzTyp();

                std::cout << "\nCzy bilet ulgowy? (tak - 1/ nie - 0)  ";
                std::cin >> ulga; std::cin.ignore();

                std::cout << "\nCena wybranego biletu: " << sprawdzCene(s, typ)*(1-ulga*0.25) << " zl\n";

                bool transakcja;
                std::cout << "\nCzy chcesz dokonac zakupu? (tak - 1/ nie - 0)  ";
                std::cin >> transakcja; std::cin.ignore();
                if (transakcja) {
                    sprzedajKarnet(s, imie, nazwisko, typ, ulga);
                    break;
                }
                else break;}
            case 2:{
                TypKarnetu typ = wybierzTyp();
                double cena;
                std::cout << "\nObecna cena: " << sprawdzCene(s, typ) << " zl";
                std::cout << "\nJaka cene chcesz ustawic? (w zl): ";
                std::cin >> cena; std::cin.ignore();

                ustawCene(s, typ, cena);
                break;}
            case 3:{
                TypKarnetu typ = wybierzTyp();
                std::cout << "\nObecna cena: " << sprawdzCene(s, typ) << " zl\n";
                break;
                }
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

