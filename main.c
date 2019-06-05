#include "tictactoe.h"

int main() {
    struct Move m1 = { 0, 0 };
    struct Move m2 = { 0, 0 };
    struct Player p1 = { false, PLAYER_TOKEN, &m1 };
    struct Player p2 = { true, COMP_TOKEN, &m2 };
    struct Game game = {
        .currentPlayer = &p1,
        .board = {
            {' ',' ',' '},
            {' ',' ',' '},
            {' ',' ',' '}
        },
        .p1 = &p1,
        .p2 = &p2
    }; 
    for (int moves = 0; moves < 9; ++moves) {
        if (! game.currentPlayer->isComp) {
            GamePrint(&game);
        }
        GameGetMove(&game);
        GameCheckWin(&game);
        GameSwitchPlayer(&game);
    }
    GameEnd(&game, TIE);
}
