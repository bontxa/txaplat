#include "include/txaplat.h"

static void createPlatform(t_platform *platform, char *str, float positionX, float positionY) {
    platform->platform = LoadTexture(str);
    platform->position = (Vector2) { positionX, positionY };
    platform->collision = (Rectangle) { platform->position.x, platform->position.y, platform->platform.width, platform->platform.height };
    platform->isRendered = false;
}

t_platform *createPlatforms(t_player *player, short numPlatforms) {
    
    t_platform *platforms = (t_platform *) MemAlloc(sizeof (t_platform) * numPlatforms);
    
    for (int i = 0; i < numPlatforms; i++) {
        if (player->level == 1) {
            if (i == 0) 
                createPlatform(&platforms[i], "./assets/sprites/base/grassBase.png", 0, HEIGHT - 192);
            if (i == 1) 
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform160.png", 832, HEIGHT - platforms[0].platform.height - 128);
            if (i == 2) 
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform128.png", platforms[1].position.x + 192, platforms[1].position.y - 128);
            if (i == 3) 
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform224.png", platforms[2].position.x + 192, platforms[2].position.y - 128);
            if (i == 4)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform384.png", 1952, HEIGHT - platforms[0].platform.height - 128);
            if (i == 5)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform288.png", platforms[4].position.x + 192, platforms[4].position.y - 128);
            if (i == 6)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform224.png", platforms[5].position.x + 160, platforms[5].position.y - 128);
            if (i == 7)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform256.png", 2816, HEIGHT - platforms[0].platform.height - 128);
            if (i == 8)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform256.png", platforms[7].position.x + 192, platforms[7].position.y - 128);
            if (i == 9)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform256.png", 3680, HEIGHT - platforms[0].platform.height - 128);
            if (i == 10)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform128.png", platforms[9].position.x + 128, platforms[9].position.y - 128);
            if (i == 11)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/platform64.png", platforms[10].position.x + 64, platforms[10].position.y - 128);
            if (i == 12)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/rock.png", 4320, HEIGHT - platforms[0].platform.height - 128);
            if (i == 13)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/rock.png", platforms[12].position.x + 128, platforms[12].position.y - 128);
            if (i == 14)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/rock640.png", platforms[13].position.x + 128, platforms[13].position.y - 128);
            if (i == 15)
                createPlatform(&platforms[i], "./assets/sprites/platforms/level0/rock640.png", LEVELWIDTH - 640, (HEIGHT >> 1) - (platforms[14].platform.height >> 1));
        }

        else if (player->level == 1.1f) {
            char *strPath = "./assets/sprites/platforms/level0/platform288.png";
            if (i == 0) 
                createPlatform(&platforms[i], strPath, 64, player[0].idle->height + BASEHEIGHT);
            if (i == 1) 
                createPlatform(&platforms[i], strPath, WIDTH - 64 - platforms[0].platform.width, platforms[0].position.y);
            if (i == 2) 
                createPlatform(&platforms[i], strPath, (WIDTH >> 2), (HEIGHT >> 2) + (HEIGHT >> 3));
            if (i == 3) 
                createPlatform(&platforms[i], strPath, (WIDTH >> 1) + (WIDTH >> 2) - (platforms[0].platform.width), platforms[2].position.y);
            if (i == 4)
                createPlatform(&platforms[i], strPath, (WIDTH >> 1) - (platforms[0].platform.width >> 1), (HEIGHT >> 1) - (platforms[0].platform.height >> 1));
            if (i == 5)
                createPlatform(&platforms[i], strPath, platforms[2].position.x, (HEIGHT >> 1) + (HEIGHT >> 3));
            if (i == 6)
                createPlatform(&platforms[i], strPath, platforms[3].position.x, platforms[5].position.y);
            if (i == 7)
                createPlatform(&platforms[i], strPath, platforms[0].position.x, HEIGHT - BASEHEIGHT - player->idle[0].height - platforms[0].platform.height);
            if (i == 8)
                createPlatform(&platforms[i], strPath, platforms[1].position.x, platforms[7].position.y);
            if (i == 9)
                createPlatform(&platforms[i], "./assets/sprites/base/grassBase1920.png", 0, HEIGHT - BASEHEIGHT);
            player->position = (Vector2) { (WIDTH >> 1) - player->drawTexture.width / 2, -16 - player->drawTexture.height };
        }   
    }
    return platforms;
}

