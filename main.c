#include "tictactoe.h"

int main() {
    struct Move move = { -1, -1 };
    struct Move m1 = { 0, 0 };
    struct Move m2 = { 0, 0 };
    struct Player p1 = { false, PLAYER_TOKEN, &m1 };
    struct Player p2 = { true, COMP_TOKEN, &m2 };
    struct Game game = {
        .currentToken = PLAYER_TOKEN,
        .board = {
            {' ',' ',' '},
            {' ',' ',' '},
            {' ',' ',' '}
        },
        .p1 = &p1,
        .p2 = &p2
    }; 
    for (;;) {
        GamePrint(&game);
        while(! PlayerMove(&p1, &move) ||
                game.board[move.row][move.col] != OPEN_TOKEN);
        PlayerSetMove(&p1, &move);
        game.board[move.row][move.col] = PLAYER_TOKEN;
        if (GameCheckSquares(&game, &p1)) {
            GameEnd(&game, WIN);
        }
        GameCompMove(&game, &p2);
        if (GameCheckSquares(&game, &p2)) {
            GameEnd(&game, LOSE);
        }
    }
}
