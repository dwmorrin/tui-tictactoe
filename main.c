#include "tictactoe.h"

int main() {
    struct Move m1 = {0, 0}, m2 = {0, 0};
    struct Player player = {false, PLAYER_TOKEN, &m1},
                  comp = {true, COMP_TOKEN, &m2};
    struct Game game = {
        .currentPlayer = &player,
        .board = {
            {' ',' ',' '},
            {' ',' ',' '},
            {' ',' ',' '}
        },
        .p1 = &player,
        .p2 = &comp
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
