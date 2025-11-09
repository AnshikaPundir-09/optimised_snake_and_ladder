#ifndef SCOREBOARD_H
#define SCOREBOARD_H

void initScoreboard(int totalPlayers);

void recordMove(int playerIndex);
void declareMoveWinner(int playerIndex);
void showMoveScoreboard();

void startTimer(int playerIndex);
void stopTimer(int playerIndex);
void declareTimeWinner(int playerIndex);
void showTimeScoreboard();

void freeScoreboard();

#endif

