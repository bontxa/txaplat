#include "include/txaplat.h"

void createPlayer(t_player *player) {
    player->idle[0] = LoadTexture("./assets/sprites/player/idleRight.png");
    player->idle[1] = LoadTexture("./assets/sprites/player/idleLeft.png");
    player->jump[0] = LoadTexture("./assets/sprites/player/jumpRight.png");
    player->jump[1] = LoadTexture("./assets/sprites/player/jumpLeft.png");
    player->runRight[0] = LoadTexture("./assets/sprites/player/runRight0.png");
    player->runRight[1] = LoadTexture("./assets/sprites/player/runRight1.png");
    player->runRight[2] = LoadTexture("./assets/sprites/player/runRight2.png");
    player->runRight[3] = LoadTexture("./assets/sprites/player/runRight3.png");
    player->runLeft[0] = LoadTexture("./assets/sprites/player/runLeft0.png");
    player->runLeft[1] = LoadTexture("./assets/sprites/player/runLeft1.png");
    player->runLeft[2] = LoadTexture("./assets/sprites/player/runLeft2.png");
    player->runLeft[3] = LoadTexture("./assets/sprites/player/runLeft3.png");
    player->death = LoadTexture("./assets/sprites/player/dead.png");
    player->enemyDeath = LoadTexture("./assets/sprites/player/skull.png");
    player->coin = LoadSound("./assets/sounds/getCoin.ogg");
    player->walking = LoadSound("./assets/sounds/walk.ogg");
    player->jumping = LoadSound("./assets/sounds/jump.ogg");
    player->pow = LoadSound("./assets/sounds/powTaken.ogg");
    player->hit1 = LoadSound("./assets/sounds/squash.ogg");
    player->playerDeath = LoadSound("./assets/sounds/playerDeath.ogg");
    player->launchBowlingBall = LoadSound("./assets/sounds/rolling.ogg");
    player->drawTexture = player->idle[0];
    player->velocity = (Vector2) { 0, 0 };
    player->position = (Vector2) { 240, -16 - player->drawTexture.height };
    player->positionResume = (Vector2) { player->position.x, player->position.y };
    player->collision = (Rectangle) { player->position.x, player->position.y, player->drawTexture.width, player->drawTexture.height };
    player->isFacingLeft = false;
    player->isMoving = false;
    player->isJumping = false;
    player->isDead = false;
    player->isResumed = false;
    player->isLevelCreated = false;
    player->isEnemySquashed = false;
    player->isLevelRestarted = false;
    player->score = 0;
    player->currentFrame = 0;
    player->frameCounter = 0;
    player->lives = 3;
    player->limit = 0;
    player->level = 0;
    player->coinsTaken = 0;
    player->shots = 0;
}

void playerDeath(t_player *player) {
    if (player->isDead)
        return;
    player->isDead = true;
    player->lives--;
    player->velocity.y = -PLAYER_JUMP_FORCE;
    player->drawTexture = player->death;
    PlaySound(player->playerDeath);
}

static void enemySquash(t_player *player, t_enemy *enemy) {
    enemy->isDead = true;
    player->isEnemySquashed = true;
    player->score += 150;
    PlaySound(player->hit1);
}

void handlePlayerCollision(t_enemy *enemy, t_player *player) {
    if (enemy->isDead || player->isDead)
        return;
    float gravityUnit = GRAVITY / 60.0f;
    if (CheckCollisionRecs(player->collision, enemy->collision)) {
        if (player->velocity.y > gravityUnit)
            enemySquash(player, enemy);
        else
            playerDeath(player);
    }
}

static void moveOnMovingPlatform(t_player *player, t_movingPlatform *platforms) {
    short totalPlatforms;
    if (player->level == 1)
        totalPlatforms = 12;

    for (int i = 0; i < totalPlatforms; i++) {
        if (player->level == 1 && !platforms[i].isRendered)
            continue;
        Rectangle movingPlatformCollision = { platforms[i].position.x, platforms[i].position.y, platforms[i].texture.width, platforms[i].texture.height };
        if (CheckCollisionRecs(player->collision, movingPlatformCollision)) {
            if (player->velocity.y > 0 && player->position.y < platforms[i].position.y ) {
                player->position.y = platforms[i].position.y - player->drawTexture.height;
                player->velocity.y = 0;
                player->isJumping = false;
                if (i != 3 && i != 4)
                    player->velocity.x += platforms[i].velocity.x * 2;
                else
                    player->velocity.y += platforms[i].velocity.y; 
            }
            else if (player->velocity.y < 0 && player->position.y > platforms[i].position.y) {
                player->position.y = platforms[i].position.y + platforms[i].texture.height;
                player->velocity.y = 0;
            }
        }
    }
}

