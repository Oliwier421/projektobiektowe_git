#include <iostream>
#include "Stacja.h"
#include "Admin.h"
using namespace std;

int main() {
    Stacja s(9, 0, 0, 6, 12, 2025);
    s.pracownicy.push_back(std::make_unique<Admin>("Jan", "Kowalski", "administrator", "haslo"));
    int i;
    while (1) {
        std::cout << "--- MENU GLOWNE ---\n";
        std::cout << "1. Zaloguj\n";
        std::cout << "2. Sprawdz godzine\n";
        std::cout << "3. Ustaw date i czas\n";
        std::cout << "4. Zobacz liste wyciagow\n";
        std::cout << "Wybierz: ";
        std::cin >> i; std::cin.ignore();

        switch (i){
            case 1:{
                std::string login, haslo;
                std::cout << "\n Podaj login:  ";
                std::cin >> login;
                std::cout << "\n Podaj haslo:  ";
                std::cin >> haslo;

                Osoba* user = s.zaloguj(login, haslo);
                if (user != nullptr) user->menu(s);
                break;                }
            case 2:
                s.sprawdzGodzine();
                break;
            case 3:{
                int h, m, sec, D, M, R;
                string input;
                cout << "Wpisz godzine i date w formacie h:m:s | D.M.R: ";
                std::getline(std::cin, input);
                if (s.wczytajDateCzas(input, h, m, sec, D, M, R))
                    s.ustawGodzineDate(h, m, sec, D, M, R);
                else cout << "Bledny format.\n";
                break;}
            case 4:
                s.listaWyciagow();
                break;
        }
    }

    return 0;
}
