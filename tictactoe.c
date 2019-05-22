#include "tictactoe.h"

int main(void) {
    resetBoard();
    for (int moves = 0;; ++moves) {
        printBoard();
        playerMove();
        if (checkSquares(squares, PLAYER_TOKEN)) {
            end(WIN);
            moves = -1;
        } else if (moves == 4) {
            end(TIE);
            moves = -1;
        } else {
            compMove();
            if (checkSquares(squares, COMP_TOKEN)) {
                end(LOSE);
                moves = -1;
            }
        }
    }
    return 0;
}

int checkSquares(char board[], char player) {
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

void end(int result) {
    printBoard();
    switch (result) {
        case TIE:
            puts("It's a tie!");
            break;
        case WIN:
            puts("You won!");
            break;
        case LOSE:
            puts("Computer won.");
            break;
    }

    int choice;
    do {
        choice = getInput("\nPlay again? [y/n] ");
    } while (choice != 'Y' && choice != 'y' &&
             choice != 'N' && choice != 'n');

    if (choice == 'Y' || choice == 'y') {
        resetBoard();
        return;
    }
    exit(EXIT_SUCCESS);
}

int findWinningSquare(char player) {
    char boardCopy[BOARD_SIZE];
    memcpy(boardCopy, squares, BOARD_SIZE * sizeof(char));
    for (int i = 0; i < BOARD_SIZE; ++i) {
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

int getInput(char *prompt) {
    int c, input;
    printf("%s", prompt);
    c = getchar();
    input = c;
    /* discard remaining input */
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
    return input;
}

void playerMove() {
    int choice, row;
    do {
        choice = getInput("\nChoose [1-9]: ");
        choice -= '0' + 1;
        if (choice < 0 || choice > 8) {
            continue;
        }
        row = 0;
        while (row > 2) {
            choice -= 3;
            ++row;
        }
    } while (squares[row][choice] != OPEN_TOKEN);
    squares[row][choice] = PLAYER_TOKEN;
}

void printBoard(void) {
    printf("\n");
    for (int i = 0, j = 0; i < 3; ++i) {
        j = i * 3;
        printf(BOARD_ROW, j + 1, j + 2, j + 3,
                squares[i][0], squares[i][1], squares[i][2]);
        if (i < 2) {
            printf(BOARD_BORDER);
        }
    }
}

void resetBoard(void) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        squares[i] = OPEN_TOKEN;
    }
}
