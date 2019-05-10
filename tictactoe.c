#include "tictactoe.h"

int main(void) {
    for (;;) {
        printBoard();
        playerMove();
        if (checkSquares(squares, PLAYER_TOKEN)) {
            printBoard();
            puts("Player has won");
            break;
        }
        compMove();
        if (checkSquares(squares, COMP_TOKEN)) {
            printBoard();
            puts("Comp has won");
            break;
        }
    }
    return 0;
}

int checkSquares(int board[], int player) {
    for (int i = 0; i < WINS_SIZE; ++i) {
        if (hasSet(board, player, wins[i])) {
            return 1;
        }
    }
    return 0;
}

void compMove() {
    int choice;
    choice = findWinningSquare(COMP_TOKEN);
    if (choice < 0) {
        choice = findWinningSquare(PLAYER_TOKEN);
    }
    if (choice > -1) {
        squares[choice] = COMP_TOKEN;
        return;
    }
    int i = 0;
    while (squares[i] != OPEN_TOKEN) {
        ++i;
    }
    squares[i] = COMP_TOKEN;
}

int findWinningSquare(int player) {
    int boardCopy[9];
    memcpy(boardCopy, squares, 9 * sizeof(int));
    for (int i = 0; i < 9; ++i) {
        if (boardCopy[i] != OPEN_TOKEN) {
            continue;
        }
        boardCopy[i] = player;
        if (checkSquares(boardCopy, player)) {
            return i;
        }
        boardCopy[i] = OPEN_TOKEN;
    }
    return -1;
}

int hasSet(int board[], int player, int set[]) {
    for (int i = 0; i < 3; ++i) {
        if (board[set[i]] != player) {
            return 0;
        }
    }
    return 1;
}

void playerMove() {
    int choice, input;
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
    squares[choice] = PLAYER_TOKEN;
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
