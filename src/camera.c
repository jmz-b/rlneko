#include <raylib.h>
#include <raymath.h>
#include "camera.h"

void UpdateSmoothFollowCamera(SmoothFollowCamera *camera, Vector2 targetPosition) {
    // get pointer to nested Camera2D structure
    Camera2D *camera2d = (Camera2D *)camera;

    const float delta = GetFrameTime();
    Vector2 diff = Vector2Subtract(targetPosition, camera2d->target);
    float length = Vector2Length(diff);
    
    if (length > camera->config.minEffectLength) {
        float speed = fmaxf(camera->config.fractionSpeed * length, camera->config.minSpeed);
        camera2d->target = Vector2Add(camera2d->target, Vector2Scale(diff, speed * delta/length));
    }
}