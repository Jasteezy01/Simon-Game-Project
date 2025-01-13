/*
 * CS3505
 * Assignment 06
 * Jadon Olson and Nathaniel Atwood
 * October 28, 2024
 */
#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "simongamemodel.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainView;
}
QT_END_NAMESPACE

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(SimonGameModel& gameModel, QWidget *parent = nullptr);
    ~MainView();

private:
    Ui::MainView *ui;
    SimonGameModel& gameModel; // Store a reference to the game model
    void flashSequence(QQueue<int> sequenceQueue); // Flash the buttons based on the sequence

private slots:
    void startGame(); // New slot for starting the game
    void endGame();
    void setProgress(int);
    void levelPassed();
};
#endif // MAINVIEW_H
