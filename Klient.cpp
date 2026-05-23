#include "Klient.h"
#include <iostream>

Klient::Klient(std::string I, std::string N, std::string L, std::string H) :
    Osoba(I, N, L, H) {}

void Klient::kupKarnet(Stacja& s, TypKarnetu T, bool U) {
    if (s.z.getSec()>=20*3600) {
        std::cout << "Stacja zamknieta. Nie mozna kupic karnetu.\n";
        return;
    }
    if (karnet != nullptr) karnet = nullptr;
    karnet = std::make_unique<Karnet>(T, U, s.z.getSec(), s.z.getDays(), s.cennik);
}

void Klient::wejdzNaWyciag(Stacja& s, int id){
    if (karnet == nullptr) std::cout << "Brak karnetu!\n";
    else if (karnet->czyAktywny(s.z.getSec(), s.z.getDays())){
        int ID = znajdzWyciag(s.wyciagi, id);
        if (ID == -1) {std::cout << "Nie znaleziono wyciagu.\n"; return;}
        s.wyciagi[ID] ->poczatekWjazdu(s.z.getSec());
    } else std::cout << "Karnet nie jest aktywny!\n";
}

void Klient::sprawdzDoKiedyWazne(Stacja& s) const{
    if (karnet == nullptr) {
        std::cout << "Brak karnetu.\n";
        return;
    }
    std::cout << s.z.sec2time(karnet->getCzasKonca()) << " " << s.z.days2date(karnet->getDataKonca());
}

void Klient::menu(Stacja& s) {
    int i, on = 1;
    while (on) {
        std::cout << "--- MENU ---\n";
        std::cout << "1. Kup karnet\n";
        std::cout << "2. Wejdz na wyciag\n";
        std::cout << "3. Sprawdz date waznosci karnetu\n";
        std::cout << "4. Sprawdz liste wyciagow\n";
        std::cout << "5. Zmien haslo\n";
        std::cout << "0. Wyloguj\n";
        std::cout << "Wybierz: ";
        std::cin >> i; std::cin.ignore();

        switch (i){
            case 1:{
                TypKarnetu typ = wybierzTyp();

                bool ulga;
                std::cout << "\nCzy bilet ulgowy? (tak - 1/ nie - 0)  ";
                std::cin >> ulga; std::cin.ignore();

                std::cout << "\nCena wybranego biletu: " << s.cennik.getCena(typ)*(1-ulga*0.25) << " zl";

                bool transakcja;
                std::cout << "\nCzy chcesz dokonac zakupu? (tak - 1/ nie - 0)  ";
                std::cin >> transakcja; std::cin.ignore();
                if (transakcja) {
                    kupKarnet(s, typ, ulga);
                    break;
                }
                else break;}
            case 2:{
                int id;
                std::cout << "\nWpisz id wyciagu na ktory chcesz wejsc: ";
                std::cin >> id; std::cin.ignore();
                wejdzNaWyciag(s, id);
                break;}
            case 3:
                std::cout << "Karnet wazny do ";
                sprawdzDoKiedyWazne(s);
                std::cout << std::endl;
                break;
            case 4:
                s.listaWyciagow();
                break;
            case 5:{
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
