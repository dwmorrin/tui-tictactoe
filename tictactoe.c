#include "tictactoe.h"

int main(void) {
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

int hasSet(int board[], int player, int set[]) {
    for (int i = 0; i < 3; ++i) {
        if (board[set[i]] != player) {
            return 0;
        }
    }
    return 1;
}

void playerMove() {
    int choice;
    do {
        choice = getInput("\nChoose [0-9]: ");
        choice -= '0';
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

void resetBoard(void) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        squares[i] = OPEN_TOKEN;
    }
}
