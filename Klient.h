#pragma once

#include <memory>
#include <string>

#include "Osoba.h"
#include "Karnet.h"

class Klient : public Osoba {
private:
    std::unique_ptr<Karnet> karnet = nullptr;

public:
    Klient(std::string I, std::string N, std::string L, std::string H);

    void kupKarnet(Stacja& s, TypKarnetu T, bool U) override;
    void wejdzNaWyciag(Stacja& s, int id);
    void sprawdzDoKiedyWazne(Stacja& s) const;

    bool czyMaKarnet() const;
    bool czyKarnetAktywowany() const;
    bool czyKarnetAktywny(Stacja& s) const;
    bool czyMoznaAktywowacKarnet(Stacja& s) const;
    bool czyKarnetWygasl(Stacja& s) const;

    int getPozostaleSekundyKarnetu(Stacja& s) const;
    std::string opisWaznosciKarnetu(Stacja& s) const;

    void menu(Stacja& s) override;
};
