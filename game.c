#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

static int positions[2] = {0, 0};
static const char* players[2] = {"Player 1", "Player 2"};

int rollDice() {
    return rand() % 6 + 1;
}

int playerMoves(int player, int roll) {
    int pos = positions[player] + roll;
    if (pos > MAX_POSITION) return positions[player];

    int ladder = ladderClimb(pos);
    if (ladder != pos) {
        printf(" Ladder! Climbed up from %d to %d\n", pos, ladder);
        pos = ladder;
    } else {
        int snake = Snaketail(pos);
        if (snake != pos) {
            printf(" Snake! Slid down from %d to %d\n", pos, snake);
            pos = snake;
        }
    }

    positions[player] = pos;
    return pos;
}

void boardgame(int p1, int p2) {
    printf(" Game Board:\n");
    for (int row = 9; row >= 0; row--) {
        for (int col = 0; col < 10; col++) {
            int pos = (row % 2 == 0) ? row * 10 + col + 1 : row * 10 + (9 - col) + 1;

            if (pos == p1 && pos == p2){
                printf("[A&B%2d]", pos);
            }
            else if (pos == p1)
            {
                printf("[A%3d]", pos);
            }
            else if (pos == p2){
                printf("[B%3d]", pos);
            }
            else
            {
                printf("[%5d]", pos);
            }
        }
        printf("\n");
    }
    printf("Token at: Player 1 -> %d, Player 2 -> %d\n\n", p1, p2);
}

void gameplay() {
    srand(time(NULL));
    int turn = 0;

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

    while (1) {
        printf("%s's turn. Press Enter to roll the dice...\n", players[turn]);
        getchar();

        int roll = rollDice();
        printf(" You rolled: %d\n", roll);
        printf(" Scoreboard:\n%s rolled:  %d\n", players[turn], roll);

        int newpos = playerMoves(turn, roll);
        printf("%s moved to: %d\n\n", players[turn], newpos);

         boardgame(positions[0], positions[1]);

        if (newpos == MAX_POSITION) {
            printf(" %s wins the game!\n", players[turn]);
            break;
        }

        turn = 1-turn;
    }
}