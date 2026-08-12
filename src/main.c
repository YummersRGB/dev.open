#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "game.h"

static void *framebuffer = NULL;
static GXRModeObj *rmode = NULL;

void system_init(void) {
    VIDEO_Init();
    WPAD_Init();

    rmode = VIDEO_GetPreferredMode(NULL);
    framebuffer = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

    CONSOLE_Init(framebuffer, 20, 20, rmode->fbWidth, rmode->xfbHeight, 
                 rmode->fbWidth * VI_DISPLAY_PIXELS_TO_BYTES);

    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(framebuffer);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
}

int main(int argc, char **argv) {
    system_init();

    GameState game;
    game_init(&game);

    while (game.is_running) {
        game_update(&game);
        game_render(&game);
        VIDEO_WaitVSync();
    }

    printf("\nExiting to Homebrew Channel...\n");
    return 0;
}