#include "Klient.h"
#include <iostream>

Klient::Klient(std::string I, std::string N, std::string L, std::string H) :
    Osoba(I, N, L, H) {}

void Klient::kupKarnet(Stacja& s, TypKarnetu T, bool U) {
    if (s.z.getSec() >= 20 * 3600) {
        std::cout << "Stacja zamknieta. Nie mozna kupic karnetu.\n";
        return;
    }
    if (karnet != nullptr) {
        if (!czyKarnetWygasl(s)) {
            std::cout << "Klient ma juz aktywny lub nieaktywny karnet.\n";
            return;
        }
        karnet.reset();
    }

    karnet = std::make_unique<Karnet>(T, U, s.z.getSec(), s.z.getDays(), s.cennik);
}

void Klient::wejdzNaWyciag(Stacja& s, int id) {
    if (karnet == nullptr) {
        std::cout << "Brak karnetu!\n";
        return;
    }

    if (!karnet->czyAktywowany()) {
        if (!karnet->czyMoznaAktywowac(s.z.getSec())) {
            std::cout << "Nie mozna teraz aktywowac karnetu.\n";
            return;
        }
        karnet->aktywuj(s.z.getSec(), s.z.getDays());
    }

    if (!karnet->czyAktywny(s.z.getSec(), s.z.getDays())) {
        std::cout << "Karnet nie jest aktywny!\n";
        return;
    }

    for (auto& w : s.wyciagi) {
        if (w->czyKlientJedzie(getLogin(), s.z.getSec())) {
            std::cout << "Klient jest juz na wyciagu.\n";
            return;
        }
    }

    int ID = znajdzWyciag(s.wyciagi, id);

    if (ID == -1) {
        std::cout << "Nie znaleziono wyciagu.\n";
        return;
    }

    s.wyciagi[ID]->poczatekWjazdu(s.z.getSec(), getLogin());
}

void Klient::sprawdzDoKiedyWazne(Stacja& s) const {
    std::cout << opisWaznosciKarnetu(s) << std::endl;
}

bool Klient::czyMaKarnet() const {return karnet != nullptr;}

bool Klient::czyKarnetAktywowany() const {
    if (karnet == nullptr)
        return false;
    return karnet->czyAktywowany();
}

bool Klient::czyKarnetAktywny(Stacja& s) const {
    if (karnet == nullptr)
        return false;
    return karnet->czyAktywny(s.z.getSec(), s.z.getDays());
}

bool Klient::czyKarnetWygasl(Stacja& s) const {
    if (karnet == nullptr) return false;
    if (!karnet->czyAktywowany()) return false;
    return karnet->getPozostaleSekundy(s.z.getSec(), s.z.getDays()) <= 0;
}

bool Klient::czyMoznaAktywowacKarnet(Stacja& s) const {
    if (karnet == nullptr) return false;
    return karnet->czyMoznaAktywowac(s.z.getSec());
}

int Klient::getPozostaleSekundyKarnetu(Stacja& s) const {
    if (karnet == nullptr) return 0;
    return karnet->getPozostaleSekundy(s.z.getSec(), s.z.getDays());
}

std::string Klient::opisWaznosciKarnetu(Stacja& s) const {
    if (karnet == nullptr) return "Brak karnetu.";

    if (!karnet->czyAktywowany())
        return "Karnet jest kupiony, ale jeszcze nieaktywny.\n"
               "Aktywuje sie przy pierwszym wejsciu na wyciag.";

    std::string opis = "Karnet wazny do: ";
    opis += s.z.sec2time(karnet->getCzasKonca());
    opis += " ";
    opis += s.z.days2date(karnet->getDataKonca());

    if (karnet->czyAktywny(s.z.getSec(), s.z.getDays()))
        opis += "\nStatus: aktywny.";
    else
        opis += "\nStatus: nieaktywny.";

    return opis;
}

void Klient::menu(Stacja& s){
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

        std::cin >> i;
        std::cin.ignore();

        switch (i) {
        case 1: {
            TypKarnetu typ = wybierzTyp();

            bool ulga;
            std::cout << "\nCzy bilet ulgowy? (tak - 1/ nie - 0)  ";
            std::cin >> ulga;
            std::cin.ignore();

            std::cout << "\nCena wybranego biletu: " << s.cennik.getCena(typ) * (1 - ulga * 0.25) << " zl";

            bool transakcja;
            std::cout << "\nCzy chcesz dokonac zakupu? (tak - 1/ nie - 0)  ";
            std::cin >> transakcja;
            std::cin.ignore();

            if (transakcja) kupKarnet(s, typ, ulga);
            break;}

        case 2: {
            int id;
            std::cout << "\nWpisz id wyciagu na ktory chcesz wejsc: ";
            std::cin >> id;
            std::cin.ignore();

            wejdzNaWyciag(s, id);
            break;}

        case 3:
            sprawdzDoKiedyWazne(s);
            break;

        case 4:
            s.listaWyciagow();
            break;

        case 5: {
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
