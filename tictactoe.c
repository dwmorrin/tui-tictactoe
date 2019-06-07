#include "tictactoe.h"

/**
 * getInput gets a single character from stdin
 * the caller is responsible for checking the value
 * a supplied string goes to stdout as a prompt
 */
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

/**
 * init initializes all the global variables
 */
void init(void) {
    playersMove.row = playersMove.col =
    compsMove.row = compsMove.col = 0;
    player.isComp = false;
    player.token = PLAYER_TOKEN;
    player.move = &playersMove;
    comp.isComp = true;
    comp.token = COMP_TOKEN;
    comp.move = &compsMove;
    game.currentPlayer = &player;
    game.p1 = &player;
    game.p2 = &comp;
    GameReset(&game);
}

/**
 * GameCheckSquares looks at the given player's last move
 * and checks the board to see if the player won.
 * A win returns true, otherwise returns false.
 */
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

/**
 * GameCheckWin is a wrapper for GameCheckSquares that
 * can be called each turn to determine if there was
 * a win or not.
 */
void GameCheckWin(struct Game *game) {
    if (GameCheckSquares(game, game->currentPlayer)) {
        int result = game->currentPlayer->isComp ?
            LOSE : WIN;
        GameEnd(game, result);
    }
}

/**
 * GameCompMove is a script for the comp player's turn
 * the comp tries to find a win for itself, or a
 * blocking move against player's next move, or
 * picks the next available square.
 */
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
    if (move.row < 0) {
        GameFindOpenMove(game, &move);
    }
    if (move.row > -1) {
        game->board[move.row][move.col] = comp->token;
        PlayerSetMove(comp, &move);
        return;
    }
    puts("no legal move for comp!");
    exit(EXIT_FAILURE);
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

/**
 * GameFindOpenMove sets the supplied Move to the
 * next open square.
 * TODO randomize this rather than always selecting
 * in order.
 */
void GameFindOpenMove(struct Game *game, struct Move *move) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (game->board[row][col] == OPEN_TOKEN) {
                move->row = row;
                move->col = col;
                return;
            }
        }
    }
}

/**
 * GameGetMove is a routing function that figures out whose
 * turn it is to play
 */
void GameGetMove(struct Game *game) {
    if (game->currentPlayer->isComp) {
        GameCompMove(game);
    } else {
        GamePlayerMove(game);
    }
}

/**
 * GamePlayerMove handles getting input and setting
 * the player's move.
 */
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

/**
 * GamePrint displays the board state on stdout
 */
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

/**
 * GameReset returns all squares to open and resets the done flag
 */
void GameReset(struct Game *game) {
    game->done = false;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            game->board[row][col] = OPEN_TOKEN;
        }
    }
}

/**
 * GameSwitchPlayer changes the player's turn
 */
void GameSwitchPlayer(struct Game *game) {
    game->currentPlayer = game->currentPlayer == game->p1 ?
        game->p2 : game->p1;
}

/**
 * PlayerMove is a wrapper for getInput that validates
 * and a helper that converts 0-9 to {row,col}
 */
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

/**
 * PlayerSetMove is a setter for a Player.move
 */
void PlayerSetMove(struct Player *player, struct Move *move) {
    player->move->row = move->row;
    player->move->col = move->col;
}
