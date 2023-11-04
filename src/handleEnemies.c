#include "include/txaplat.h"

static void setEnemyPosition(t_enemy *enemy, t_platform *platform, int distance, bool begin) {
    if (begin)
        enemy->position.x = platform->position.x + distance;
    else
        enemy->position.x = platform->position.x + platform->platform.width - enemy->drawTexture.width - distance;
    
    enemy->position.y = platform->position.y - enemy->drawTexture.height;
    
    if (distance != 16)
        enemy->min = platform->platform.width - enemy->drawTexture.width - 481;
    else
        enemy->min = platform->position.x + distance;
    
    enemy->max = platform->position.x + platform->platform.width - enemy->drawTexture.width - 16;
    enemy->collision = (Rectangle) { enemy->position.x, enemy->position.y, enemy->drawTexture.width, enemy->drawTexture.height };
}

t_enemy *createEnemies(t_player *player, t_platform *platforms) {
    t_enemy *enemies;
    short numFrames;
    short index = 0;
    short totalEnemies = 0;
    short enemy1 = 0;
    short enemy2 = 0;
    
    if (player->level == 1) {
        totalEnemies = 19;
        enemy1 = 7;
        enemy2 = 5;
        numFrames = 2;
    }
    
    enemies = (t_enemy *) MemAlloc(sizeof (t_enemy) * totalEnemies);
   
    for (int i = 0; i < totalEnemies; i++) {
        enemies[i].isDead = false;
        enemies[i].isRendered = false;
        enemies[i].velocity.x = 1.0f;
        enemies[i].velocity.y = 0;
        enemies[i].currentFrame = 0;
        enemies[i].frameCounter = 0;
        enemies[i].timer = 0;
        if (player->level == 1) {
            enemies[i].enemy = (Texture2D *) MemAlloc(sizeof (Texture2D) * numFrames);
            if (i < enemy1) {
                enemies[i].enemy[0] = LoadTexture("./assets/sprites/enemy1/enemy1_0.png");
                enemies[i].enemy[1] = LoadTexture("./assets/sprites/enemy1/enemy1_1.png");
            }
            else if (i < enemy1 + enemy2) {
                enemies[i].enemy[0] = LoadTexture("./assets/sprites/enemy2/enemy2_0.png");
                enemies[i].enemy[1] = LoadTexture("./assets/sprites/enemy2/enemy2_1.png");
            }
            else {
                enemies[i].enemy[0] = LoadTexture("./assets/sprites/enemy3/enemy3_0.png");
                enemies[i].enemy[1] = LoadTexture("./assets/sprites/enemy3/enemy3_1.png");
            }
            enemies[i].drawTexture = enemies[i].enemy[0];
        }
    }
    setEnemyPosition(&enemies[index++], &platforms[2], 16, true);
    setEnemyPosition(&enemies[index++], &platforms[1], 16, true);
    setEnemyPosition(&enemies[index++], &platforms[3], 16, true);
    setEnemyPosition(&enemies[index++], &platforms[5], 16, true);
    setEnemyPosition(&enemies[index++], &platforms[0], platforms[0].platform.width - 480, true);
    setEnemyPosition(&enemies[index++], &platforms[6], 16, true);
    setEnemyPosition(&enemies[index++], &platforms[8], 16, false);
    setEnemyPosition(&enemies[index++], &platforms[4], 16, true);
    setEnemyPosition(&enemies[index++], &platforms[6], 16, false);
    setEnemyPosition(&enemies[index++], &platforms[7], 16, true);
    setEnemyPosition(&enemies[index++], &platforms[9], 16, true);
    setEnemyPosition(&enemies[index++], &platforms[8], 16, true);
    setEnemyPosition(&enemies[index++], &platforms[9], 16, false);
    setEnemyPosition(&enemies[index++], &platforms[4], 16, false);    
    setEnemyPosition(&enemies[index++], &platforms[10], 16, true);    
    setEnemyPosition(&enemies[index++], &platforms[7], 16, false);
    setEnemyPosition(&enemies[index++], &platforms[14], 16, true);
    enemies[index].position.x = platforms[14].position.x + (platforms[14].platform.width >> 1) - (enemies[5].drawTexture.width >> 1);
    enemies[index].position.y = platforms[14].position.y - enemies[index].drawTexture.height;
    enemies[index].min = platforms[14].position.x + 16;
    enemies[index].max = platforms[14].position.x + platforms[14].platform.width - enemies[index].drawTexture.width - 24;
    enemies[index].collision = (Rectangle) { enemies[index].position.x, enemies[index].position.y, enemies[index].drawTexture.width, enemies[index].drawTexture.height };
    index++;
    setEnemyPosition(&enemies[index++], &platforms[14], 16, false);
    index = 0;

    return enemies;
}

