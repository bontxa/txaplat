#include "include/txaplat.h"

void createCamera(Camera2D *camera) {
    camera->target = (Vector2) { WIDTH / 2, HEIGHT / 2 };
    camera->offset = (Vector2) { WIDTH / 2, HEIGHT / 2 };
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
}

static float Lerp(float start, float end, float t) {
    return start + (end - start) * t;
}

void updateCamera(Camera2D *camera, t_player *player) {
    if (player->isResumed) {
        camera->target.x = player->position.x + player->idle[0].width / 2;
        player->isResumed = false;
    } else
        camera->target.x = Lerp(camera->target.x, player->position.x + player->idle[0].width / 2, 0.05f);

    if (camera->target.x < player->limit + WIDTH / 2)
        camera->target.x = player->limit + WIDTH / 2;
    else if (camera->target.x > LEVELWIDTH - camera->offset.x)
        camera->target.x = LEVELWIDTH - camera->offset.x;
}
