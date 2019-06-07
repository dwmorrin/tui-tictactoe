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
        .p2 = &comp,
        .done = false
    }; 
    while (true) {
        for (int moves = 0; moves < 9 && ! game.done; ++moves) {
            if (! game.currentPlayer->isComp) {
                GamePrint(&game);
            }
            GameGetMove(&game);
            GameCheckWin(&game);
            GameSwitchPlayer(&game);
        }
        if (! game.done) {
            GameEnd(&game, TIE);
        }
        int tryAgain = getInput("play again? ");
        if (tryAgain != 'y' && tryAgain != 'Y') {
            break;
        }
        GameReset(&game);
    }
}
