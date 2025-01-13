/*
 * CS3505
 * Assignment 06
 * Jadon Olson and Nathaniel Atwood
 * October 28, 2024
 */
#include "mainview.h"
#include "ui_mainview.h"
#include "simongamemodel.h"
#include <QTimer>
#include <QQueue>
#include <cstdlib>
#include <ctime>
#include <queue>


MainView::MainView(SimonGameModel& gameModel, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainView)
    , gameModel(gameModel) //Initialize gameModel
{
    ui->setupUi(this);

    ui->redButton->setDisabled(true); //disable red button
    ui->blueButton->setDisabled(true); //disable blue button
    ui->blueButton->setStyleSheet("background-color: blue"); //Set bluebutton color
    ui->redButton->setStyleSheet("background-color: red"); //Set redbutton color
    ui->gameOverText->setVisible(false);

    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainView::startGame); //Connect to startGame

    connect(ui->redButton,
            &QPushButton::clicked,
            &gameModel,
            &SimonGameModel::redPressed); //Connect to redPressed

    connect(ui->blueButton,
            &QPushButton::clicked,
            &gameModel,
            &SimonGameModel::bluePressed); //Connect to bluePressed

    connect(&gameModel,
            &SimonGameModel::gameOver,
            this,
            &MainView::endGame);

    connect(&gameModel,
            &SimonGameModel::updateProgress,
            this,
            &MainView::setProgress);

    connect(&gameModel,
            &SimonGameModel::levelPassed,
            this,
            &MainView::levelPassed);
}

MainView::~MainView() {
    delete ui;
}

void MainView::startGame() {
    ui->startButton->setDisabled(true);
    ui->blueButton->setDisabled(true);
    ui->redButton->setDisabled(true);
    ui->gameOverText->setVisible(false);
    while (!gameModel.sequence.empty()) {
        gameModel.sequence.pop();
    }
    gameModel.score = 0;
    ui->currentScoreTracker->display(0);
    gameModel.progress = 0;
    ui->progressBar->setValue(0);
    ui->progressBarTracker->display(0);

    // Wait 1 second before starting the flashing sequence
    QTimer::singleShot(1000, this, [this]() {
        // Generate the next level sequence and convert it to QQueue
        std::queue<int> seq = gameModel.nextLevel();
        QQueue<int> sequenceQueue;

        // Move the elements from std::queue to QQueue
        while (!seq.empty()) {
            sequenceQueue.enqueue(seq.front());
            seq.pop();
        }

        // Start flashing the buttons
        flashSequence(sequenceQueue);
    });
}

void MainView::flashSequence(QQueue<int> sequenceQueue) {
    ui->redButton->setDisabled(true);
    ui->blueButton->setDisabled(true);
    if (sequenceQueue.isEmpty()) {
        // Re-enable the buttons after the sequence finishes
        ui->redButton->setDisabled(false);
        ui->blueButton->setDisabled(false);
        return;
    }

    int nextValue = sequenceQueue.dequeue();
    QPushButton* button = (nextValue == 1) ? ui->redButton : ui->blueButton;
    QColor originalColor = (nextValue == 1) ? QColor("red") : QColor("blue");
    QColor flashColor = (nextValue == 1) ? QColor("lightcoral") : QColor("lightblue");

    // Change the button color to the flash color
    button->setStyleSheet("background-color: " + flashColor.name());

    // Use a singleShot timer to revert the color back after a short delay
    QTimer::singleShot(500, this, [this, button, originalColor, sequenceQueue]() mutable {
        button->setStyleSheet("background-color: " + originalColor.name());
        // Move to the next button in the sequence
        QTimer::singleShot(1000, this, [this, sequenceQueue]() mutable {
            flashSequence(sequenceQueue); // Pass the updated queue copy
        });
    });
}

void MainView::endGame(){
    ui->blueButton->setDisabled(true);
    ui->redButton->setDisabled(true);
    ui->startButton->setEnabled(true);
    ui->gameOverText->setVisible(true);
    while (!gameModel.sequence.empty()) {
        gameModel.sequence.pop();
    }
    gameModel.score = 0;
    ui->progressBar->setValue(0);
    ui->progressBarTracker->display(0);
}

void MainView::setProgress(int progress){
    ui->progressBar->setValue(progress);
    ui->progressBarTracker->display(progress);
}

void MainView::levelPassed(){
    QTimer::singleShot(1000, this, [this]() {
        gameModel.progress = 0;
        gameModel.score++;
        ui->currentScoreTracker->display(gameModel.score);
        if(gameModel.score > gameModel.highScore){
            gameModel.highScore = gameModel.score;
            ui->highScoreTracker->display(gameModel.highScore);
        }

        ui->progressBar->setValue(0);
        ui->progressBarTracker->display(0);
        // Generate the next level sequence and convert it to QQueue
        std::queue<int> seq = gameModel.nextLevel();
        QQueue<int> sequenceQueue;

        // Move the elements from std::queue to QQueue
        while (!seq.empty()) {
            sequenceQueue.enqueue(seq.front());
            seq.pop();
        }

        // Start flashing the buttons
        flashSequence(sequenceQueue);
    });
}
