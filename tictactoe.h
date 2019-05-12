#ifndef TUI_TICTACTOE
#define TUI_TICTACTOE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 9
#define WINS_SIZE 8
#define OPEN_TOKEN ' '
#define PLAYER_TOKEN 'X' 
#define COMP_TOKEN 'O'
#define BOARD_BORDER "     --|---|--\n"
#define BOARD_ROW "%d%d%d: %c | %c | %c\n"

enum {WIN, TIE, LOSE};

/*
 * board is held in a 9 element array
 * mapped as follows:
 *   0 | 1 | 2
 *   --|---|--
 *   3 | 4 | 5
 *   --|---|--
 *   6 | 7 | 8
 * winning combinations are:
 * Rows: 012, 345, 678
 * Cols: 036, 147, 258
 * Diag: 048, 246
 */
char squares[BOARD_SIZE];
int wins[WINS_SIZE][3] = {
    {0,1,2}, {3,4,5}, {6,7,8},
    {0,3,6}, {1,4,7}, {2,5,8},
    {0,4,8}, {2,4,6}
};

/* checkSquares scans squares for winning combinations for player */
int checkSquares(char board[], char player);

void compMove(void);

void end(int result);

/* findWinningSquare searches board for squares the player could win with
 * If a winning square is found, the computer chooses it
 */
int findWinningSquare(char player);

int getInput(char *prompt);

int hasSet(char board[], char player, int set[]);

void playerMove(void);

/* printBoard displays the current status in a terminal
 * TODO implement in ncurses
 */
void printBoard(void);

void resetBoard(void);

#endif