t_flyingEnemy *createFlyingEnemies(t_player *player) {
    
    t_flyingEnemy *enemies = NULL;
    short numEnemies = 0;
    short numFrames = 0;
    if (player->level == 1) {
        numEnemies = 3;
        numFrames = 2;
        enemies = (t_flyingEnemy *) MemAlloc(sizeof (t_flyingEnemy) * numEnemies);
        for (int i = 0; i < numEnemies; i++) {
            enemies[i].enemyLeft = (Texture2D *) MemAlloc(sizeof (Texture2D) * numFrames);
            enemies[i].enemyLeft[0] = LoadTexture("./assets/sprites/enemy4/enemy4_0.png");
            enemies[i].enemyLeft[1] = LoadTexture("./assets/sprites/enemy4/enemy4_1.png");
            enemies[i].noise = LoadSound("./assets/sounds/bbzzz.ogg");
            enemies[i].drawTexture = enemies[i].enemyLeft[0];
            enemies[i].isRendered = false;
            enemies[i].velocity.x = 3.0f;
            enemies[i].velocity.y = 0;
            enemies[i].currentFrame = 0;
            enemies[i].frameCounter = 0;
            enemies[i].timer = 0;
            enemies[i].min = 16;
            enemies[i].max = LEVELWIDTH - enemies[i].drawTexture.width;
            enemies[i].bomb.bomb = LoadTexture("./assets/sprites/enemy4/sphere.png");
            enemies[i].bomb.splat = LoadSound("./assets/sounds/splat.ogg");
            enemies[i].bomb.drop = LoadSound("./assets/sounds/drop.ogg");
            enemies[i].bomb.isActive = false;
            enemies[i].bomb.isRendered = false;
            enemies[i].bomb.velocity.x = 0;
            enemies[i].bomb.velocity.y = 0;
            if (i == 0)
                enemies[i].position = (Vector2) { (LEVELWIDTH >> 1) - enemies[i].drawTexture.width, enemies[i].drawTexture.height + 32 };
            else if (i == 1)
                enemies[i].position = (Vector2) { enemies[0].position.x + 640, enemies[0].position.y + enemies[0].drawTexture.height + 8 };    
            else
                enemies[i].position = (Vector2) { enemies[1].position.x + 640, enemies[1].position.y + enemies[1].drawTexture.height + 8 };
            enemies[i].collision = (Rectangle) { enemies[i].position.x, enemies[i].position.y, enemies[i].drawTexture.width, enemies[i].drawTexture.height };
        }
    }

    return enemies;
}

static void enemyHittedByBowlingBall(t_player *player, t_enemy *enemy, t_movingPow *bowlingBall) {
    if (enemy->isDead)
        return;
    Rectangle bowlingBallCollision = { bowlingBall->position.x, bowlingBall->position.y - bowlingBall->pow.height/* - bowlingBall->pow.height aggiunto per farlo andare ma strano*/, bowlingBall->pow.width, bowlingBall->pow.height };

    if (bowlingBall->active && CheckCollisionRecs(bowlingBallCollision, enemy->collision)) {
        enemy->isDead = true;
        bowlingBall->active = false;
        player->score += 150;
        PlaySound(player->hit1);
    }
}

void updateEnemies(t_enemy *enemies, t_movingPow *bowlingBall, t_player *player, Rectangle cameraRect) {
    short numFrames = 0;
    short refreshFrame;
    short totalEnemies = 0;
    
    if (player->level == 1) {
        totalEnemies = 19;
        numFrames = 2;
        refreshFrame = 24;
    }

    for (int i = 0; i < totalEnemies; i++) {
        if (enemies[i].isDead)
            continue;
        
        enemies[i].collision = (Rectangle) { enemies[i].position.x, enemies[i].position.y, enemies[i].drawTexture.width, enemies[i].drawTexture.height };

        if (CheckCollisionRecs(enemies[i].collision, cameraRect))
            enemies[i].isRendered = true;
        else
            enemies[i].isRendered = false;
        
        handleMovement(&enemies[i].currentFrame, &enemies[i].frameCounter, refreshFrame, numFrames);
        
        for(int j = 0; j < totalEnemies; j++)
            if (i != j && !enemies[j].isDead && CheckCollisionRecs(enemies[i].collision, enemies[j].collision))
                enemies[i].velocity.x *= -1.0f;

        if (enemies[i].position.x > enemies[i].max || enemies[i].position.x < enemies[i].min)
            enemies[i].velocity.x *= -1.0f;

        enemies[i].position.x += enemies[i].velocity.x;
        enemies[i].drawTexture = enemies[i].enemy[enemies[i].currentFrame];
        handlePlayerCollision(&enemies[i], player);
        enemyHittedByBowlingBall(player, &enemies[i], bowlingBall);
    }

    if (player->isEnemySquashed) {
        player->velocity.y = -8;
        player->isEnemySquashed = false;
    }
}

