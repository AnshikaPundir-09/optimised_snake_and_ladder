#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scoreboard.h"

#define MAX_PLAYERS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int moves;
    int finished;
} MovePlayer;

typedef struct {
    char name[NAME_LEN];
    time_t start;
    time_t end;
    double duration;
    int finished;
} TimePlayer;

static MovePlayer moveHeap[MAX_PLAYERS];
static TimePlayer timeHeap[MAX_PLAYERS];
static int moveSize = 0;
static int timeSize = 0;
static int totalPlayers = 0;

void initScoreboard(int players) {
    totalPlayers = players;
    moveSize = 0;
    timeSize = 0;
    for (int i = 0; i < players; i++) {
        sprintf(moveHeap[i].name, "Player %d", i + 1);
        moveHeap[i].moves = 0;
        moveHeap[i].finished = 0;

        sprintf(timeHeap[i].name, "Player %d", i + 1);
        timeHeap[i].start = 0;
        timeHeap[i].end = 0;
        timeHeap[i].duration = 0.0;
        timeHeap[i].finished = 0;
    }
}

void recordMove(int playerIndex) {
    moveHeap[playerIndex].moves++;
}

void swapMove(int a, int b) {
    MovePlayer temp = moveHeap[a];
    moveHeap[a] = moveHeap[b];
    moveHeap[b] = temp;
}

void heapifyUpMove(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (moveHeap[index].moves < moveHeap[parent].moves) {
            swapMove(index, parent);
            index = parent;
        } else break;
    }
}

void declareMoveWinner(int playerIndex) {
    moveHeap[playerIndex].finished = 1;
    moveHeap[moveSize++] = moveHeap[playerIndex];
    heapifyUpMove(moveSize - 1);
}

void showMoveScoreboard() {
    printf("\n Move-Based Scoreboard (Least Moves First):\n");
    for (int i = 0; i < moveSize; i++) {
        printf("%d. %s - %d moves\n", i + 1, moveHeap[i].name, moveHeap[i].moves);
    }
}

void startTimer(int playerIndex) {
    timeHeap[playerIndex].start = time(NULL);
}

void stopTimer(int playerIndex) {
    timeHeap[playerIndex].end = time(NULL);
    timeHeap[playerIndex].duration = difftime(timeHeap[playerIndex].end, timeHeap[playerIndex].start);
}

void swapTime(int a, int b) {
    TimePlayer temp = timeHeap[a];
    timeHeap[a] = timeHeap[b];
    timeHeap[b] = temp;
}

void heapifyUpTime(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (timeHeap[index].duration < timeHeap[parent].duration) {
            swapTime(index, parent);
            index = parent;
        } else break;
    }
}

void declareTimeWinner(int playerIndex) {
    timeHeap[playerIndex].finished = 1;
    timeHeap[timeSize++] = timeHeap[playerIndex];
    heapifyUpTime(timeSize - 1);
}

void showTimeScoreboard() {
    printf("\n Time-Based Scoreboard (Fastest First):\n");
    for (int i = 0; i < timeSize; i++) {
        printf("%d. %s - %.2f seconds\n", i + 1, timeHeap[i].name, timeHeap[i].duration);
    }
}

void freeScoreboard() {
    moveSize = 0;
    timeSize = 0;
}