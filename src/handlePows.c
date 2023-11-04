#include "include/txaplat.h"

t_rotatingPow *createRotatingPows(t_platform *platforms, t_movingPlatform *movPlatform, float playerHeight) {
    t_rotatingPow *rotatingPows = (t_rotatingPow *) MemAlloc(sizeof (t_rotatingPow) * 4);
    for (int i = 0; i < 4; i++) {
        if (i == 0)
            rotatingPows[i].pow = LoadTexture("./assets/sprites/pow/bowlingPin.png");
        else if (i == 1)
            rotatingPows[i].pow = LoadTexture("./assets/sprites/pow/arrowUp.png");
        else if (i == 2)
            rotatingPows[i].pow = LoadTexture("./assets/sprites/pow/clock.png");
        else    
            rotatingPows[i].pow = LoadTexture("./assets/sprites/pow/exit.png");
        rotatingPows[i].taken = false;
        rotatingPows[i].isRendered = false;
        rotatingPows[i].rotationAngle = 0;
        rotatingPows[i].rotationSpeed = 1.0f;
        rotatingPows[i].origin = (Vector2) { rotatingPows[i].pow.width / 2, rotatingPows[i].pow.height / 2 };
        if (i == 0) {
            rotatingPows[i].position.x = platforms[11].position.x + (platforms[11].platform.width >> 1);
            rotatingPows[i].position.y = platforms[11].position.y - playerHeight / 2;
        }
        else if (i == 1) {
            rotatingPows[i].position.x = movPlatform[4].position.x + (rotatingPows[i].pow.width >> 1);
            rotatingPows[i].position.y = HEIGHT >> 1;
        }
        else if (i == 2) {
            rotatingPows[i].position.x = platforms[15].position.x + platforms[15].platform.width / 2;
            rotatingPows[i].position.y = platforms[15].position.y - playerHeight / 2;
        }
        else {
            rotatingPows[i].position.x = LEVELWIDTH - rotatingPows[i].pow.width;
            rotatingPows[i].position.y = platforms[15].position.y - playerHeight / 2;
        }
    }
    return rotatingPows;
}

void updateRotatingPows(t_player *player, t_rotatingPow *rotatingPows, Rectangle cameraRect) {

    for (int i = 0; i < 4; i++) {
        if (i == 1 && player->isResumed) //renderizza nuovamente arrowup dopo la morte del player
            rotatingPows[i].taken = false;

        if(rotatingPows[i].taken)
            continue;

        Rectangle powCollision = { rotatingPows[i].position.x, rotatingPows[i].position.y, rotatingPows[i].pow.width, rotatingPows[i].pow.height };
        if (CheckCollisionRecs(powCollision, cameraRect))
            rotatingPows[i].isRendered = true;
        else
            rotatingPows[i].isRendered = false;
    
        if (CheckCollisionRecs(player->collision, powCollision)) {
            rotatingPows[i].taken = true;
            PlaySound(player->pow);
            if (i == 0)
                player->shots += 5;
            else if (i == 2) {
                player->level = 1.01f;
                player->isLevelCreated = false;
            }
            else if (i == 3) {
                player->level = 1.11f;
                player->isLevelCreated = false;
            }
        }
        else {
            float rotationLimit = 22.5f;

            rotatingPows[i].rotationAngle += rotatingPows[i].rotationSpeed;
            if (rotatingPows[i].rotationAngle >= rotationLimit || rotatingPows[i].rotationAngle <= -rotationLimit)
                rotatingPows[i].rotationSpeed *= -1;

        }
    }
}

void createBowlingBall(t_movingPow *bowlingBall, t_player *player) {
    bowlingBall->pow = LoadTexture("./assets/sprites/bowlingBall/bowlingBall.png");
    bowlingBall->position.x = player->position.x + player->drawTexture.width;
    bowlingBall->position.y = player->position.y + player->drawTexture.height;
    bowlingBall->velocity = (Vector2) { 0, 0 };
    bowlingBall->active = false;
    bowlingBall->rotationAngle = 0.0f;
    bowlingBall->origin = (Vector2){ bowlingBall->pow.width / 2, bowlingBall->pow.height / 2 };
}

void updateBowlingBall(t_player *player, t_movingPow *bowlingBall, t_platform *platforms, t_rotatingPow *rotatingPows) {
    if (IsKeyPressed(KEY_SPACE) && !bowlingBall->active && rotatingPows[0].taken && player->shots > 0) {
        bowlingBall->active = true;
        bowlingBall->position.x = player->position.x + player->idle[0].width;
        bowlingBall->position.y = player->position.y + player->idle[0].height - bowlingBall->pow.height;
        player->shots--;
        
        if (player->isFacingLeft) {
            bowlingBall->position.x = player->position.x - player->idle[0].width;
            bowlingBall->velocity.x = -10.0f;
        }
        else {
            bowlingBall->position.x = player->position.x + player->idle[0].width;
            bowlingBall->velocity.x = 10.0f;
        }
    }

    if (bowlingBall->active) {
        if (!IsSoundPlaying(player->launchBowlingBall))
            PlaySound(player->launchBowlingBall);
        bowlingBall->velocity.y += GRAVITY / 60.0f;
        if (bowlingBall->velocity.x > 0)
            bowlingBall->rotationAngle += 15.0f;
        else
            bowlingBall->rotationAngle -= 15.0f;
        for (int i = 0; i < 16; i++) {
            if (bowlingBall->position.y + bowlingBall->pow.height >= platforms[i].position.y &&
                bowlingBall->position.y + bowlingBall->pow.height <= platforms[i].position.y + platforms[i].platform.height &&
                bowlingBall->position.x >= platforms[i].position.x &&
                bowlingBall->position.x <= platforms[i].position.x + platforms[i].platform.width) {
                bowlingBall->position.y = platforms[i].position.y;
                bowlingBall->velocity.y = 0; 
            }
        }
        if (bowlingBall->position.x + bowlingBall->pow.width > player->limit + WIDTH || bowlingBall->position.x < player->limit || bowlingBall->position.y > HEIGHT)
            bowlingBall->active = false;
        bowlingBall->position.y += bowlingBall->velocity.y; 
        bowlingBall->position.x += bowlingBall->velocity.x;
    }

}
