#include <stdio.h>
#include "game.h"

void game_init(GameState *game) {
    game->score = 0;
    game->player_x = 10;
    game->is_running = 1;
}

void game_update(GameState *game) {
    WPAD_ScanPads();
    u32 pressed = WPAD_ButtonsDown(0);

    // Wiimote Button Handlers
    if (pressed & WPAD_BUTTON_A) {
        game->score += 10;
    }
    if (pressed & WPAD_BUTTON_RIGHT) {
        game->player_x++;
    }
    if (pressed & WPAD_BUTTON_LEFT) {
        if (game->player_x > 0) game->player_x--;
    }
    if (pressed & WPAD_BUTTON_HOME) {
        game->is_running = 0;
    }
}

void game_render(const GameState *game) {
    // Reset cursor position to top-left of the TV console
    printf("\x1b[20;0H");
    printf("=========================================\n");
    printf("         WII DEV HOMEBREW GAME           \n");
    printf("=========================================\n\n");
    printf(" Player Position X: %d  \n", game->player_x);
    printf(" Current Score:    %d  \n\n", game->score);
    printf(" Controls:\n");
    printf("  - D-Pad Left / Right : Move Player\n");
    printf("  - [A] Button        : Add Points\n");
    printf("  - [HOME] Button     : Exit Game\n");
}