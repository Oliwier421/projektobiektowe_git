#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Admin.h"
#include "Kasjer.h"
#include "Operator.h"
#include "Klient.h"

#include <memory>

#include <QApplication>
#include <QPushButton>
#include <QComboBox>
#include <QInputDialog>
#include <QMessageBox>
#include <QLineEdit>

static TypKarnetu wybierzTypKarnetu(QWidget* parent, bool* ok)
{
    QStringList typy;
    typy << "3h"
         << "1 dzien"
         << "3 dni"
         << "1 tydzien"
         << "Nocna jazda";

    QString wybor = QInputDialog::getItem(
        parent,
        "Wybierz typ karnetu",
        "Typ karnetu:",
        typy,
        0,
        false,
        ok
    );

    if (!(*ok)) {
        return Czasowy3h;
    }

    if (wybor == "3h") return Czasowy3h;
    if (wybor == "1 dzien") return Dzienny1d;
    if (wybor == "3 dni") return Dzienny3d;
    if (wybor == "1 tydzien") return Tygodniowy;
    if (wybor == "Nocna jazda") return NocnaJazda;

    return Czasowy3h;
}

static QString formatujSekundy(int sekundy)
{
    if (sekundy <= 0) {
        return "00:00:00";
    }

    int dni = sekundy / (24 * 3600);
    sekundy %= 24 * 3600;

    int h = sekundy / 3600;
    int m = (sekundy % 3600) / 60;
    int s = sekundy % 60;

    QString czas = QString("%1:%2:%3")
        .arg(h, 2, 10, QChar('0'))
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));

    if (dni > 0) {
        czas = QString::number(dni) + " dni " + czas;
    }

    return czas;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      stacja(9, 0, 0, 6, 12, 2025)
{
    ui->setupUi(this);

    qApp->setStyleSheet(
        "QMainWindow {"
        "   background-color: #eef4fb;"
        "}"

        "QWidget {"
        "   color: #111827;"
        "   font-family: Segoe UI;"
        "   font-size: 10pt;"
        "}"

        "QLabel {"
        "   color: #111827;"
        "   background: transparent;"
        "}"

        "QPushButton {"
        "   background-color: #e8f1ff;"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 6px;"
        "   padding: 7px 10px;"
        "}"

        "QPushButton:hover {"
        "   background-color: #d9eaff;"
        "}"

        "QPushButton:pressed {"
        "   background-color: #c5dcf7;"
        "}"

        "QLineEdit {"
        "   background-color: white;"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 4px;"
        "   padding: 4px;"
        "}"

        "QTextEdit {"
        "   background-color: white;"
        "   color: #111827;"
        "   border: 1px solid #b8c7d9;"
        "   border-radius: 6px;"
        "   padding: 8px;"
        "}"

        "QGroupBox {"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 8px;"
        "   margin-top: 10px;"
        "   background-color: #f8fbff;"
        "}"

        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 12px;"
        "   padding: 0px 5px;"
        "   color: #111827;"
        "   background-color: #eef4fb;"
        "}"

        "QDialog {"
        "   background-color: #eef4fb;"
        "   color: #111827;"
        "}"

        "QInputDialog {"
        "   background-color: #eef4fb;"
        "   color: #111827;"
        "}"

        "QMessageBox {"
        "   background-color: #eef4fb;"
        "   color: #111827;"
        "}"

        "QInputDialog QLabel, QMessageBox QLabel {"
        "   color: #111827;"
        "   background: transparent;"
        "   font-size: 10pt;"
        "}"

        "QInputDialog QLineEdit {"
        "   background-color: #ffffff;"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 6px;"
        "   padding: 6px;"
        "   min-height: 24px;"
        "}"

        "QInputDialog QPushButton, QMessageBox QPushButton {"
        "   background-color: #e8f1ff;"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 6px;"
        "   padding: 7px 18px;"
        "   min-width: 70px;"
        "}"

        "QInputDialog QPushButton:hover, QMessageBox QPushButton:hover {"
        "   background-color: #d9eaff;"
        "}"

        "QInputDialog QPushButton:pressed, QMessageBox QPushButton:pressed {"
        "   background-color: #c5dcf7;"
        "}"

        "QInputDialog QComboBox {"
        "   background-color: white;"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 6px;"
        "   padding: 5px;"
        "}"

        "QInputDialog QSpinBox, QInputDialog QDoubleSpinBox {"
        "   background-color: white;"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 6px;"
        "   padding: 5px;"
        "}"
    );

    ui->topFrame->setStyleSheet(
        "QFrame#topFrame {"
        "   background-color: #dbeafe;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 8px;"
        "}"

        "QLabel {"
        "   color: #111827;"
        "   font-weight: bold;"
        "   background: transparent;"
        "}"

        "QComboBox {"
        "   background-color: #ffffff;"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 6px;"
        "   padding: 4px 26px 4px 8px;"
        "   min-width: 58px;"
        "}"

        "QComboBox:hover {"
        "   border: 1px solid #5b8fca;"
        "}"

        "QComboBox::drop-down {"
        "   subcontrol-origin: padding;"
        "   subcontrol-position: top right;"
        "   width: 22px;"
        "   border-left: 1px solid #c7d7ea;"
        "   border-top-right-radius: 6px;"
        "   border-bottom-right-radius: 6px;"
        "   background-color: #eef4fb;"
        "}"

        "QComboBox QAbstractItemView {"
        "   background-color: #ffffff;"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   selection-background-color: #dbeafe;"
        "   selection-color: #111827;"
        "   padding: 4px;"
        "   outline: 0px;"
        "}"
        );

    ui->statusLabel->setStyleSheet(
        "QLabel {"
        "   background-color: #ffffff;"
        "   color: #111827;"
        "   border: 1px solid #9bb7d4;"
        "   border-radius: 6px;"
        "   padding: 6px 10px;"
        "}"
        );

    ui->pagesWidget->setCurrentIndex(0);
    ui->statusLabel->setText("Status: gotowe");

    connect(ui->loginButton, &QPushButton::clicked,
            this, &MainWindow::onLoginClicked);

    connect(ui->adminLogoutButton, &QPushButton::clicked,
            this, &MainWindow::onLogoutClicked);

    connect(ui->kasjerLogoutButton, &QPushButton::clicked,
            this, &MainWindow::onLogoutClicked);

    connect(ui->operatorLogoutButton, &QPushButton::clicked,
            this, &MainWindow::onLogoutClicked);

    connect(ui->klientLogoutButton, &QPushButton::clicked,
            this, &MainWindow::onLogoutClicked);

    connect(ui->speedComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSpeedChanged);

    connect(ui->adminAddOperatorButton, &QPushButton::clicked,
            this, &MainWindow::onAddOperatorClicked);

    connect(ui->adminAddKasjerButton, &QPushButton::clicked,
            this, &MainWindow::onAddKasjerClicked);

    connect(ui->adminChangePasswordButton, &QPushButton::clicked,
            this, &MainWindow::onChangePasswordClicked);

    connect(ui->kasjerSellTicketButton, &QPushButton::clicked,
            this, &MainWindow::onKasjerSellTicketClicked);

    connect(ui->kasjerSetPriceButton, &QPushButton::clicked,
            this, &MainWindow::onKasjerSetPriceClicked);

    connect(ui->kasjerCheckPriceButton, &QPushButton::clicked,
            this, &MainWindow::onKasjerCheckPriceClicked);

    connect(ui->kasjerChangePasswordButton, &QPushButton::clicked,
            this, &MainWindow::onChangePasswordClicked);

    connect(ui->operatorOpenLiftButton, &QPushButton::clicked,
            this, &MainWindow::onOperatorOpenLiftClicked);

    connect(ui->operatorCloseLiftButton, &QPushButton::clicked,
            this, &MainWindow::onOperatorCloseLiftClicked);

    connect(ui->operatorStopLiftButton, &QPushButton::clicked,
            this, &MainWindow::onOperatorStopLiftClicked);

    connect(ui->operatorAddLiftButton, &QPushButton::clicked,
            this, &MainWindow::onOperatorAddLiftClicked);

    connect(ui->operatorRemoveLiftButton, &QPushButton::clicked,
            this, &MainWindow::onOperatorRemoveLiftClicked);

    connect(ui->operatorChangePasswordButton, &QPushButton::clicked,
            this, &MainWindow::onChangePasswordClicked);

    connect(ui->klientBuyTicketButton, &QPushButton::clicked,
            this, &MainWindow::onKlientBuyTicketClicked);

    connect(ui->klientEnterLiftButton, &QPushButton::clicked,
            this, &MainWindow::onKlientEnterLiftClicked);

    connect(ui->klientCheckTicketButton, &QPushButton::clicked,
            this, &MainWindow::onKlientCheckTicketClicked);

    connect(ui->klientChangePasswordButton, &QPushButton::clicked,
            this, &MainWindow::onChangePasswordClicked);

    connect(ui->setDateTimeButton, &QPushButton::clicked,
            this, &MainWindow::onSetDateTimeClicked);

    stacja.pracownicy.push_back(
        std::make_unique<Admin>("Jan", "Kowalski", "administrator", "haslo")
        );

    ui->wyciagiTextEdit->setReadOnly(true);
    ui->osobyTextEdit->setReadOnly(true);

    ui->speedComboBox->clear();
    ui->speedComboBox->addItem("x1");
    ui->speedComboBox->addItem("x2");
    ui->speedComboBox->addItem("x5");
    ui->speedComboBox->addItem("x10");
    ui->speedComboBox->addItem("x30");
    ui->speedComboBox->addItem("x60");
    ui->speedComboBox->setCurrentIndex(0);

    refreshTimer = new QTimer(this);

    connect(refreshTimer, &QTimer::timeout, this, [this]() {
        odswiezCzas();
        odswiezWyciagi();
        odswiezOsoby();
    });

    refreshTimer->start(500);

    odswiezCzas();
    odswiezWyciagi();
    odswiezOsoby();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoginClicked()
{
    std::string login = ui->loginEdit->text().toStdString();
    std::string haslo = ui->passwordEdit->text().toStdString();

    aktualnyUzytkownik = stacja.zaloguj(login, haslo);

    if (aktualnyUzytkownik == nullptr) {
        ui->statusLabel->setText("Status: niepoprawny login lub haslo.");

        QMessageBox::warning(
            this,
            "Blad logowania",
            "Niepoprawny login lub haslo."
            );

        return;
    }

    if (dynamic_cast<Admin*>(aktualnyUzytkownik)) {
        ui->pagesWidget->setCurrentIndex(1);
        ui->statusLabel->setText("Status: zalogowano jako administrator.");
    }
    else if (dynamic_cast<Kasjer*>(aktualnyUzytkownik)) {
        ui->pagesWidget->setCurrentIndex(2);
        ui->statusLabel->setText("Status: zalogowano jako kasjer.");
    }
    else if (dynamic_cast<Operator*>(aktualnyUzytkownik)) {
        ui->pagesWidget->setCurrentIndex(3);
        ui->statusLabel->setText("Status: zalogowano jako operator.");
    }
    else if (dynamic_cast<Klient*>(aktualnyUzytkownik)) {
        ui->pagesWidget->setCurrentIndex(4);
        ui->statusLabel->setText("Status: zalogowano jako klient.");
    }

    ui->loginEdit->clear();
    ui->passwordEdit->clear();
}

void MainWindow::onLogoutClicked()
{
    stacja.wyloguj();
    aktualnyUzytkownik = nullptr;

    ui->pagesWidget->setCurrentIndex(0);

    ui->loginEdit->clear();
    ui->passwordEdit->clear();

    ui->statusLabel->setText("Status: wylogowano.");
}

void MainWindow::onSpeedChanged(int index)
{
    int mnoznik = 1;

    switch (index) {
    case 0: mnoznik = 1; break;
    case 1: mnoznik = 2; break;
    case 2: mnoznik = 5; break;
    case 3: mnoznik = 10; break;
    case 4: mnoznik = 30; break;
    case 5: mnoznik = 60; break;
    default: mnoznik = 1; break;
    }

    stacja.z.setMnoznikCzasu(mnoznik);

    ui->statusLabel->setText(
        "Status: ustawiono tempo czasu x" + QString::number(mnoznik)
        );
}

void MainWindow::onAddOperatorClicked()
{
    Admin* admin = dynamic_cast<Admin*>(aktualnyUzytkownik);

    if (admin == nullptr) {
        ui->statusLabel->setText("Status: tylko administrator moze dodac operatora.");
        return;
    }

    bool ok;

    QString imie = QInputDialog::getText(
        this,
        "Dodaj operatora",
        "Podaj imie:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || imie.isEmpty()) {
        ui->statusLabel->setText("Status: anulowano dodawanie operatora.");
        return;
    }

    QString nazwisko = QInputDialog::getText(
        this,
        "Dodaj operatora",
        "Podaj nazwisko:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || nazwisko.isEmpty()) {
        ui->statusLabel->setText("Status: anulowano dodawanie operatora.");
        return;
    }

    std::string I = imie.toStdString();
    std::string N = nazwisko.toStdString();
    std::string L = I + "_" + N + "O";
    std::string H = "1234";

    admin->dodajOperatora(stacja, I, N, L, H);

    odswiezOsoby();

    ui->statusLabel->setText(
        "Status: dodano operatora. Login: " + QString::fromStdString(L) + ", haslo: 1234"
        );
}

void MainWindow::onAddKasjerClicked()
{
    Admin* admin = dynamic_cast<Admin*>(aktualnyUzytkownik);

    if (admin == nullptr) {
        ui->statusLabel->setText("Status: tylko administrator moze dodac kasjera.");
        return;
    }

    bool ok;

    QString imie = QInputDialog::getText(
        this,
        "Dodaj kasjera",
        "Podaj imie:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || imie.isEmpty()) {
        ui->statusLabel->setText("Status: anulowano dodawanie kasjera.");
        return;
    }

    QString nazwisko = QInputDialog::getText(
        this,
        "Dodaj kasjera",
        "Podaj nazwisko:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || nazwisko.isEmpty()) {
        ui->statusLabel->setText("Status: anulowano dodawanie kasjera.");
        return;
    }

    std::string I = imie.toStdString();
    std::string N = nazwisko.toStdString();
    std::string L = I + "_" + N + "K";
    std::string H = "1234";

    admin->dodajKasjera(stacja, I, N, L, H);

    odswiezOsoby();

    ui->statusLabel->setText(
        "Status: dodano kasjera. Login: " + QString::fromStdString(L) + ", haslo: 1234"
        );
}

void MainWindow::onKasjerSellTicketClicked()
{
    Kasjer* kasjer = dynamic_cast<Kasjer*>(aktualnyUzytkownik);

    if (kasjer == nullptr) {
        ui->statusLabel->setText("Status: tylko kasjer moze sprzedac karnet.");
        return;
    }

    bool ok;

    QString imie = QInputDialog::getText(
        this,
        "Sprzedaj karnet",
        "Imie klienta:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || imie.isEmpty()) {
        ui->statusLabel->setText("Status: anulowano sprzedaz karnetu.");
        return;
    }

    QString nazwisko = QInputDialog::getText(
        this,
        "Sprzedaj karnet",
        "Nazwisko klienta:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || nazwisko.isEmpty()) {
        ui->statusLabel->setText("Status: anulowano sprzedaz karnetu.");
        return;
    }

    Klient* istniejacyKlient = nullptr;

    for (auto& osoba : stacja.osoby) {
        Klient* klient = dynamic_cast<Klient*>(osoba.get());

        if (klient != nullptr &&
            klient->getImie() == imie.toStdString() &&
            klient->getNazwisko() == nazwisko.toStdString()) {
            istniejacyKlient = klient;
            break;
        }
    }

    if (istniejacyKlient != nullptr && istniejacyKlient->czyMaKarnet()) {
        ui->statusLabel->setText("Status: klient ma juz zakupiony karnet.");

        QMessageBox::information(
            this,
            "Karnet juz istnieje",
            "Ten klient ma juz zakupiony karnet. Nie mozna sprzedac kolejnego."
            );

        return;
    }

    TypKarnetu typ = wybierzTypKarnetu(this, &ok);
    if (!ok) {
        ui->statusLabel->setText("Status: anulowano sprzedaz karnetu.");
        return;
    }

    bool ulga = QMessageBox::question(
                    this,
                    "Ulga",
                    "Czy karnet ulgowy?",
                    QMessageBox::Yes | QMessageBox::No
                    ) == QMessageBox::Yes;

    double cena = kasjer->sprawdzCene(stacja, typ) * (ulga ? 0.75 : 1.0);

    QMessageBox::StandardButton decyzja = QMessageBox::question(
        this,
        "Potwierdzenie sprzedazy",
        "Cena karnetu: " + QString::number(cena, 'f', 2) + " zl\n"
                                                           "Czy potwierdzasz sprzedaz?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (decyzja != QMessageBox::Yes) {
        ui->statusLabel->setText("Status: anulowano sprzedaz karnetu.");
        return;
    }

    kasjer->sprzedajKarnet(
        stacja,
        imie.toStdString(),
        nazwisko.toStdString(),
        typ,
        ulga
        );

    odswiezOsoby();

    ui->statusLabel->setText(
        "Status: sprzedano karnet za " + QString::number(cena, 'f', 2) + " zl."
        );
}

void MainWindow::onKasjerSetPriceClicked()
{
    Kasjer* kasjer = dynamic_cast<Kasjer*>(aktualnyUzytkownik);

    if (kasjer == nullptr) {
        ui->statusLabel->setText("Status: tylko kasjer moze ustawic cene.");
        return;
    }

    bool ok;

    TypKarnetu typ = wybierzTypKarnetu(this, &ok);
    if (!ok) {
        ui->statusLabel->setText("Status: anulowano ustawianie ceny.");
        return;
    }

    double cena = QInputDialog::getDouble(
        this,
        "Ustaw cene",
        "Nowa cena:",
        1.0,
        0.01,
        100000.0,
        2,
        &ok
        );

    if (!ok) {
        ui->statusLabel->setText("Status: anulowano ustawianie ceny.");
        return;
    }

    kasjer->ustawCene(stacja, typ, cena);

    ui->statusLabel->setText(
        "Status: ustawiono cene: " + QString::number(cena, 'f', 2) + " zl."
        );
}
void MainWindow::onKasjerCheckPriceClicked()
{
    Kasjer* kasjer = dynamic_cast<Kasjer*>(aktualnyUzytkownik);

    if (kasjer == nullptr) {
        ui->statusLabel->setText("Status: tylko kasjer moze sprawdzic cene.");
        return;
    }

    bool ok;

    TypKarnetu typ = wybierzTypKarnetu(this, &ok);
    if (!ok) {
        ui->statusLabel->setText("Status: anulowano sprawdzanie ceny.");
        return;
    }

    double cena = kasjer->sprawdzCene(stacja, typ);

    QMessageBox::information(
        this,
        "Cena karnetu",
        "Cena: " + QString::number(cena, 'f', 2) + " zl"
        );

    ui->statusLabel->setText("Status: sprawdzono cene karnetu.");
}

void MainWindow::onOperatorOpenLiftClicked()
{
    Operator* op = dynamic_cast<Operator*>(aktualnyUzytkownik);

    if (op == nullptr) {
        ui->statusLabel->setText("Status: tylko operator moze otworzyc wyciag.");
        return;
    }

    bool ok;

    int id = QInputDialog::getInt(
        this,
        "Otworz wyciag",
        "ID wyciagu:",
        1,
        1,
        100000,
        1,
        &ok
        );

    if (!ok) {
        ui->statusLabel->setText("Status: anulowano otwieranie wyciagu.");
        return;
    }

    Wyciag* wyciag = nullptr;

    for (auto& w : stacja.wyciagi) {
        if (w->getId() == id) {
            wyciag = w.get();
            break;
        }
    }

    if (wyciag == nullptr) {
        ui->statusLabel->setText(
            "Status: nie znaleziono wyciagu o ID " + QString::number(id) + "."
            );

        QMessageBox::warning(
            this,
            "Brak wyciagu",
            "Nie znaleziono wyciagu o podanym ID."
            );

        return;
    }

    if (wyciag->isOtwarty()) {
        ui->statusLabel->setText(
            "Status: wyciag ID " + QString::number(id) + " jest juz otwarty."
            );

        QMessageBox::information(
            this,
            "Wyciag juz otwarty",
            "Ten wyciag jest juz otwarty."
            );

        return;
    }

    op->otworzWyciagOP(stacja, id);

    odswiezWyciagi();

    ui->statusLabel->setText(
        "Status: otwarto wyciag ID " + QString::number(id) + "."
        );
}

void MainWindow::onOperatorCloseLiftClicked()
{
    Operator* op = dynamic_cast<Operator*>(aktualnyUzytkownik);

    if (op == nullptr) {
        ui->statusLabel->setText("Status: tylko operator moze zamknac wyciag.");
        return;
    }

    bool ok;

    int id = QInputDialog::getInt(
        this,
        "Zamknij wyciag",
        "ID wyciagu:",
        1,
        1,
        100000,
        1,
        &ok
        );

    if (!ok) {
        ui->statusLabel->setText("Status: anulowano zamkniecie wyciagu.");
        return;
    }

    Wyciag* wyciag = nullptr;

    for (auto& w : stacja.wyciagi) {
        if (w->getId() == id) {
            wyciag = w.get();
            break;
        }
    }

    if (wyciag == nullptr) {
        ui->statusLabel->setText(
            "Status: nie znaleziono wyciagu o ID " + QString::number(id) + "."
            );

        QMessageBox::warning(
            this,
            "Brak wyciagu",
            "Nie znaleziono wyciagu o podanym ID."
            );

        return;
    }

    int aktywni = wyciag->getLiczbaAktywnychWjazdow(stacja.z.getSec());

    if (aktywni > 0) {
        ui->statusLabel->setText(
            "Status: nie mozna zamknac wyciagu ID " +
            QString::number(id) +
            ", bo sa na nim osoby."
            );

        QMessageBox::warning(
            this,
            "Nie mozna zamknac",
            "Nie mozna zamknac wyciagu, poniewaz sa na nim osoby."
            );

        return;
    }

    op->zamknijWyciagOP(stacja, id);

    odswiezWyciagi();

    ui->statusLabel->setText(
        "Status: zamknieto wyciag ID " + QString::number(id) + "."
        );
}

void MainWindow::onOperatorStopLiftClicked()
{
    Operator* op = dynamic_cast<Operator*>(aktualnyUzytkownik);

    if (op == nullptr) {
        ui->statusLabel->setText("Status: tylko operator moze zatrzymac wyciag.");
        return;
    }

    bool ok;

    int id = QInputDialog::getInt(
        this,
        "Zatrzymaj wyciag",
        "ID wyciagu:",
        1,
        1,
        100000,
        1,
        &ok
        );

    if (!ok) {
        ui->statusLabel->setText("Status: anulowano zatrzymanie wyciagu.");
        return;
    }

    Wyciag* wyciag = nullptr;

    for (auto& w : stacja.wyciagi) {
        if (w->getId() == id) {
            wyciag = w.get();
            break;
        }
    }

    if (wyciag == nullptr) {
        ui->statusLabel->setText(
            "Status: nie znaleziono wyciagu o ID " + QString::number(id) + "."
            );
        return;
    }

    int czas = QInputDialog::getInt(
        this,
        "Zatrzymaj wyciag",
        "Czas zatrzymania w sekundach:",
        60,
        1,
        100000,
        1,
        &ok
        );

    if (!ok) {
        ui->statusLabel->setText("Status: anulowano zatrzymanie wyciagu.");
        return;
    }

    op->zatrzymajWyciagOP(stacja, id, czas);

    odswiezWyciagi();

    ui->statusLabel->setText(
        "Status: zatrzymano wyciag ID " +
        QString::number(id) +
        " na " +
        QString::number(czas) +
        " s."
        );
}

void MainWindow::onOperatorAddLiftClicked()
{
    Operator* op = dynamic_cast<Operator*>(aktualnyUzytkownik);

    if (op == nullptr) {
        ui->statusLabel->setText("Status: tylko operator moze dodac wyciag.");
        return;
    }

    bool ok;

    int id = QInputDialog::getInt(
        this,
        "Dodaj wyciag",
        "ID wyciagu:",
        1,
        1,
        100000,
        1,
        &ok
        );

    if (!ok) {
        ui->statusLabel->setText("Status: anulowano dodawanie wyciagu.");
        return;
    }

    for (auto& w : stacja.wyciagi) {
        if (w->getId() == id) {
            ui->statusLabel->setText(
                "Status: wyciag o ID " + QString::number(id) + " juz istnieje."
                );

            QMessageBox::warning(
                this,
                "Wyciag juz istnieje",
                "Wyciag o podanym ID juz istnieje."
                );

            return;
        }
    }

    int czas = QInputDialog::getInt(
        this,
        "Dodaj wyciag",
        "Czas wjazdu w sekundach:",
        300,
        1,
        100000,
        1,
        &ok
        );

    if (!ok) {
        ui->statusLabel->setText("Status: anulowano dodawanie wyciagu.");
        return;
    }

    op->dodajWyciag(stacja, id, czas);

    odswiezWyciagi();

    ui->statusLabel->setText(
        "Status: dodano wyciag ID " +
        QString::number(id) +
        " z czasem wjazdu " +
        QString::number(czas) +
        " s."
        );
}

void MainWindow::onOperatorRemoveLiftClicked()
{
    Operator* op = dynamic_cast<Operator*>(aktualnyUzytkownik);

    if (op == nullptr) {
        ui->statusLabel->setText("Status: tylko operator moze usunac wyciag.");
        return;
    }

    bool ok;

    int id = QInputDialog::getInt(
        this,
        "Usun wyciag",
        "ID wyciagu:",
        1,
        1,
        100000,
        1,
        &ok
        );

    if (!ok) {
        ui->statusLabel->setText("Status: anulowano usuwanie wyciagu.");
        return;
    }

    Wyciag* wyciag = nullptr;

    for (auto& w : stacja.wyciagi) {
        if (w->getId() == id) {
            wyciag = w.get();
            break;
        }
    }

    if (wyciag == nullptr) {
        ui->statusLabel->setText(
            "Status: nie znaleziono wyciagu o ID " + QString::number(id) + "."
            );

        QMessageBox::warning(
            this,
            "Brak wyciagu",
            "Nie znaleziono wyciagu o podanym ID."
            );

        return;
    }

    int aktywni = wyciag->getLiczbaAktywnychWjazdow(stacja.z.getSec());

    if (aktywni > 0) {
        ui->statusLabel->setText(
            "Status: nie mozna usunac wyciagu ID " +
            QString::number(id) +
            ", bo sa na nim osoby."
            );

        QMessageBox::warning(
            this,
            "Nie mozna usunac",
            "Nie mozna usunac wyciagu, poniewaz sa na nim osoby."
            );

        return;
    }

    op->usunWyciag(stacja, id);

    odswiezWyciagi();

    ui->statusLabel->setText(
        "Status: usunieto wyciag ID " + QString::number(id) + "."
        );
}

void MainWindow::onKlientBuyTicketClicked()
{
    Klient* klient = dynamic_cast<Klient*>(aktualnyUzytkownik);

    if (klient == nullptr) {
        ui->statusLabel->setText("Status: blad - zalogowany uzytkownik nie jest klientem.");
        return;
    }

    if (klient->czyMaKarnet() && !klient->czyKarnetWygasl(stacja)) {
        ui->statusLabel->setText("Status: klient ma juz zakupiony wazny lub nieaktywny karnet.");

        QMessageBox::information(
            this,
            "Karnet juz istnieje",
            "Masz juz zakupiony karnet. Nowy karnet mozesz kupic dopiero po wygasnieciu obecnego."
            );

        return;
    }

    bool ok;

    TypKarnetu typ = wybierzTypKarnetu(this, &ok);
    if (!ok) {
        ui->statusLabel->setText("Status: anulowano zakup karnetu.");
        return;
    }

    bool ulga = QMessageBox::question(
                    this,
                    "Ulga",
                    "Czy karnet ulgowy?",
                    QMessageBox::Yes | QMessageBox::No
                    ) == QMessageBox::Yes;

    double cena = stacja.cennik.getCena(typ) * (ulga ? 0.75 : 1.0);

    QMessageBox::StandardButton decyzja = QMessageBox::question(
        this,
        "Potwierdzenie zakupu",
        "Cena karnetu: " + QString::number(cena, 'f', 2) + " zl\n"
                                                           "Czy potwierdzasz zakup?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (decyzja != QMessageBox::Yes) {
        ui->statusLabel->setText("Status: anulowano zakup karnetu.");
        return;
    }

    klient->kupKarnet(stacja, typ, ulga);

    odswiezOsoby();

    ui->statusLabel->setText(
        "Status: kupiono karnet za " + QString::number(cena, 'f', 2) + " zl."
        );
}

void MainWindow::onKlientEnterLiftClicked()
{
    Klient* klient = dynamic_cast<Klient*>(aktualnyUzytkownik);

    if (klient == nullptr) {
        ui->statusLabel->setText("Status: blad - zalogowany uzytkownik nie jest klientem.");
        return;
    }

    if (!klient->czyMaKarnet()) {
        ui->statusLabel->setText("Status: nie mozna wejsc na wyciag - klient nie ma karnetu.");

        QMessageBox::warning(
            this,
            "Brak karnetu",
            "Nie mozna wejsc na wyciag, poniewaz klient nie ma karnetu."
            );

        return;
    }

    if (!klient->czyKarnetAktywowany() && !klient->czyMoznaAktywowacKarnet(stacja)) {
        ui->statusLabel->setText("Status: nie mozna teraz aktywowac tego karnetu.");

        QMessageBox::warning(
            this,
            "Nie mozna aktywowac",
            "Nie mozna teraz aktywowac tego karnetu."
            );

        return;
    }

    if (klient->czyKarnetAktywowany() && !klient->czyKarnetAktywny(stacja)) {
        ui->statusLabel->setText("Status: karnet wygasl albo nie jest teraz aktywny.");

        QMessageBox::warning(
            this,
            "Karnet nieaktywny",
            "Nie mozna wejsc na wyciag, poniewaz karnet wygasl albo nie jest teraz aktywny."
            );

        return;
    }

    bool ok;

    int id = QInputDialog::getInt(
        this,
        "Wejdz na wyciag",
        "ID wyciagu:",
        1,
        1,
        100000,
        1,
        &ok
        );

    if (!ok) {
        ui->statusLabel->setText("Status: anulowano wejscie na wyciag.");
        return;
    }

    Wyciag* wyciag = nullptr;

    for (auto& w : stacja.wyciagi) {
        if (w->getId() == id) {
            wyciag = w.get();
            break;
        }
    }

    if (wyciag == nullptr) {
        ui->statusLabel->setText(
            "Status: nie znaleziono wyciagu o ID " + QString::number(id) + "."
            );

        QMessageBox::warning(
            this,
            "Brak wyciagu",
            "Nie znaleziono wyciagu o podanym ID."
            );

        return;
    }

    if (wyciag->isZatrzymany(stacja.z.getSec())) {
        ui->statusLabel->setText("Status: nie mozna wejsc - wyciag jest zatrzymany.");

        QMessageBox::warning(
            this,
            "Wyciag zatrzymany",
            "Nie mozna wejsc na zatrzymany wyciag. Poczekaj, az zostanie ponownie uruchomiony."
            );

        return;
    }

    if (!wyciag->isOtwarty()) {
        ui->statusLabel->setText("Status: nie mozna wejsc - wyciag jest zamkniety.");

        QMessageBox::warning(
            this,
            "Wyciag zamkniety",
            "Nie mozna wejsc na zamkniety wyciag."
            );

        return;
    }

    for (auto& w : stacja.wyciagi) {
        if (w->czyKlientJedzie(klient->getLogin(), stacja.z.getSec())) {
            ui->statusLabel->setText(
                "Status: klient " + QString::fromStdString(klient->getLogin()) +
                " jest juz na innym wyciagu."
                );

            QMessageBox::warning(
                this,
                "Klient jest na wyciagu",
                "Klient jest juz na wyciagu. Poczekaj, az zakonczy obecny wjazd."
                );

            return;
        }
    }

    bool aktywowanoTeraz = !klient->czyKarnetAktywowany();

    klient->wejdzNaWyciag(stacja, id);

    if (!wyciag->czyKlientJedzie(klient->getLogin(), stacja.z.getSec())) {
        ui->statusLabel->setText("Status: nie udalo sie wejsc na wyciag.");

        QMessageBox::warning(
            this,
            "Nieudane wejscie",
            "Nie udalo sie wejsc na wyciag. Sprawdz waznosc karnetu i stan wyciagu."
            );

        odswiezWyciagi();
        odswiezOsoby();
        return;
    }

    odswiezWyciagi();
    odswiezOsoby();

    if (aktywowanoTeraz) {
        ui->statusLabel->setText(
            "Status: aktywowano karnet i rozpoczeto wjazd wyciagiem ID " +
            QString::number(id) + "."
            );
    }
    else {
        ui->statusLabel->setText(
            "Status: klient rozpoczal wjazd wyciagiem ID " +
            QString::number(id) + "."
            );
    }
}
void MainWindow::onKlientCheckTicketClicked()
{
    Klient* klient = dynamic_cast<Klient*>(aktualnyUzytkownik);

    if (klient == nullptr) {
        ui->statusLabel->setText("Status: blad - zalogowany uzytkownik nie jest klientem.");
        return;
    }

    QString opis = QString::fromStdString(
        klient->opisWaznosciKarnetu(stacja)
        );

    QMessageBox::information(
        this,
        "Waznosc karnetu",
        opis
        );

    ui->statusLabel->setText("Status: sprawdzono waznosc karnetu.");
}

void MainWindow::onChangePasswordClicked()
{
    if (aktualnyUzytkownik == nullptr) {
        ui->statusLabel->setText("Status: nikt nie jest zalogowany.");
        return;
    }

    bool ok;

    QString stare = QInputDialog::getText(
        this,
        "Zmien haslo",
        "Stare haslo:",
        QLineEdit::Password,
        "",
        &ok
        );

    if (!ok || stare.isEmpty()) {
        ui->statusLabel->setText("Status: anulowano zmiane hasla.");
        return;
    }

    if (!aktualnyUzytkownik->sprawdzHaslo(stare.toStdString())) {
        ui->statusLabel->setText("Status: niepoprawne stare haslo.");

        QMessageBox::warning(
            this,
            "Blad zmiany hasla",
            "Wpisano niepoprawne stare haslo."
            );

        return;
    }

    QString nowe = QInputDialog::getText(
        this,
        "Zmien haslo",
        "Nowe haslo:",
        QLineEdit::Password,
        "",
        &ok
        );

    if (!ok || nowe.isEmpty()) {
        ui->statusLabel->setText("Status: anulowano zmiane hasla.");
        return;
    }

    aktualnyUzytkownik->zmienHaslo(
        stare.toStdString(),
        nowe.toStdString()
        );

    ui->statusLabel->setText("Status: haslo zostalo zmienione.");
}

void MainWindow::odswiezCzas()
{
    ui->timeLabel->setText(
        QString::fromStdString(stacja.z.getTime())
        );

    ui->dateLabel->setText(
        QString::fromStdString(stacja.z.getDate())
        );
}

void MainWindow::odswiezWyciagi()
{
    QString tekst;

    int czasObecny = stacja.z.getSec();

    if (stacja.wyciagi.empty()) {
        tekst = "Brak wyciagow.";
    }

    for (auto& w : stacja.wyciagi) {
        int aktywni = w->getLiczbaAktywnychWjazdow(czasObecny);

        tekst += "ID: ";
        tekst += QString::number(w->getId());
        tekst += " | ";
        tekst += QString::fromStdString(w->getStatus(czasObecny));
        tekst += " | czas wjazdu: ";
        tekst += QString::number(w->getCzasWjazdu());
        tekst += " s";
        tekst += " | osoby na wyciagu: ";
        tekst += QString::number(aktywni);
        tekst += "\n";

        tekst += QString::fromStdString(
            w->getOpisAktywnychWjazdow(czasObecny)
            );

        tekst += "\n";
    }

    ui->wyciagiTextEdit->setPlainText(tekst);
}

void MainWindow::odswiezOsoby()
{
    QString kasjerzy;
    QString operatorzy;
    QString klienci;

    for (auto& p : stacja.pracownicy) {
        QString osoba = QString::fromStdString(p->getLogin());

        if (dynamic_cast<Kasjer*>(p.get())) {
            kasjerzy += osoba + "\n";
        }
        else if (dynamic_cast<Operator*>(p.get())) {
            operatorzy += osoba + "\n";
        }
    }

    for (auto& o : stacja.osoby) {
        Klient* klient = dynamic_cast<Klient*>(o.get());

        QString osoba = QString::fromStdString(o->getLogin());

        if (klient != nullptr) {
            if (!klient->czyMaKarnet()) {
                osoba += " | brak karnetu";
            }
            else if (!klient->czyKarnetAktywowany()) {
                osoba += " | karnet nieaktywny";
            }
            else {
                int pozostalo = klient->getPozostaleSekundyKarnetu(stacja);

                if (pozostalo > 0) {
                    osoba += " | karnet zostalo: " + formatujSekundy(pozostalo);
                }
                else {
                    osoba += " | karnet wygasl";
                }
            }
        }

        klienci += osoba + "\n";
    }

    QString tekst;

    tekst += "--- KASJERZY ---\n";
    tekst += (kasjerzy.isEmpty() ? "brak\n" : kasjerzy);

    tekst += "\n--- OPERATORZY ---\n";
    tekst += (operatorzy.isEmpty() ? "brak\n" : operatorzy);

    tekst += "\n--- KLIENCI ---\n";
    tekst += (klienci.isEmpty() ? "brak\n" : klienci);

    ui->osobyTextEdit->setPlainText(tekst);
}
void MainWindow::onSetDateTimeClicked()
{
    bool ok;

    QString input = QInputDialog::getText(
        this,
        "Ustaw date i czas",
        "Wpisz w formacie:\nHH:MM:SS | DD.MM.RRRR",
        QLineEdit::Normal,
        QString::fromStdString(stacja.z.getTime()) + " | " + QString::fromStdString(stacja.z.getDate()),
        &ok
        );

    if (!ok || input.isEmpty()) {
        ui->statusLabel->setText("Status: anulowano zmiane czasu.");
        return;
    }

    int h, m, s, D, M, R;

    if (!stacja.wczytajDateCzas(input.toStdString(), h, m, s, D, M, R)) {
        ui->statusLabel->setText("Status: bledny format daty lub godziny.");

        QMessageBox::warning(
            this,
            "Bledny format",
            "Wpisz czas w formacie:\nHH:MM:SS | DD.MM.RRRR\n\nPrzyklad:\n12:30:00 | 06.12.2025"
            );

        return;
    }

    stacja.ustawGodzineDate(h, m, s, D, M, R);

    odswiezCzas();
    odswiezWyciagi();
    odswiezOsoby();

    ui->statusLabel->setText(
        "Status: ustawiono czas na " + input + "."
        );
}