#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

typedef struct {
    int minSpeed;
    int minEffectLength;
    int fractionSpeed;
} SmoothFollowCameraConfig;

typedef struct {
    Camera2D camera2d;
    SmoothFollowCameraConfig config;
} SmoothFollowCamera;

void UpdateSmoothFollowCamera(SmoothFollowCamera *camera, Vector2 targetPosition);

#endif