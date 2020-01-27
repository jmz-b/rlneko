#include <stdlib.h>
#include <raylib.h>
#include "terrain.h"

Terrain LoadTerrain(TerrainConfig config) {
    // dynamic memory allocation to store pixels data (Color type)
    Color *pixels = (Color *)malloc(config.width * config.height * sizeof(Color));

    // generate checked pattern
    for (int y = 0; y < config.height; y++) {
        for (int x = 0; x < config.width; x++) {
            if (((x/32+y/32)/1)%2 == 0) pixels[y * config.width + x] = LIGHTGRAY;
            else pixels[y * config.width + x] = GRAY;
        }
    }

    // load pixels data into an image structure and create texture
    Image image = LoadImageEx(pixels, config.width, config.height);
    // ExportImage(image, "terrain.png");
    Texture2D texture = LoadTextureFromImage(image);

    // dynamic memory must be freed after using it
    free(pixels);
    UnloadImage(image);

    return (Terrain) { config, texture };
}

void UnloadTerrain(Terrain *terrain) {
    UnloadTexture(terrain->texture);
}