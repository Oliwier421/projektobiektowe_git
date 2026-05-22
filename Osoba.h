#pragma once
#include <string>
#include "Stacja.h"
#include "TypKarnetu.h"
class Stacja;

class Osoba {
    private:
        std::string imie, nazwisko, login, haslo;
    public:
        Osoba(std::string& I, std::string& N, std::string& L, std::string& H);
        std::string getImie() const;
        std::string getNazwisko() const;
        std::string getLogin() const;
        bool sprawdzHaslo(std::string h) const;
        void zmienHaslo(std::string stare, std::string nowe);
        virtual void menu(Stacja& s) = 0;
        virtual void kupKarnet(Stacja& s, TypKarnetu T, bool U);

        int znajdzWyciag(std::vector <std::unique_ptr<Wyciag>>& W, int id);
        int znajdzOsobe(std::vector <std::unique_ptr<Osoba>>& o, std::string imie, std::string nazwisko);
        TypKarnetu wybierzTyp();
};

