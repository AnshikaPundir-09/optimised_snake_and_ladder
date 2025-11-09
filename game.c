#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "board.h"
#include "scoreboard.h"  

static int* positions;
static char** players;
static int numPlayers;

int rollDice() {
    return rand() % 6 + 1;
}

int playerMoves(int player, int roll) {
    int pos = positions[player] + roll;
    if (pos > MAX_POSITION) return positions[player];

    int ladder = checkLadder(pos);
    if (ladder != pos) {
        printf(" Ladder! Climbed up from %d to %d\n", pos, ladder);
        pos = ladder;
    } else {
        int snake = checkSnake(pos);
        if (snake != pos) {
            printf(" Snake! Slid down from %d to %d\n", pos, snake);
            pos = snake;
        }
    }

    positions[player] = pos;
    return pos;
}

void boardgame() {
    printf(" Game Board:\n");
    for (int row = 9; row >= 0; row--) {
        for (int col = 0; col < 10; col++) {
            int pos = (row % 2 == 0) ? row * 10 + col + 1 : row * 10 + (9 - col) + 1;
            char token[10] = "";
            for (int i = 0; i < numPlayers; i++) {
                if (positions[i] == pos) {
                    char label = 'A' + i;
                    int len = strlen(token);
                    token[len] = label;
                    token[len + 1] = '\0';
                }
            }
            if (strlen(token) > 0) {
                printf("[%s%3d]", token, pos);
            } else {
                printf("[%5d]", pos);
            }
        }
        printf("\n");
    }
    printf("Token positions:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf(" Player %c -> %d\n", 'A' + i, positions[i]);
    }
    printf("\n");
}

void gameplay() {
    srand(time(NULL));
    printf("Enter number of players: ");
    scanf("%d", &numPlayers);
    getchar(); 

    positions = (int*)calloc(numPlayers, sizeof(int));
    players = (char**)malloc(numPlayers * sizeof(char*));
    for (int i = 0; i < numPlayers; i++) {
        players[i] = (char*)malloc(20);
        sprintf(players[i], "Player %d", i + 1);
    }

    initScoreboard(numPlayers);  

    printf(" Starting Snake and Ladder Game!\n\n");
    printf(" Snake and Ladder Board Setup:\nSnakes:\n");
    printf("  Head at 99 -> Tail at 78\n  Head at 95 -> Tail at 75\n  Head at 92 -> Tail at 88\n");
    printf("  Head at 89 -> Tail at 68\n  Head at 74 -> Tail at 53\n  Head at 62 -> Tail at 19\n");
    printf("  Head at 49 -> Tail at 11\n  Head at 46 -> Tail at 25\n  Head at 16 -> Tail at 6\n\n");
    printf("Ladders:\n");
    printf("  Base at 2 -> Top at 38\n  Base at 7 -> Top at 14\n  Base at 8 -> Top at 31\n");
    printf("  Base at 15 -> Top at 26\n  Base at 21 -> Top at 42\n  Base at 28 -> Top at 84\n");
    printf("  Base at 36 -> Top at 44\n  Base at 51 -> Top at 67\n  Base at 71 -> Top at 91\n");
    printf("  Base at 78 -> Top at 98\n  Base at 87 -> Top at 94\n\n");

    int turn = 0;
    while (1) {
        printf("%s's turn. Press Enter to roll the dice...\n", players[turn]);
        getchar();

        if (positions[turn] == 0) {
            startTimer(turn);  
        }

        int roll = rollDice();
        printf(" You rolled: %d\n", roll);
        printf(" Scoreboard:\n%s rolled:  %d\n", players[turn], roll);

        recordMove(turn);  

        int newpos = playerMoves(turn, roll);
        printf("%s moved to: %d\n\n", players[turn], newpos);

        boardgame();

        if (newpos == MAX_POSITION) {
            stopTimer(turn);  
            printf(" %s wins the game!\n", players[turn]);

            declareMoveWinner(turn);
            declareTimeWinner(turn);

            showMoveScoreboard();
            showTimeScoreboard();
            break;
        }

        turn = (turn + 1) % numPlayers;
    }

    for (int i = 0; i < numPlayers; i++) {
        free(players[i]);
    }
    free(players);
    free(positions);
    freeScoreboard();  
}
