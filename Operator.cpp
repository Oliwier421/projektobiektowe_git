#include "Operator.h"
#include <iostream>

Operator::Operator(std::string I, std::string N, std::string L, std::string H) :
    Osoba(I, N, L, H) {}

void Operator::otworzWyciagOP(Stacja& s, int id){
    int ID = znajdzWyciag(s.wyciagi, id);

    if (ID != -1) 
        s.wyciagi[ID]->otworzWyciag();
    else
        std::cout << "Nie znaleziono wyciagu o takim id.\n";
}

void Operator::zamknijWyciagOP(Stacja& s, int id){
    int ID = znajdzWyciag(s.wyciagi, id);
    if (ID != -1) 
        s.wyciagi[ID]->zamknijWyciag(s.z.getSec());
    else 
        std::cout << "Nie znaleziono wyciagu o takim id.\n";
}

void Operator::zatrzymajWyciagOP(Stacja& s, int id, int czas){
    if (czas <= 0) {
        std::cout << "Czas musi byc dodatni!\n";
        return;
    }
    int ID = znajdzWyciag(s.wyciagi, id);
    if (ID != -1) 
        s.wyciagi[ID]->zatrzymajWyciag(s.z.getSec(), czas);
    else 
        std::cout << "Nie znaleziono wyciagu o takim id.\n";
}

void Operator::dodajWyciag(Stacja& s, int id, int czas_wjazdu){
    if (czas_wjazdu <= 0) {
        std::cout << "Czas musi byc dodatni.\n";
        return;
    }

    if (znajdzWyciag(s.wyciagi, id) != -1) {
        std::cout << "Wyciag o takim id juz istnieje.\n";
        return;
    }

    s.wyciagi.push_back(std::make_unique<Wyciag>(czas_wjazdu, id));
}

void Operator::usunWyciag(Stacja& s, int id) {
    int ID = znajdzWyciag(s.wyciagi, id);

    if (ID != -1)
        s.wyciagi.erase(s.wyciagi.begin() + ID);
    else
        std::cout << "Nie znaleziono wyciagu o takim id.\n";
}

void Operator::menu(Stacja& s){
    int i, on = 1;

    while (on) {
        std::cout << "--- MENU ---\n";
        std::cout << "1. Otworz wyciag\n";
        std::cout << "2. Zamknij wyciag\n";
        std::cout << "3. Zatrzymaj wyciag\n";
        std::cout << "4. Dodaj wyciag\n";
        std::cout << "5. Usun wyciag\n";
        std::cout << "6. Sprawdz liste wyciagow\n";
        std::cout << "7. Zmien haslo\n";
        std::cout << "0. Wyloguj\n";
        std::cout << "Wybierz: ";

        std::cin >> i;
        std::cin.ignore();

        switch (i) {
        case 1: {
            int id;
            std::cout << "\nWpisz id wyciagu, ktory chcesz otworzyc: ";
            std::cin >> id;
            std::cin.ignore();

            otworzWyciagOP(s, id);
            break;}

        case 2: {
            int id;
            std::cout << "\nWpisz id wyciagu, ktory chcesz zamknac: ";
            std::cin >> id;
            std::cin.ignore();

            zamknijWyciagOP(s, id);
            break;}

        case 3: {
            int id, t;
            std::cout << "\nWpisz id wyciagu, ktory chcesz zatrzymac: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "\nWpisz na ile czasu chcesz zatrzymac wyciag (w sekundach): ";
            std::cin >> t;
            std::cin.ignore();

            zatrzymajWyciagOP(s, id, t);
            break;}

        case 4: {
            int id, t;
            std::cout << "\nWpisz id wyciagu: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "\nWpisz ile czasu trwa wjazd (w sekundach): ";
            std::cin >> t;
            std::cin.ignore();

            dodajWyciag(s, id, t);
            break;}

        case 5: {
            int id;
            std::cout << "\nWpisz id wyciagu, ktory chcesz usunac: ";
            std::cin >> id;
            std::cin.ignore();

            usunWyciag(s, id);
            break;}

        case 6:
            s.listaWyciagow();
            break;

        case 7: {
            std::string h, nowe;

            std::cout << "\nWpisz haslo: ";
            std::cin >> h;
            std::cin.ignore();

            std::cout << "\nWpisz nowe haslo: ";
            std::cin >> nowe;
            std::cin.ignore();

            zmienHaslo(h, nowe);
            break;}

        case 0:
            on = 0;
            break;
        }
    }

    s.wyloguj();
}
