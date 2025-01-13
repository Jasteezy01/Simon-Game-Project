/*
 * CS3505
 * Assignment 06
 * Jadon Olson and Nathaniel Atwood
 * October 28, 2024
 */
#include "simongamemodel.h"
#include <QDebug>
#include <queue>
#include <cstdlib>
#include <ctime>

SimonGameModel::SimonGameModel(QObject *parent)
    : QObject{parent} // Initialize level if needed
{}

void SimonGameModel::bluePressed() {
    if(progress == 0){
        currentSequence = sequence;
    }

    if(currentSequence.front() == 0){
        progress += ((1.0/sequence.size()) * 100);
        emit updateProgress(progress);
        currentSequence.pop();
        if(currentSequence.size() == 0){
            emit levelPassed();
        }
    }
    else{
        emit gameOver();
    }
}

void SimonGameModel::redPressed() {
    if(progress == 0){
        currentSequence = sequence;
    }
    if(currentSequence.front() == 1){
        progress += ((1.0/sequence.size()) * 100);
        emit updateProgress(progress);
        currentSequence.pop();
        if(currentSequence.size() == 0){
            emit levelPassed();
        }
    }
    else{
        emit gameOver();
    }

}

std::queue<int> SimonGameModel::nextLevel() {
    std::srand(static_cast<unsigned>(std::time(0))); // Seed rand() with current time
    sequence.push(rand() % 2); // Generates 0 or 1 and adds to the queue


    return sequence; // Return the generated sequence
}
