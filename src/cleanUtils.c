#include "include/txaplat.h"

void clearPlayer(t_player *player) {
    for(int i = 0; i < 2; i++) {
        UnloadTexture(player->idle[i]);
        UnloadTexture(player->jump[i]);
    }
    for(int i = 0; i < 4; i++) {
        UnloadTexture(player->runRight[i]);
        UnloadTexture(player->runLeft[i]);
    }
    UnloadTexture(player->death);
    UnloadTexture(player->enemyDeath);

    UnloadSound(player->walking);
    UnloadSound(player->jumping);
    UnloadSound(player->coin);
    UnloadSound(player->pow);
    UnloadSound(player->launchBowlingBall);
    UnloadSound(player->hit1);
    UnloadSound(player->playerDeath);
}

void clearPlatforms(t_platform *platforms, short numPlatforms, t_movingPlatform *movingPlatforms, short numMovingPlatforms) {
    if (platforms == NULL)
        return;
    for (int i = 0; i < numPlatforms; i++)
        UnloadTexture(platforms[i].platform);
    MemFree(platforms);
    
    if (movingPlatforms == NULL)
        return;
    for (int i = 0; i < numMovingPlatforms; i++)
        UnloadTexture(movingPlatforms[i].texture);
    MemFree(movingPlatforms);    
}

void clearCoins(t_coin *coins, short numCoins) {
    if (coins == NULL)
        return;
    for (int i = 0; i < numCoins; i++) {
        for (int j = 0; j < 5; j++)
            UnloadTexture(coins[i].coin[j]);            
    }
    MemFree(coins);
}

static void clearEnemies(t_enemy *enemies, short numEnemies) {
    short numFrames = 2;
    for (int i = 0; i < numEnemies; i++) {
        for (int j = 0; j < numFrames; j++)
            UnloadTexture(enemies[i].enemy[j]);
        MemFree(enemies[i].enemy);
    }
    MemFree(enemies);
}

static void clearFlyingEnemies(t_flyingEnemy *enemies, short numEnemies) {
    short numFrames = 2;
    for (int i = 0; i < numEnemies; i++) { 
        for (int j = 0; j < numFrames; j++)
            UnloadTexture(enemies[i].enemyLeft[j]);
        UnloadSound(enemies[i].noise);
        UnloadTexture(enemies[i].bomb.bomb);
        UnloadSound(enemies[i].bomb.splat);
        UnloadSound(enemies[i].bomb.drop);
        MemFree(enemies[i].enemyLeft);
    }
    MemFree(enemies);
}

void clearLevel1(t_coin *coins, t_platform *platforms, t_movingPlatform *movingPlatforms, t_enemy *enemies, t_flyingEnemy *enemies4, t_rotatingPow *rotatingPows, t_movingPow *bowlingBall, t_background *background) {
    
    clearCoins(coins, 24);
    clearEnemies(enemies, 19);
    clearFlyingEnemies(enemies4, 3);
    clearPlatforms(platforms, 16, movingPlatforms, 12);
    UnloadTexture(bowlingBall->pow);

    for (int i = 0; i < 4; i++)
        UnloadTexture(rotatingPows[i].pow);
    MemFree(rotatingPows);

    for(int i = 0; i < 21; i++)
        UnloadTexture(background[i].background);
    MemFree(background);

}

void clearLevel1_1(t_platform *platforms, t_coin *coins) {
    clearPlatforms(platforms, 10, NULL, 0);
    clearCoins(coins, 24);
}
