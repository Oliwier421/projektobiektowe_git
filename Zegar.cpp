#include "Zegar.h"
#include <iostream>
#include <iomanip>
#include <chrono>

Zegar::Zegar(int h_, int m_, int s_, int D_, int M_, int R_)
    : dziala(false), h(h_), m(m_), s(s_), D(D_), M(M_), R(R_)
{
    sec = time2sec(h, m, s);
    days = date2days(D, M, R);
}

Zegar::~Zegar() {
    stop();
}

void Zegar::liczCzas() {
    while (dziala) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> lock(mtx);

        sec++;
        s++;

        if (s >= 60) {s = 0; m++;}
        if (m >= 60) {m = 0; h++;}
        if (h >= 24) {
            h = 0; sec = 0;
            days++; D++;
            bool przestepny = czyPrzestepny(R);
            switch (M) {
                case 1: case 3: case 5: case 7: case 8: case 10:
                    if (D > 31) {D = 1; M++;} break;
                case 4: case 6: case 9: case 11:
                    if (D > 30) {D = 1; M++;} break;
                case 2:
                    if ((przestepny && D > 29) || (!przestepny && D > 28)) {D = 1; M++;}
                    break;
                case 12: if (D > 31) {D = 1; M = 1; R++;}break;
            }
        }
    }
}

void Zegar::start() {
    if (dziala) return;
    dziala = true;
    timerThread = std::thread(&Zegar::liczCzas, this);
}

void Zegar::stop() {
    dziala = false;
    if (timerThread.joinable()) timerThread.join();
}


void Zegar::ustawCzas(int h_, int m_, int s_, int D_, int M_, int R_) {
    std::lock_guard<std::mutex> lock(mtx);
    h = h_; m = m_; s = s_; D = D_; M = M_; R = R_;

    sec = time2sec(h, m, s);
    days = date2days(D, M, R);
}


bool Zegar::czyPrzestepny(int rok) const {return (rok % 4 == 0);}

int Zegar::time2sec(int h, int m, int s) const {return s + 60 * m + 3600 * h;}

int Zegar::date2days(int dzien, int miesiac, int rok) const {
    int dniWMiesiacach[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (czyPrzestepny(rok)) dniWMiesiacach[1] = 29;
    int startRok = 2025;
    int licznik = 0;

    for (int r = startRok; r < rok; r++) {licznik += czyPrzestepny(r) ? 366 : 365;}
    for (int m = 0; m < miesiac - 1; m++) {licznik += dniWMiesiacach[m];}
    licznik += dzien;

    return licznik;
}

std::string Zegar::sec2time(int sec) const {
   int h1 = sec/3600, m1 = (sec%3600)/60, s1 = (sec%3600)%60;
   return
        (h1<10 ? "0" + std::to_string(h1) : std::to_string(h1)) + ":" +
        (m1<10 ? "0" + std::to_string(m1) : std::to_string(m1)) + ":" +
        (s1<10 ? "0" + std::to_string(s1) : std::to_string(s1));
}

std::string Zegar::days2date(int dni) const {
    int dniWMiesiacach[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    int Rok = 2025;
    // odejmowanie pe³nych lat
    while (true) {
        int dniWRoku = czyPrzestepny(Rok) ? 366 : 365;
        if (dni > dniWRoku) {
            dni -= dniWRoku;
            Rok++;
        } else break;
    }

    // poprawka lutego
    if (czyPrzestepny(Rok))
        dniWMiesiacach[1] = 29;

    int Mies = 1;
    // odejmowanie pe³nych miesiêcy
    while (dni > dniWMiesiacach[Mies - 1]) {
        dni -= dniWMiesiacach[Mies - 1];
        Mies++;
    }

    int Dn = dni;

    return (Dn<10 ? "0" + std::to_string(Dn) : std::to_string(Dn)) + "." +
    (Mies<10 ? "0" + std::to_string(Mies) : std::to_string(Mies)) + "." + std::to_string(Rok);
}

std::string Zegar::getDate() const {
    std::lock_guard<std::mutex> lock(mtx);
    return (D<10 ? "0" + std::to_string(D) : std::to_string(D)) + "." +
    (M<10 ? "0" + std::to_string(M) : std::to_string(M)) + "." + std::to_string(R);
}

std::string Zegar::getTime() const {
    std::lock_guard<std::mutex> lock(mtx);
    return
        (h<10 ? "0" + std::to_string(h) : std::to_string(h)) + ":" +
        (m<10 ? "0" + std::to_string(m) : std::to_string(m)) + ":" +
        (s<10 ? "0" + std::to_string(s) : std::to_string(s));
}

int Zegar::getSec() const {
    std::lock_guard<std::mutex> lock(mtx);
    return sec;
}

int Zegar::getDays() const {
    std::lock_guard<std::mutex> lock(mtx);
    return days;
}
