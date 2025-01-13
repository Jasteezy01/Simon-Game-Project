/*
 * CS3505
 * Assignment 06
 * Jadon Olson and Nathaniel Atwood
 * October 28, 2024
 *
 * GitHub Usernames:
 * Jasteezy01
 * QuanAloha
 * https://github.com/University-of-Utah-CS3505/a6-simon-f24-QuanAloha.git
 *
 * High score feature,
 * visual with progress bar,
 * and game over display
 */

#include "mainview.h"
#include "simongamemodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimonGameModel gameModel;
    MainView w(gameModel);
    w.show();
    return a.exec();
}
