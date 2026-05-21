#pragma once
#include "TypKarnetu.h"

class Cennik {
    private:
        double cena3h{80}, cena1d{120}, cena3d{300}, cena1tyg{700}, cenaNoc{65};
    public:
        void setCena(TypKarnetu typ, double cena);
        double getCena(TypKarnetu typ) const;
};
