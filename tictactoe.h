#ifndef TUI_TICTACTOE
#define TUI_TICTACTOE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define OPEN_TOKEN ' '
#define PLAYER_TOKEN 'X' 
#define COMP_TOKEN 'O'
#define BOARD_BORDER "     --|---|--\n"
#define BOARD_ROW "%d%d%d: %c | %c | %c\n"

enum {WIN, TIE, LOSE};

struct Move {
    int row, col;
} playersMove, compsMove;

struct Player {
    bool isComp;
    char token;
    struct Move *move;
} player, comp;

struct Game {
    bool done;
    char board[3][3];
    struct Player *p1, *p2, *currentPlayer;
} game;

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

int getInput(char*);
void init(void);
bool GameCheckSquares(struct Game*, struct Player*);
void GameCheckWin(struct Game*);
void GameCompMove(struct Game*);
void GameGetMove(struct Game*);
void GameEnd(struct Game*, int);
void GameFindWinningMove(struct Game*, struct Player*, struct Move*);
void GamePlayerMove(struct Game*);
void GamePrint(struct Game*);
void GameReset(struct Game*);
void GameSwitchPlayer(struct Game*);
bool PlayerMove(struct Player*, struct Move*);
void PlayerSetMove(struct Player*, struct Move*);

#endif
