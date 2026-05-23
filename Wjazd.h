#pragma once
#include <string>

class Wjazd {
private:
    int czas_poczatku;
    int czas_konca;
    std::string klientLogin;

public:
    Wjazd(int czas_p, int czas_wjazdu, const std::string& login);
    void wydluzWjazd(int czas);

    int getCzasPoczatku() const;
    int getCzasKonca() const;
    std::string getKlientLogin() const;
    int getPozostalyCzasWjazdu(int czas_obecny) const;
};
