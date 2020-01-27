#ifndef TERRAIN_H
#define TERRAIN_H

#include <raylib.h>

typedef struct {
    int width;
    int height;
} TerrainConfig;

typedef struct {
    TerrainConfig config;
    Texture2D texture;
} Terrain;


Terrain LoadTerrain(TerrainConfig config);
void UnloadTerrain(Terrain *terrain);

#endif