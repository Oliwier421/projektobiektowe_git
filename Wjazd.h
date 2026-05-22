#pragma once

class Wjazd {
    private:
        int czas_poczatku, czas_konca;
    public:
        Wjazd(int czas_p, int czas_wjazdu);
        void wydluzWjazd(int czas);
        int getCzasPoczatku() const;
        int getCzasKonca() const;
};
