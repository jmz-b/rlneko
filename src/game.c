#include "player.h"
#include "game.h"

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

Game LoadGame(GameConfig gameConfig, PlayerConfig playerConfig) {
    // render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(gameConfig.width, gameConfig.height);
    SetTextureFilter(target.texture, FILTER_POINT);  // texture scale filter to use

    Player player = LoadPlayer(playerConfig);
    float scale = 1;

    return (Game) { gameConfig, target, player, scale };
}

void UpdateGame(Game *game) { 
    game->scale = min((float)GetScreenWidth()/game->config.width, (float)GetScreenHeight()/game->config.height);

    UpdatePlayer(&game->player);

    // step player animation every gameFPS/playerFPS cycles
    if (game->player.framesCounter >= game->config.FPS/game->player.config.FPS) {
        game->player.framesCounter = 0;
        AnimatePlayer(&game->player);
    };

}

void DrawGame(Game *game) {
    ClearBackground(BLACK);

    // draw to RenderTexture2D
    BeginTextureMode(game->target);
        ClearBackground(LIGHTGRAY);
        DrawPlayer(&game->player);
    EndTextureMode();

    // draw RenderTexture2D to window, properly scaled
    DrawTexturePro(
        game->target.texture,
        (Rectangle){ 0.0f, 0.0f, (float)game->target.texture.width, (float)-game->target.texture.height },
        (Rectangle) {
            (GetScreenWidth() - ((float)game->config.width * game->scale)) * 0.5,
            (GetScreenHeight() - ((float)game->config.height * game->scale)) * 0.5,
            (float)game->config.width * game->scale, (float)game->config.height * game->scale
        },
        (Vector2){ 0, 0 },
        0.0f, WHITE
    );
}

void UnloadGame(Game *game) {
    UnloadPlayer(&game->player);
}