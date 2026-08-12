#ifndef GAME_H
#define GAME_H

#include <gccore.h>
#include <wiiuse/wpad.h>

typedef struct {
    int score;
    int player_x;
    int is_running;
} GameState;

void game_init(GameState *game);
void game_update(GameState *game);
void game_render(const GameState *game);

#endif // GAME_H