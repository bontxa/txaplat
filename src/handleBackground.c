#include "include/txaplat.h"

t_background *createBackground(t_player *player, short totalElements) {
    t_background *background;
    if (player->level == 1) {
        short startSeaPosition;
        background = (t_background *) MemAlloc(sizeof (t_background) * totalElements);
        for (int i = 0; i < totalElements; i++) {
            if (i < 11) {
                if (i == 0 || i == 2)
                    background[i].background = LoadTexture("./assets/sprites/background/back1.png");
                else if (i == 1 || i == 3 || i == 4)
                    background[i].background = LoadTexture("./assets/sprites/background/back2.png");
                else if (i == 5)
                    background[i].background = LoadTexture("./assets/sprites/background/back3.png");
                else {
                background[i].background = LoadTexture("./assets/sprites/background/cloudSky.png");}
                background[i].position = (Vector2) { i * background[i].background.width, 0 };
            }
            else if (i < 20) {
                background[i].background = LoadTexture("./assets/sprites/background/sea.png");
                if (i == 11)
                    startSeaPosition = 4800;
                background[i].position = (Vector2) { startSeaPosition , HEIGHT - background[i].background.height };
                startSeaPosition += background[i].background.width;
            }
            else {
                background[i].background = LoadTexture("./assets/sprites/background/house.png");
                background[i].position = (Vector2) { 0,  HEIGHT - BASEHEIGHT - background[i].background.height };
            }
            background[i].isRendered = false;
        }
    }
    return background;
}

void updateBackground(t_background *background, Rectangle cameraRect, short totalElements) {
    for (int i = 0; i < totalElements; i++) {

        Rectangle backgroundCollision = { background[i].position.x, background[i].position.y, background[i].background.width, background[i].background.height };
        if (CheckCollisionRecs(backgroundCollision, cameraRect))
            background[i].isRendered = true;
        else
            background[i].isRendered = false;
    }
}
