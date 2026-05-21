#pragma once
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

class Zegar {
private:
    int sec;
    int days;         // dni od 01.01.2025

    int h, m, s;
    int D, M, R;

    std::atomic<bool> dziala;
    std::thread timerThread;

    mutable std::mutex mtx;

    void liczCzas();
    bool czyPrzestepny(int rok) const;

public:
    Zegar(int h_, int m_, int s_, int D_, int M_, int R_);

    ~Zegar();

    void start();
    void stop();

    void ustawCzas(int h, int m, int s, int D, int M, int R);

    int time2sec(int h, int m, int s) const;
    int date2days(int dzien, int miesiac, int rok) const;

    std::string sec2time(int sec) const;
    std::string days2date(int days) const;

    std::string getDate() const;
    std::string getTime() const;

    int getSec() const;
    int getDays() const;
};
