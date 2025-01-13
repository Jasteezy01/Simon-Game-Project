/*
 * CS3505
 * Assignment 06
 * Jadon Olson and Nathaniel Atwood
 * October 28, 2024
 */
#ifndef SIMONGAMEMODEL_H
#define SIMONGAMEMODEL_H

#include <QObject>
#include <queue>
using std::queue;

class SimonGameModel : public QObject
{
    Q_OBJECT




public:
    explicit SimonGameModel(QObject *parent = nullptr);
    int score = 0;
    int highScore = 0;
    int level = 1;
    int progress = 0;
    std::queue<int> sequence;
    std::queue<int> currentSequence;


public slots:
    void bluePressed();
    void redPressed();
    queue<int> nextLevel();
signals:
    void gameOver();
    void updateProgress(int);
    void levelPassed();
};

#endif // SIMONGAMEMODEL_H