static void moveOnPlatform(t_player *player, t_platform *platforms) {
    float gravityUnit = GRAVITY / 60.0f;
    short totalPlatforms;
    if (player->level == 1)
        totalPlatforms = 16;
    else if (player->level == 1.1f)
        totalPlatforms = 10;

    for (int i = 0; i < totalPlatforms; i++) {
        if (player->level == 1 && !platforms[i].isRendered)
            continue;
        Rectangle platformCollision = { platforms[i].position.x, platforms[i].position.y, platforms[i].platform.width, platforms[i].platform.height };
        if (CheckCollisionRecs(player->collision, platformCollision)) {
            if (player->velocity.y > gravityUnit && player->position.y < platforms[i].position.y) {
                player->position.y = platforms[i].position.y - player->drawTexture.height;
                player->velocity.y = 0;
                player->isJumping = false;
            }
            else if (player->velocity.y < 0 && player->position.y > platforms[i].position.y) {
                player->position.y = platforms[i].position.y + platforms[i].platform.height;
                player->velocity.y = 0;
            }
            else if ((!player->isFacingLeft && player->position.x < platforms[i].position.x) || (player->isFacingLeft && player->position.x > platforms[i].position.x))
                player->velocity.x = 0;
        }
    }
}


static void movePlayer(t_player *player) {

    if (IsKeyDown(KEY_LEFT)) {
        player->isFacingLeft = true;
        player->isMoving = true;
        player->velocity.x = -3.5f;
        if (!player->isJumping)
            player->drawTexture = player->runLeft[player->currentFrame];
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        player->isFacingLeft = false;
        player->isMoving = true;
        player->velocity.x = +3.5f;

        if (!player->isJumping)
            player->drawTexture = player->runRight[player->currentFrame];
    }
    else {
        player->isMoving = false;
        player->velocity.x = 0;
    }

    if (IsKeyPressed(KEY_UP) && !player->isJumping) {
        player->velocity.y = -PLAYER_JUMP_FORCE;
        player->isJumping = true;
        PlaySound(player->jumping);
        if (player->isFacingLeft)
            player->drawTexture = player->jump[1];
        else
            player->drawTexture = player->jump[0];
    }
}

void updatePlayer(t_player *player, t_platform *platforms, t_movingPlatform *movingPlatforms, Camera2D *camera) {

    player->collision = (Rectangle) { player->position.x, player->position.y, player->drawTexture.width, player->drawTexture.height }; 
    float gravityUnit = GRAVITY / 60.0f;
    player->velocity.y += gravityUnit;
    
    if(player->isDead) {
        player->drawTexture = player->death;
        player->position.y += player->velocity.y;
        player->velocity.x = 0;
        if (player->position.y > HEIGHT) {
            player->limit = 0;
            player->velocity = (Vector2) { 0, 0 };
            player->position = (Vector2) { player->positionResume.x, player->positionResume.y };
            player->isDead = false;
            player->isResumed = true;
            if (player->lives == 0) {
                player->level = 1.11f;
                player->isLevelCreated = false;
            }
        }
        return;
    }

    movePlayer(player);
    moveOnPlatform(player, platforms);
    if (movingPlatforms != NULL)
        moveOnMovingPlatform(player, movingPlatforms);
    
    if (player->level == 1) {
        player->limit = camera->target.x - WIDTH / 2;
        if (player->position.x > 3852)
            player->positionResume = (Vector2) { 3852, HEIGHT - BASEHEIGHT - player->drawTexture.height };
    }
    else if (player->level == 1.1f)
        player->limit = 0;
    
    if (player->isMoving) {
        handleMovement(&player->currentFrame, &player->frameCounter, 4, 4);
        if (!player->isJumping && player->currentFrame == 1)
            PlaySound(player->walking);
    }

    if (!player->isMoving && !player->isJumping) {
        if (player->isFacingLeft)
            player->drawTexture = player->idle[1];
        else
            player->drawTexture = player->idle[0];
    }
    
    if (player->position.y > HEIGHT)
        playerDeath(player);
    
    
    else {
        player->position.y += player->velocity.y;
        player->position.x += player->velocity.x;
    
        if (player->position.x <= player->limit)
            player->position.x = player->limit; 
        else if (player->position.x + player->idle[0].width >= LEVELWIDTH)
            player->position.x = LEVELWIDTH - player->idle[0].width;
    }   
}
