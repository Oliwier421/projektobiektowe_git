#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Wjazd.h"

class Wyciag {
private:
    int czas_wjazdu;
    std::vector<std::unique_ptr<Wjazd>> wjazdy;
    bool czyOtwarty;
    bool czyZatrzymany;
    int czasWznowienia;
    int id;

    void aktualizujStan(int czas_obecny);
public:
    Wyciag(int Cw, int ID);

    void poczatekWjazdu(int czas_obecny, const std::string& klientLogin);
    void koniecWjazdu(int czas_obecny);

    void otworzWyciag();
    void zamknijWyciag(int czas_obecny);
    void zatrzymajWyciag(int czas_obecny, int czas_zatrzymania);

    int getId() const;
    bool isOtwarty() const;

    bool isZatrzymany(int czas_obecny);
    bool czyMoznaWsiasc(int czas_obecny);
    std::string getStatus(int czas_obecny);

    int getCzasWjazdu() const;
    int getLiczbaAktywnychWjazdow(int czas_obecny);

    bool czyKlientJedzie(const std::string& login, int czas_obecny);

    std::string getOpisAktywnychWjazdow(int czas_obecny);
};
