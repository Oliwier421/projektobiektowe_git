# Stacja narciarska

Projekt aplikacji desktopowej napisanej w języku C++ z wykorzystaniem biblioteki Qt.  
Program symuluje działanie stacji narciarskiej i umożliwia obsługę różnych typów użytkowników, takich jak administrator, kasjer, operator wyciągu oraz klient.

Aplikacja posiada graficzny interfejs użytkownika (GUI) wykonany w Qt Designer i pozwala między innymi na:
- logowanie użytkowników,
- zarządzanie wyciągami,
- sprzedaż i kontrolę karnetów,
- obsługę czasu symulacji,
- monitorowanie działania stacji.

## Wymagania

Do uruchomienia projektu potrzebne są:

- Qt Creator,
- Qt 6.x,
- CMake,
- kompilator zgodny z Qt (np. MinGW 64-bit),
- system Windows.

## Struktura projektu

Projekt składa się z kilku głównych modułów odpowiedzialnych za logikę działania systemu:

CMakeLists.txt
main.cpp
mainwindow.cpp
mainwindow.h
mainwindow.ui

Admin.cpp / Admin.h
Kasjer.cpp / Kasjer.h
Operator.cpp / Operator.h
Klient.cpp / Klient.h
Osoba.cpp / Osoba.h

Stacja.cpp / Stacja.h
Wyciag.cpp / Wyciag.h
Wjazd.cpp / Wjazd.h

Karnet.cpp / Karnet.h
TypKarnetu.h
Cennik.cpp / Cennik.h

Zegar.cpp / Zegar.h
