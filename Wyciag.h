#pragma once
#include <vector>
#include <memory>
#include "Wjazd.h"

class Wyciag {
    private:
        int czas_wjazdu;
        std::vector <std::unique_ptr<Wjazd>> wjazdy;
        bool czyOtwarty;
        int id;
    public:
        Wyciag(int Cw, int ID);
        void poczatekWjazdu(int czas_obecny);
        void koniecWjazdu(int czas_obecny);

        void otworzWyciag();
        void zamknijWyciag(int czas_obecny);
        void zatrzymajWyciag(int czas);

        int getId() const;
        bool isOtwarty() const;
};
