#include <raylib.h>
#include "player.h"
#include "game.h"

Game LoadGame(GameConfig gameConfig, PlayerConfig playerConfig) {
    RenderTexture2D target = LoadRenderTexture(gameConfig.width, gameConfig.height);
    Player player = LoadPlayer(playerConfig);

    SetTextureFilter(target.texture, FILTER_POINT);  // texture scale filter to use

    return (Game) { gameConfig, target, player };
}

void UpdateGame(Game *game) { 
    UpdatePlayer(&game->player);

    // step player animation every gameFPS/playerFPS cycles
    if (game->player.framesCounter >= game->config.FPS/game->player.config.FPS) {
        game->player.framesCounter = 0;
        AnimatePlayer(&game->player);
    };
}

void DrawGame(Game *game) {
    ClearBackground(LIGHTGRAY);
    DrawPlayer(&game->player);
}

void UnloadGame(Game *game) {
    UnloadPlayer(&game->player);
}