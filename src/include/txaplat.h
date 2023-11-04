#ifndef TXAPLAT_H
#define TXAPLAT_H
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#define WIDTH 1920
#define HEIGHT 1080
#define LEVELWIDTH 8952
#define LEVELHEIGHT 1080
#define BASEHEIGHT 192
#define MAINFONT 30
#define GRAVITY 70.0f
#define PLAYER_JUMP_FORCE 20.0f

typedef struct s_player {
    Texture2D idle[2];
    Texture2D jump[2];
    Texture2D runRight[4];
    Texture2D runLeft[4];
    Texture2D death;
    Texture2D drawTexture;
    Texture2D enemyDeath;
    Vector2 velocity;
    Vector2 position;
    Vector2 positionResume;
    Rectangle collision;
    Sound walking;
    Sound jumping;
    Sound coin;
    Sound pow;
    Sound launchBowlingBall;
    Sound hit1;
    Sound playerDeath;
    int score;
    int currentFrame; 
    int frameCounter;
    bool isFacingLeft;
    bool isMoving;
    bool isJumping;
    bool isDead;
    bool isResumed;
    bool isLevelCreated;
    bool isEnemySquashed;
    bool isLevelRestarted;
    short coinsTaken;
    short lives;
    short shots;
    float limit;
    float level;
}   t_player;

typedef struct s_background {
    Texture2D background;
    Vector2 position;
    bool isRendered;
}   t_background;

typedef struct s_enemy {
    Texture2D *enemy;
    Texture2D drawTexture;
    Vector2 velocity;
    Vector2 position;
    Rectangle collision;
    bool isDead;
    bool isRendered;
    int currentFrame;
    int frameCounter;
    float min;
    float max;
    double timer;
}   t_enemy;


typedef struct s_bomb {
    Texture2D bomb;
    Vector2 velocity;
    Vector2 position;
    Sound splat;
    Sound drop;
    bool isActive;
    bool isRendered;
}   t_bomb;

typedef struct s_flyingEnemy {
    Texture2D *enemyLeft;
    Texture2D drawTexture;
    Sound noise;
    Vector2 velocity;
    Vector2 position;
    Rectangle collision;
    bool isRendered;
    int currentFrame;
    int frameCounter;
    float min;
    float max;
    double timer;
    t_bomb bomb;
}   t_flyingEnemy;


typedef struct s_coin {
    Texture2D coin[5];
    Texture2D drawTexture;
    Vector2 position;
    Rectangle collision;
    bool taken;
    bool isRendered;
    int currentFrame;
    int frameCounter;
}   t_coin;

typedef struct s_platform {
    Texture2D platform;
    Vector2 position;
    Rectangle collision;
    bool isRendered;
}   t_platform;

typedef struct s_movingPlatform {
    Texture2D texture;
    Vector2 velocity;
    Vector2 position;
    float min;
    float max;
    bool isRendered;
}   t_movingPlatform;

typedef struct s_rotatingPow {
    Texture2D pow;
    Vector2 position;
    Vector2 origin;
    float rotationAngle;
    float rotationSpeed;
    bool taken;
    bool isRendered;
}   t_rotatingPow;

typedef struct s_splashScreen {
    Texture2D splashScreen;
    Vector2 position;
    float increment;
}   t_splashScreen;

typedef struct s_movingPow {
    Texture2D pow;
    Vector2 position;
    Vector2 velocity;
    Vector2 origin;
    float rotationAngle;
    bool active;
}   t_movingPow;

void lowScreenResolution();
bool loadHighScore(int *highScore);
bool uploadHighScore(int *score, int *highScore);
void welcomeScreen(t_player *player, t_splashScreen *splashScreen, Sound *music);
void creditScreen(t_player *player, Font mainFont);
void runScreen(t_player *player, t_splashScreen *splashScreen, Font mainFont);
bool pauseGame(bool *isPaused, t_player *player, Font mainFont);
void handleMovement(int *currentFrame, int *frameCounter, int frameSpeed, int numFrames);
void createPlayer(t_player *player);
void createCamera(Camera2D *camera);
t_background *createBackground(t_player *player, short totalElements);
t_enemy *createEnemies(t_player *player, t_platform *platforms);
t_flyingEnemy *createFlyingEnemies(t_player *player);
t_platform *createPlatforms(t_player *player, short numPlatforms);
t_movingPlatform *createMovingPlatforms(short numPlatforms);
t_coin *createCoins(t_platform *platforms, t_movingPlatform *mov_platforms, t_player *player, short numCoins);
t_rotatingPow *createRotatingPows(t_platform *platforms, t_movingPlatform *movPlatform, float playerHeight);
void createBowlingBall(t_movingPow *bowlingBall, t_player *player);
void updateCamera(Camera2D *camera, t_player *player);
void updateBackground(t_background *background, Rectangle cameraRect, short totalElements);
void updateEnemies(t_enemy *enemies, t_movingPow *bowlingBall, t_player *player, Rectangle cameraRect);
void updatePlatforms(t_platform *platforms, Rectangle cameraRect);
void updateMovingPlatforms(t_movingPlatform *platforms, t_player *player, t_rotatingPow *rotatingPows, Rectangle cameraRect, short numPlatforms);
void updateFlyingEnemies(t_flyingEnemy *enemies, t_player *player, t_platform *platforms, t_movingPlatform *movingPlatforms, Rectangle cameraRect);
void updateCoins(t_player *player, t_coin *coins, short numCoins, Rectangle cameraRect);
void updateRotatingPows(t_player *player, t_rotatingPow *rotatingPows, Rectangle cameraRect);
void updateBowlingBall(t_player *player, t_movingPow *bowlingBall, t_platform *platforms, t_rotatingPow *rotatingPows);
void updatePlayer(t_player *player, t_platform *platforms, t_movingPlatform *movingPlatforms, Camera2D *camera);
void printHighscore(int highScore, Font mainFont);
void printScore(t_player *player, Font mainFont);
void printLives(t_player *player, Font mainFont);
void printTotalCoins(t_player *player, Font mainFont);
void printTotalShots(t_player *player, Font mainFont);
void printTime(Font mainFont, double timer);
void handlePlayerCollision(t_enemy *enemy, t_player *player);
void playerDeath(t_player *player);
void createDemoEnd(Font mainFont);
void clearPlayer(t_player *player);
void clearLevel1(t_coin *coins, t_platform *platforms, t_movingPlatform *movingPlatforms, t_enemy *enemies, t_flyingEnemy *enemies4, t_rotatingPow *rotatingPows, t_movingPow *bowlingBall, t_background *background);
void clearLevel1_1(t_platform *platforms, t_coin *coins);
void clearPlatforms(t_platform *platforms, short numPlatforms, t_movingPlatform *movingPlatforms, short numMovingPlatforms);
void clearCoins(t_coin *coins, short numCoins);

#endif
