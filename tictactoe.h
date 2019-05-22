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
 * board is held in a 2d 3x3 array
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
char squares[3][3] = {
    {'-', '-', '-'},
    {'-', '-', '-'},
    {'-', '-', '-'}
};

/* checkSquares scans squares for winning combinations for player */
int checkSquares(char board[3][3], char player);

void compMove(void);

void end(int result);

/* findWinningSquare searches board for squares the player could win with
 * If a winning square is found, the computer chooses it
 */
int findWinningSquare(char player);

int getInput(char *prompt);

int hasSet(char board[3][3], char player, int set[]);

void playerMove(void);

/* printBoard displays the current status in a terminal
 * TODO implement in ncurses
 */
void printBoard(void);

void resetBoard(void);

#endif