void updatePlatforms(t_platform *platforms, Rectangle cameraRect) {
   
    for (int i = 0; i < 16; i++) {
         
        platforms[i].collision = (Rectangle) { platforms[i].position.x, platforms[i].position.y, platforms[i].platform.width, platforms[i].platform.height };
        if (CheckCollisionRecs(platforms[i].collision, cameraRect))
            platforms[i].isRendered = true;
        else
            platforms[i].isRendered = false;
    }
}

static void createMovingPlatform(t_movingPlatform *platform, int index, int positionX, int positionY, float velocity) {
    if (index < 8)
        platform->texture = LoadTexture("./assets/sprites/platforms/level0/rock480.png");
    else 
        platform->texture = LoadTexture("./assets/sprites/platforms/level0/rock.png");
    platform->position = (Vector2) { positionX, positionY };
    platform->isRendered = false;
    
    if (index == 3 || index == 4) {
        platform->velocity.x = 0;
        platform->velocity.y = velocity;
        platform->min = 384;
        platform->max = HEIGHT - BASEHEIGHT - platform->texture.height; //non il vero max ma il punto in cui sale a velocità 1 index 4
    }

    else if (index == 5 || index == 6 || index >= 8) {
        platform->velocity.x = 0;
        platform->velocity.y = velocity;
        platform->min = platform->position.y;
        platform->max = HEIGHT + 96;
    }
    
    else {
        platform->velocity.x = velocity;
        platform->velocity.y = 0;
        platform->min = platform->position.x;
        platform->max = platform->position.x + 224;
    }
}

t_movingPlatform *createMovingPlatforms(short numPlatforms) {
    t_movingPlatform *platforms = (t_movingPlatform *) MemAlloc(sizeof (t_movingPlatform) * numPlatforms);
    for (int i = 0; i < numPlatforms; i++) {
        if (i == 0) 
            createMovingPlatform(&platforms[i], i, 5344, HEIGHT - BASEHEIGHT - 128, 1.0f);
        if (i == 1) 
            createMovingPlatform(&platforms[i], i, platforms[0].position.x + 320, platforms[0].position.y - 92, 1.5f);
        if (i == 2) 
            createMovingPlatform(&platforms[i], i, platforms[1].position.x + 398, platforms[1].position.y - 92, 1.0f);
        if (i == 3) 
            createMovingPlatform(&platforms[i], i, platforms[2].max + platforms[2].texture.width + 64, HEIGHT - BASEHEIGHT - 192, 1.5f);
        if (i == 4)
            createMovingPlatform(&platforms[i], i, platforms[3].position.x + platforms[3].texture.width + 128, HEIGHT + 1, -20.0f);
        if (i == 5)
            createMovingPlatform(&platforms[i], i, platforms[4].position.x + platforms[4].texture.width + 64, HEIGHT >> 2, 0);
        if (i == 6)
            createMovingPlatform(&platforms[i], i, platforms[5].position.x + platforms[5].texture.width + 64, platforms[5].position.y + 96, 0);
        if (i == 7)
            createMovingPlatform(&platforms[i], i, platforms[6].position.x + platforms[6].texture.width, HEIGHT - BASEHEIGHT - 192, 1.5f);
        if (i == 8)
            createMovingPlatform(&platforms[i], i, platforms[7].max + platforms[7].texture.width + 64, platforms[7].position.y - 96, 0);
        if (i == 9)
            createMovingPlatform(&platforms[i], i, platforms[8].position.x + platforms[8].texture.width + 144, platforms[8].position.y - 96, 0);
        if (i == 10)
            createMovingPlatform(&platforms[i], i, platforms[9].position.x + platforms[9].texture.width + 144, platforms[9].position.y - 96, 0);
        if (i == 11)
            createMovingPlatform(&platforms[i], i, platforms[10].position.x + platforms[9].texture.width + 144, platforms[10].position.y, 0);
    }
    return platforms;
}