static void handleBombCollision(t_flyingEnemy *enemy) {
    enemy->bomb.velocity.y = 0;
    enemy->bomb.isActive = false;
    enemy->timer = 0;
    enemy->bomb.position = (Vector2) { 0, 0 };
    if (enemy->bomb.isRendered)
        PlaySound(enemy->bomb.splat);
}

static void updateBomb(t_flyingEnemy *enemy, t_platform *platforms, t_movingPlatform *movingPlatforms, t_player *player, Rectangle cameraRect) {
    
    Rectangle bombCollision = { enemy->bomb.position.x, enemy->bomb.position.y, enemy->bomb.bomb.width, enemy->bomb.bomb.height };
    
    if (CheckCollisionRecs(bombCollision, cameraRect))
        enemy->bomb.isRendered = true;
    else
        enemy->bomb.isRendered = false;
    
    for (int i = 0; i < 16; i++) {  
        if (CheckCollisionRecs(bombCollision, platforms[i].collision)) {
            handleBombCollision(enemy);
            return;
        }
    }

    for (int i = 0; i < 7; i++) {    
        Rectangle movingPlatformCollision = { movingPlatforms[i].position.x, movingPlatforms[i].position.y, movingPlatforms[i].texture.width, movingPlatforms[i].texture.height };
        if (CheckCollisionRecs(bombCollision, movingPlatformCollision)) {
            handleBombCollision(enemy);
            return;
        }
    }

    //gestisce collisione con il mare
    if (enemy->bomb.position.y + enemy->bomb.bomb.height > LEVELHEIGHT - BASEHEIGHT) {
        handleBombCollision(enemy);
        return;
    }

    if (CheckCollisionRecs(bombCollision, player->collision)) {
        handleBombCollision(enemy);
        playerDeath(player);
        return;
    }
    enemy->bomb.velocity.y = 3.0f;
    enemy->bomb.position.y += enemy->bomb.velocity.y;
}

void updateFlyingEnemies(t_flyingEnemy *enemies, t_player *player, t_platform *platforms, t_movingPlatform *movingPlatforms, Rectangle cameraRect) {

    if (player->level != 1)
        return;

    short numEnemies = 3;
    short numFrames = 2;

    for (int i = 0; i < numEnemies; i++) {
        enemies[i].collision = (Rectangle) { enemies[i].position.x, enemies[i].position.y, enemies[i].drawTexture.width, enemies[i].drawTexture.height };

        if (CheckCollisionRecs(enemies[i].collision, cameraRect))
            enemies[i].isRendered = true;
        else
            enemies[i].isRendered = false;

        if (CheckCollisionRecs(enemies[i].collision, player->collision))
            playerDeath(player);

        handleMovement(&enemies[i].currentFrame, &enemies[i].frameCounter, 16, numFrames);
        
        if (enemies[i].position.x > enemies[i].max || enemies[i].position.x < enemies[i].min)
            enemies[i].velocity.x *= -1.0f;
            
        enemies[i].position.x += enemies[i].velocity.x;
        enemies[i].drawTexture = enemies[i].enemyLeft[enemies[i].currentFrame];
        
        if (enemies[i].isRendered) {
            if (!IsSoundPlaying(enemies[i].noise)) {
                SetSoundVolume(enemies[i].noise, 0.5f);
                PlaySound(enemies[i].noise);
            }
            enemies[i].timer += GetFrameTime();
            if (enemies[i].timer >= 2.0 && !enemies[i].bomb.isActive) {
                enemies[i].bomb.isActive = true;
                enemies[i].bomb.position.x = enemies[i].drawTexture.width / 2 - enemies[i].bomb.bomb.width / 2 + enemies[i].position.x;
                enemies[i].bomb.position.y = enemies[i].drawTexture.height + enemies[i].position.y;
                enemies[i].timer = 0;
                PlaySound(enemies[i].bomb.drop);
            }
        }
        else
            StopSound(enemies[i].noise);
        if (enemies[i].bomb.isActive)
            updateBomb(&enemies[i], platforms, movingPlatforms, player, cameraRect);
    }
}
