#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>

#include "Stacja.h"
#include "Osoba.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Stacja stacja;
    Osoba* aktualnyUzytkownik = nullptr;

    QTimer* refreshTimer = nullptr;

    void odswiezCzas();
    void odswiezWyciagi();
    void odswiezOsoby();
    void onSetDateTimeClicked();

private slots:
    void onLoginClicked();
    void onLogoutClicked();
    void onSpeedChanged(int index);

    void onAddOperatorClicked();
    void onAddKasjerClicked();

    void onKasjerSellTicketClicked();
    void onKasjerSetPriceClicked();
    void onKasjerCheckPriceClicked();

    void onOperatorOpenLiftClicked();
    void onOperatorCloseLiftClicked();
    void onOperatorStopLiftClicked();
    void onOperatorAddLiftClicked();
    void onOperatorRemoveLiftClicked();

    void onKlientBuyTicketClicked();
    void onKlientEnterLiftClicked();
    void onKlientCheckTicketClicked();

    void onChangePasswordClicked();
};

#endif