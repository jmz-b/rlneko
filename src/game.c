#include "player.h"
#include "game.h"

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

Game LoadGame(int width, int height, int FPS) {
    // render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(width, height);
    SetTextureFilter(target.texture, FILTER_POINT);  // texture scale filter to use

    Player player = LoadPlayer("resources/tora.png", width, height);
    float scale = 1;

    return (Game) { target, player, width, height, FPS, scale };
}

void UpdateGame(Game *game) { 
    game->scale = min((float)GetScreenWidth()/game->width, (float)GetScreenHeight()/game->height);
    UpdatePlayer(&game->player, game->FPS);

}

void DrawGame(Game *game) {
    ClearBackground(BLACK);

    // draw to RenderTexture2D
    BeginTextureMode(game->target);
        ClearBackground(RAYWHITE);
        DrawPlayer(&game->player);
    EndTextureMode();

    // draw RenderTexture2D to window, properly scaled
    DrawTexturePro(
        game->target.texture,
        (Rectangle){ 0.0f, 0.0f, (float)game->target.texture.width, (float)-game->target.texture.height },
        (Rectangle) {
            (GetScreenWidth() - ((float)game->width * game->scale)) * 0.5,
            (GetScreenHeight() - ((float)game->height * game->scale)) * 0.5,
            (float)game->width * game->scale, (float)game->height * game->scale
        },
        (Vector2){ 0, 0 },
        0.0f, WHITE
    );
}

void UnloadGame(Game *game) {
    UnloadPlayer(&game->player);
}