static void repositionMovingPlatforms(t_movingPlatform *platforms, int i) {
    if (i == 4) {
        platforms->isRendered = false;
        platforms[i].position.x = platforms[3].position.x + platforms[3].texture.width + 128;        
        platforms[i].position.y = HEIGHT + 1;
    }
    if (i == 5) {
        platforms[i].position.x = platforms[4].position.x + platforms[4].texture.width + 64;
        platforms[i].position.y = HEIGHT >> 2;
    }
    else if (i == 6) {
        platforms[i].position.x = platforms[5].position.x + platforms[5].texture.width + 64;
        platforms[i].position.y = platforms[5].position.y + 96;
    }
    else if (i == 8) {
        platforms[i].position.x = platforms[7].max + platforms[7].texture.width + 64;
        platforms[i].position.y = platforms[7].position.y - 96;
    }
    else if (i == 9) {
        platforms[i].position.x = platforms[8].position.x + platforms[8].texture.width + 144;
        platforms[i].position.y = platforms[8].position.y - 96;
    }
    else if (i == 10) {
        platforms[i].position.x = platforms[9].position.x + platforms[9].texture.width + 144;
        platforms[i].position.y = platforms[9].position.y - 96;
    }
    else if (i == 11) {
        platforms[i].position.x = platforms[10].position.x + platforms[10].texture.width + 144;
        platforms[i].position.y = platforms[10].position.y;
    }
    if (i == 4)
        platforms[i].velocity.y = -20.0f;
    else
        platforms[i].velocity.y = 0;
}


void updateMovingPlatforms(t_movingPlatform *platforms, t_player *player, t_rotatingPow *rotatingPows, Rectangle cameraRect, short numPlatforms) {


    for (int i = 0; i < numPlatforms; i++) {
        if (i == 4 && player->isDead) {
            repositionMovingPlatforms(platforms, i);
        }
        Rectangle platformCollision = { platforms[i].position.x, platforms[i].position.y, platforms[i].texture.width, platforms[i].texture.height };
        if (i != 4 && CheckCollisionRecs(platformCollision, cameraRect))
            platforms[i].isRendered = true;
        else
            platforms[i].isRendered = false;
        
        if (i == 4 && !platforms[i].isRendered && rotatingPows[1].taken)
            platforms[i].isRendered = true;
        
        if (i == 4 && platforms[i].isRendered) {
            if (platforms[i].position.y <= platforms[i].min)
                platforms[i].velocity.y = 0;
            else if (platforms[i].position.y <= platforms[i].max)
                platforms[i].velocity.y = -1.5f;
            platforms[i].position.y += platforms[i].velocity.y;
            continue;
        }

        else if (i == 3) {
            if (platforms[i].position.y > platforms[i].max)
                platforms[i].velocity.y *= -1;
            else if (platforms[i].position.y < platforms[i].min)
                platforms[i].velocity.y *= -1;
            platforms[i].position.y += platforms[i].velocity.y;
        }

        else if (i == 5 || i == 6 || i >= 8) {
            if (player->isDead) {
               repositionMovingPlatforms(platforms, i);
            }
            if (CheckCollisionRecs(player->collision, platformCollision)) {
                platforms[i].velocity.y = 1.0f;
                if (platforms[i].position.y > platforms[i].max)
                    platforms[i].velocity.y = 0;
            }
            platforms[i].position.y += platforms[i].velocity.y;
        }

        else {
            if (platforms[i].position.x > platforms[i].max)
                platforms[i].velocity.x *= -1;
            else if (platforms[i].position.x < platforms[i].min)
                platforms[i].velocity.x *= -1;
            platforms[i].position.x += platforms[i].velocity.x;
        }
    }
}