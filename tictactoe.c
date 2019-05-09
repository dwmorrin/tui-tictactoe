#include "tictactoe.h"

int main(void) {
    int input, choice, player = 1, comp = 2;
    for (;;) {
        printBoard();
        do {
            printf("\nChoose [0-9]: ");
            input = getchar();
            input -= '0';
            choice = input;
            /* discard remaining input */
            while (input != '\n' && input != EOF) {
                input = getchar();
            }
        } while (choice < 0 || choice > 8 || squares[choice] != 0);
        squares[choice] = player;
        if (checkSquares(player)) {
            printBoard();
            puts("Player has won");
            break;
        }
        compMove(comp);
        if (checkSquares(comp)) {
            printBoard();
            puts("Comp has won");
            break;
        }
    }
    return 0;
}

int checkSquares(int player) {
    for (int i = 0; i < WINS_SIZE; ++i) {
        if (hasSet(player, wins[i])) {
            return 1;
        }
    }
    return 0;
}

void compMove(int comp) {
    int i = 0;
    while (squares[i] != 0) {
        ++i;
    }
    squares[i] = comp;
}

int hasSet(int player, int set[]) {
    for (int i = 0; i < 3; ++i) {
        if (squares[set[i]] != player) {
            return 0;
        }
    }
    return 1;
}

void printBoard(void) {
    printf("\n"
        " %d | %d | %d \n"
        " --|---|-- \n"
        " %d | %d | %d \n"
        " --|---|-- \n"
        " %d | %d | %d \n",
        squares[0], squares[1], squares[2],
        squares[3], squares[4], squares[5],
        squares[6], squares[7], squares[8]);
}
