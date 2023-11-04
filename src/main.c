#include "include/txaplat.h"
#include "include/getScreenResolution.h"

int main() {

    int screenResolution = getScreenResolution();
    if (screenResolution == 2)
        return 1;
    else if (screenResolution == 1) {
        lowScreenResolution();
        return 1;
    }

    int highScore = 0;
    if (!loadHighScore(&highScore))
        return 1;
    
    InitWindow(WIDTH, HEIGHT, "txaplat - Demo 0.1");
    InitAudioDevice();
    
    Font mainFont = LoadFont("./assets/fonts/8-bit-hud/8-bit-hud.ttf");
    Camera2D camera;
    t_background *background;
    t_player player;
    t_platform *platforms;
    t_movingPlatform *movingPlatforms;
    t_coin *coins;
    t_movingPow bowlingBall;
    t_enemy *enemies;
    t_flyingEnemy *flyingEnemies;
    t_rotatingPow *rotatingPows;
    Sound music = LoadSound("./assets/sounds/DarxieLand.mp3");

    t_splashScreen splashScreen;

    short numBackground = 21;
    short numPlatforms = 16;
    short numMovingPlatforms = 12;
    short numCoins = 24;

    createPlayer(&player);
    createCamera(&camera);
    
    bool isPaused = false;
    static double timer = 0;

    HideCursor();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        
        Rectangle cameraRect = {
            camera.target.x - (GetScreenWidth() / 2),
            camera.target.y - (GetScreenHeight() / 2),
            GetScreenWidth(),
            GetScreenHeight()
        };

        if (pauseGame(&isPaused, &player, mainFont))
            continue;

        if (player.level == 0)
            welcomeScreen(&player, &splashScreen, &music);

        else if (player.level == 0.1f)
            creditScreen(&player, mainFont);

        else if (player.level == 1) {
            if (!player.isLevelCreated) {

                if (player.isLevelRestarted) {
                    platforms = createPlatforms(&player, numPlatforms);
                    coins = createCoins(platforms, movingPlatforms, &player, numCoins);
                    movingPlatforms[4].position.x = 0;
                    movingPlatforms[4].position.y = HEIGHT + 96;
                    movingPlatforms[4].velocity.x = 0;
                   /*  movingPlatforms[5].position.x = 0;
                    movingPlatforms[5].position.y = HEIGHT + 96;
                    movingPlatforms[5].velocity.x = 0;
                    movingPlatforms[6].position.x = 0;
                    movingPlatforms[6].position.y = HEIGHT + 96;
                    movingPlatforms[6].velocity.x = 0; */
                    rotatingPows[2].taken = true;
                    player.position.x = rotatingPows[2].position.x;
                    player.position.y = rotatingPows[2].position.y - player.idle[0].height;
                    player.isLevelRestarted = false;
                }
                else {
                    background = createBackground(&player, numBackground);
                    platforms = createPlatforms(&player, numPlatforms);
                    movingPlatforms = createMovingPlatforms(numMovingPlatforms);
                    coins = createCoins(platforms, movingPlatforms, &player, numCoins);
                    createBowlingBall(&bowlingBall, &player);
                    enemies = createEnemies(&player, platforms);
                    flyingEnemies = createFlyingEnemies(&player);
                    rotatingPows = createRotatingPows(platforms, movingPlatforms, player.idle[0].height);
                }
                player.isLevelCreated = true;
            }

            if (!IsSoundPlaying(music)) {
                SetSoundVolume(music, 0.2f);
                PlaySound(music);
            }

            updateBackground(background, cameraRect, numBackground);
            updatePlayer(&player, platforms, movingPlatforms, &camera);
            updateEnemies(enemies, &bowlingBall, &player, cameraRect);
            updateCoins(&player, coins, numCoins, cameraRect);
            updateRotatingPows(&player, rotatingPows, cameraRect);
            updateBowlingBall(&player, &bowlingBall, platforms, rotatingPows);
            updateFlyingEnemies(flyingEnemies, &player, platforms, movingPlatforms, cameraRect);
            updatePlatforms(platforms, cameraRect);
            updateMovingPlatforms(movingPlatforms, &player, rotatingPows, cameraRect, numMovingPlatforms);
            updateCamera(&camera, &player);
            
            BeginDrawing();
            BeginMode2D(camera); 
            ClearBackground((Color){ 177, 226, 238, 255 });
            for (int i = 0; i < 10; i++)
                if (background[i].isRendered)
                    DrawTexture(background[i].background, background[i].position.x, background[i].position.y, WHITE);

            if (!player.isDead)
                DrawTexture(player.drawTexture, player.position.x, player.position.y, WHITE);
                
            for (int i = 0; i < 16; i++)
                if (platforms[i].isRendered)
                    DrawTexture(platforms[i].platform, platforms[i].position.x, platforms[i].position.y, WHITE);

            for (int i = 0; i < numMovingPlatforms; i++)
                if (movingPlatforms[i].isRendered)
                    DrawTexture(movingPlatforms[i].texture, movingPlatforms[i].position.x, movingPlatforms[i].position.y, WHITE);
            
            for (int i = 10; i < numBackground; i++)
                if (background[i].isRendered)
                    DrawTexture(background[i].background, background[i].position.x, background[i].position.y, WHITE);

            for (int i = 0; i < numCoins; i++)
                if (!coins[i].taken && coins[i].isRendered)
                    DrawTexture(coins[i].drawTexture, coins[i].position.x, coins[i].position.y, WHITE);
            
            if (bowlingBall.active)
                DrawTexturePro(bowlingBall.pow, (Rectangle){0, 0, bowlingBall.pow.width, bowlingBall.pow.height},
                  (Rectangle){bowlingBall.position.x - bowlingBall.origin.x, bowlingBall.position.y - bowlingBall.origin.y,
                              bowlingBall.pow.width, bowlingBall.pow.height},
                   bowlingBall.origin, bowlingBall.rotationAngle, WHITE);
            
            for (int i = 0; i < 19; i++)
                if (!enemies[i].isDead && enemies[i].isRendered)
                    DrawTexture(enemies[i].drawTexture, enemies[i].position.x, enemies[i].position.y, WHITE);
                else if (enemies[i].isDead && enemies[i].isRendered) {
                    enemies[i].timer += GetFrameTime();
                    if (enemies[i].timer < 0.2f)
                        DrawTexture(player.enemyDeath, enemies[i].position.x, enemies[i].position.y, WHITE);
                }

            for (int i = 0; i < 3; i++) {
                if (flyingEnemies[i].isRendered)
                    DrawTexture(flyingEnemies[i].drawTexture, flyingEnemies[i].position.x, flyingEnemies[i].position.y, WHITE);
                if(flyingEnemies[i].bomb.isRendered && flyingEnemies[i].bomb.isActive)
                    DrawTexture(flyingEnemies[i].bomb.bomb, flyingEnemies[i].bomb.position.x, flyingEnemies[i].bomb.position.y, WHITE);
            }

            for (int i = 0; i < 4; i++)
            if (!rotatingPows[i].taken && rotatingPows[i].isRendered)
                DrawTexturePro(rotatingPows[i].pow, (Rectangle){0, 0, rotatingPows[i].pow.width, rotatingPows[i].pow.height}, 
                       (Rectangle){rotatingPows[i].position.x, rotatingPows[i].position.y, rotatingPows[i].pow.width, rotatingPows[i].pow.height}, 
                        rotatingPows[i].origin, rotatingPows[i].rotationAngle, WHITE);

            if(player.isDead)
                DrawTexture(player.drawTexture, player.position.x, player.position.y, WHITE);

            EndMode2D();

            DrawTextEx(mainFont, "PLAYER 1", (Vector2){ 10, 10 }, MAINFONT, 1, RED);
            printHighscore(highScore, mainFont);
            printScore(&player, mainFont);
            printLives(&player, mainFont);
            printTotalCoins(&player, mainFont);
            printTotalShots(&player, mainFont);
            
            EndDrawing();
        }

        else if (player.level == 1.01f) {
            if (!player.isLevelCreated) {
                clearPlatforms(platforms, 16, NULL, 0);
                clearCoins(coins, numCoins);
                UnloadSound(music);
                music = LoadSound("./assets/sounds/Bet You Can ver 2.mp3");
                SetSoundVolume(music, 0.2f);
                PlaySound(music);
                splashScreen.splashScreen = LoadTexture("./assets/sprites/splash/runScreen.png");
                splashScreen.position = (Vector2){ 0, 0 };
                player.isLevelCreated = true;
            }
            runScreen(&player, &splashScreen, mainFont);
        }

        else if (player.level == 1.1f) {
            if (!player.isLevelCreated) {
                timer = 20;
                createCamera(&camera);
                numPlatforms = 10;
                numCoins = 24;
                platforms = createPlatforms(&player, numPlatforms);
                coins = createCoins(platforms, movingPlatforms, &player, numCoins);
                splashScreen.splashScreen = LoadTexture("./assets/sprites/splash/nightScreen.png");
                splashScreen.position = (Vector2){ 0, 0 };
                player.isLevelCreated = true;
            }

            updatePlayer(&player, platforms, NULL, &camera);
            updateCoins(&player, coins, numCoins, cameraRect);
            BeginDrawing();
            BeginMode2D(camera); 
            ClearBackground((Color){ 15, 11, 63, 255 });

            DrawTexture(splashScreen.splashScreen, splashScreen.position.x, splashScreen.position.y, WHITE);
            
            DrawTexture(player.drawTexture, player.position.x, player.position.y, WHITE);
            for (int i = 0; i < numPlatforms; i++)
                DrawTexture(platforms[i].platform, platforms[i].position.x, platforms[i].position.y, WHITE);
        
            for (int i = 0; i < numCoins; i++)
                if (!coins[i].taken  && coins[i].isRendered)
                    DrawTexture(coins[i].drawTexture, coins[i].position.x, coins[i].position.y, WHITE);
            
            DrawTextEx(mainFont, "PLAYER 1", (Vector2){ 10, 10 }, MAINFONT, 1, RED);
            printTime(mainFont, timer);
            printScore(&player, mainFont);
            printLives(&player, mainFont);
            printTotalCoins(&player, mainFont);
            printTotalShots(&player, mainFont);

            EndMode2D();
            EndDrawing();
            timer -= GetFrameTime();
            if (timer < 0) {
                clearLevel1_1(platforms, coins);
                UnloadTexture(splashScreen.splashScreen);
                player.level = 1;
                player.isLevelCreated = false;
                player.isLevelRestarted = true;
                player.isResumed = true;
                numPlatforms = 16;
                numCoins = 24;
                UnloadSound(music);
                music = LoadSound("./assets/sounds/DarxieLand.mp3");
            }
        }

        else if (player.level == 1.11f) {
            createDemoEnd(mainFont);
            if(!uploadHighScore(&player.score, &highScore))
                return 1; 
            if (!loadHighScore(&highScore))
                return 1;
            if(IsKeyPressed(KEY_ENTER)) {
                clearLevel1(coins, platforms, movingPlatforms, enemies, flyingEnemies, rotatingPows, &bowlingBall, background);
                clearPlayer(&player);
                createPlayer(&player);
                createCamera(&camera);
                player.level = 0;
            }
        }
    }

    if (player.level == 0)
        UnloadTexture(splashScreen.splashScreen);

    else if (player.level == 1)
        clearLevel1(coins, platforms, movingPlatforms, enemies, flyingEnemies, rotatingPows, &bowlingBall, background);

    else if (player.level == 1.01f) {
        UnloadTexture(splashScreen.splashScreen);
        clearLevel1(NULL, NULL, movingPlatforms, enemies, flyingEnemies, rotatingPows, &bowlingBall, background);
    }
   
    else if (player.level == 1.1f) {
        UnloadTexture(splashScreen.splashScreen);
        clearLevel1(NULL, NULL, movingPlatforms, enemies, flyingEnemies, rotatingPows, &bowlingBall, background);
        clearLevel1_1(platforms, coins);
    }

    else if (player.level == 1.11f)
        clearLevel1(coins, platforms, movingPlatforms, enemies, flyingEnemies, rotatingPows, &bowlingBall, background);

    UnloadFont(mainFont);
    UnloadSound(music);
    clearPlayer(&player);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
