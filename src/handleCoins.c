#include "include/txaplat.h"

static void coinsOnPlatform(t_coin *coins, t_platform *platform, t_movingPlatform *mov_platform, t_player *player, int *coinIndex, int pixel, int total) {
    
    if (player->level == 1) {
        if (*coinIndex == 18) {
            for (int i = 0; i < total; i++) {
                coins[*coinIndex].position.x = mov_platform->min + pixel;
                coins[*coinIndex].position.y = mov_platform->position.y - 128;
                coins[*coinIndex].collision = (Rectangle) { coins[*coinIndex].position.x, coins[*coinIndex].position.y, coins[*coinIndex].drawTexture.width, coins[*coinIndex].drawTexture.height };
                pixel += 48;
                *coinIndex = *coinIndex + 1;    
            }
            return; 
        }
        else if (*coinIndex == 21) {
            for (int i = 0; i < total; i++) {
                coins[*coinIndex].position.x = mov_platform->min + 96 /*(mov_platform->texture.width >> 1)  - (coins[*coinIndex].coin[0].width >> 1) */;
                coins[*coinIndex].position.y = mov_platform->position.y - pixel;
                coins[*coinIndex].collision = (Rectangle) { coins[*coinIndex].position.x, coins[*coinIndex].position.y, coins[*coinIndex].drawTexture.width, coins[*coinIndex].drawTexture.height };
                pixel += coins[*coinIndex].coin[0].height + 16;
                *coinIndex = *coinIndex + 1;    
            }
            return;
        }
    }
    float coinPosition = player->idle[0].height / 2 + coins[0].coin[0].height / 2;
    for (int i = 0; i < total; i++) {
        coins[*coinIndex].position.x = platform->position.x + pixel;
        coins[*coinIndex].position.y = platform->position.y - coinPosition;
        coins[*coinIndex].collision = (Rectangle) { coins[*coinIndex].position.x, coins[*coinIndex].position.y, coins[*coinIndex].drawTexture.width, coins[*coinIndex].drawTexture.height };
        pixel += 48;
        *coinIndex = *coinIndex + 1;    
    }
}

t_coin *createCoins(t_platform *platforms, t_movingPlatform *mov_platforms, t_player *player, short numCoins) {
    
    t_coin *coins = (t_coin *) MemAlloc(sizeof (t_coin) * numCoins);
    int coinIndex = 0;

    for (int i = 0; i < numCoins; i++) {
        coins[i].coin[0] = LoadTexture("./assets/sprites/coin/coin0.png");
        coins[i].coin[1] = LoadTexture("./assets/sprites/coin/coin1.png");
        coins[i].coin[2] = LoadTexture("./assets/sprites/coin/coin2.png");
        coins[i].coin[3] = LoadTexture("./assets/sprites/coin/coin3.png");
        coins[i].coin[4] = LoadTexture("./assets/sprites/coin/coin4.png");
        coins[i].taken = false;
        coins[i].isRendered = false;
        coins[i].currentFrame = 0;
        coins[i].frameCounter = 0;
        coins[i].drawTexture = coins[i].coin[0];
    }
    
    short coinWidth = coins[0].coin[0].width;
    if (player->level == 1) {
        coinsOnPlatform(coins, &platforms[1], NULL, player, &coinIndex, (platforms[1].platform.width >> 1) - 8 - coinWidth, 2); //centra 2 coins sulla piattaforma
        coinsOnPlatform(coins, &platforms[3], NULL, player, &coinIndex, (platforms[3].platform.width >> 1) - 8 - coinWidth, 2);
        coinsOnPlatform(coins, &platforms[0], NULL, player, &coinIndex, 4608, 4);
        coinsOnPlatform(coins, &platforms[4], NULL, player, &coinIndex, 272, 2);
        coinsOnPlatform(coins, &platforms[6], NULL, player, &coinIndex, (platforms[6].platform.width >> 1) - 8 - coinWidth, 2);
        coinsOnPlatform(coins, &platforms[7], NULL, player, &coinIndex, (platforms[7].platform.width >> 1) - 8 - coinWidth - (coinWidth >> 1), 3); //centra 3 coins sulla piattaforma
        coinsOnPlatform(coins, &platforms[8], NULL, player, &coinIndex, (platforms[8].platform.width >> 1) - 8 - coinWidth - (coinWidth >> 1), 3);
        coinsOnPlatform(coins, NULL, &mov_platforms[1], player, &coinIndex, 124, 3);
        coinsOnPlatform(coins, NULL, &mov_platforms[7], player, &coinIndex, 64, 3);
    }

    else if (player->level == 1.1f)
        for (int i = 0; i < 9; i++)
            if (i != 4)
                coinsOnPlatform(coins, &platforms[i], NULL, player, &coinIndex, (platforms[0].platform.width >> 1) - 8 - coinWidth - (coinWidth >> 1), 3);
    
    return coins;
}

static void coinIsTaken(t_player *player, t_coin *coin) {
    coin->taken = true;
    PlaySound(player->coin);
    player->score += 100;
    player->coinsTaken++;
    if (player->coinsTaken == 100) {
        player->coinsTaken = 0;
        player->lives++;
    }
}

void updateCoins(t_player *player, t_coin *coins, short numCoins, Rectangle cameraRect) {
    
    for (int i = 0; i < numCoins; i++) {
         if (coins[i].taken)
            continue;
        
        coins[i].collision = (Rectangle) { coins[i].position.x, coins[i].position.y, coins[i].drawTexture.width, coins[i].drawTexture.height };
        
        if (CheckCollisionRecs(coins[i].collision, cameraRect))
            coins[i].isRendered = true;
        else
            coins[i].isRendered = false;

        if (CheckCollisionRecs(player->collision, coins[i].collision))
            coinIsTaken(player, &coins[i]);

        if (!coins[i].taken) {
            handleMovement(&coins[i].currentFrame, &coins[i].frameCounter, 12, 5);
            coins[i].drawTexture = coins[i].coin[coins[i].currentFrame];
        }
    }
}
