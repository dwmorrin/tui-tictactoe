#include "tictactoe.h"

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

bool GameCheckSquares(struct Game *game, struct Player *player) {
    int row = player->move->row,
        col = player->move->col;
    if (game->board[row][0] == player->token &&
        game->board[row][1] == player->token &&
        game->board[row][2] == player->token) {
        return true;
    }
    if (game->board[0][col] == player->token &&
        game->board[1][col] == player->token &&
        game->board[2][col] == player->token) {
        return true;
    }
    if (row == col &&
        game->board[0][0] == player->token &&
        game->board[1][1] == player->token &&
        game->board[2][2] == player->token) {
        return true;
    }
    if (row + col == 2 &&
        game->board[0][2] == player->token &&
        game->board[1][1] == player->token &&
        game->board[2][0] == player->token) {
        return true;
    }
    return false;
}

void GameCheckWin(struct Game *game) {
    if (GameCheckSquares(game, game->currentPlayer)) {
        int result = game->currentPlayer->isComp ?
            LOSE : WIN;
        GameEnd(game, result);
    }
}

void GameCompMove(struct Game *game) {
    struct Player *comp = game->currentPlayer;
    if (! comp->isComp) {
        puts("illegal comp move");
        exit(EXIT_FAILURE);
    }
    struct Move move = {-1, -1};
    GameFindWinningMove(game, comp, &move);
    if (move.row < 0) {
        GameFindWinningMove(game, game->p1, &move);
    }
    if (move.row > -1) {
        game->board[move.row][move.col] = comp->token;
        PlayerSetMove(comp, &move);
        return;
    }
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (game->board[row][col] == OPEN_TOKEN) {
                game->board[row][col] = comp->token;
                PlayerSetMove(comp, &move);
                return;
            }
        }
    }
}

void GameEnd(struct Game *game, int result) {
    GamePrint(game);
    switch (result) {
        case WIN:
            puts("you won!");
            break;
        case LOSE:
            puts("you lose!");
            break;
        case TIE:
            puts("it's a tie!");
            break;
    }
    game->done = true;
}

/**
 * mutates the move, nothing else
 * usage: pass in a temp move and check the result
 * use -1 values to represent null
 */
void GameFindWinningMove(struct Game *game, struct Player *player, struct Move *move) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (game->board[row][col] != OPEN_TOKEN) {
                continue;
            }
            game->board[row][col] = player->token;
            if (GameCheckSquares(game, player)) {
                move->row = row;
                move->col = col;
                game->board[row][col] = OPEN_TOKEN;
                return;
            }
            game->board[row][col] = OPEN_TOKEN;
        }
    }
}

void GameGetMove(struct Game* game) {
    if (game->currentPlayer->isComp) {
        GameCompMove(game);
    } else {
        GamePlayerMove(game);
    }
}

void GamePlayerMove(struct Game *game) {
    struct Move move = {-1, -1};
    struct Player *p = game->currentPlayer;
    if (p->isComp) {
        puts("illegal player move");
        exit(EXIT_FAILURE);
    }
    while(! PlayerMove(p, &move) ||
            game->board[move.row][move.col] != OPEN_TOKEN);
    PlayerSetMove(p, &move);
    game->board[move.row][move.col] = PLAYER_TOKEN;
}

void GamePrint(struct Game *game) {
    for (int row = 0; row < 3; ++row) {
        printf(BOARD_ROW,
                3*row+1, 3*row+2, 3*row+3,
                game->board[row][0],
                game->board[row][1],
                game->board[row][2]);
        if (row < 2) {
            printf(BOARD_BORDER);
        }
    }
}

void GameReset(struct Game *game) {
    game->done = false;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            game->board[row][col] = OPEN_TOKEN;
        }
    }
}

void GameSwitchPlayer(struct Game *game) {
    game->currentPlayer = game->currentPlayer == game->p1 ?
        game->p2 : game->p1;
}

bool PlayerMove(struct Player *player, struct Move *move) {
    int choice;
    choice = getInput("\nChoose [1-9]: ");
    choice -= '0' + 1;
    if (choice < 0 || choice > 8) {
        return false;
    }
    move->row = 0;
    move->col = choice;
    while (move->col > 2) {
        move->col -= 3;
        ++(move->row);
    }
    return true;
}

void PlayerSetMove(struct Player *player, struct Move *move) {
    player->move->row = move->row;
    player->move->col = move->col;
}
