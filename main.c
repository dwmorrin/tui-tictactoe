#include "tictactoe.h"

int main() {
    init();
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
            exit(EXIT_SUCCESS);
        }
        GameReset(&game);
    }
}
