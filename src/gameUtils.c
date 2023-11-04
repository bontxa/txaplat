#include "include/txaplat.h"

void lowScreenResolution() {
    InitWindow(800, 600, "txaplat - low screen resolution");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(YELLOW);
        DrawText("Screen resolution must be at least 1920x1080", 10, 10, 20, RED);
        DrawText("Press ESC to quit", 10, 40, 20, RED);
        EndDrawing();
    }
    CloseWindow();
}

bool loadHighScore(int *highScore) {
    FILE *storeRecord = fopen("./record.txt", "r");
    if (storeRecord == NULL) {
        printf("failed to open file 'record'\n");
        return false;
    }
    if (fgetc(storeRecord) != EOF) {
        fseek(storeRecord, 0, SEEK_SET);
        fscanf(storeRecord, "%u", highScore);
        fclose(storeRecord);
    }
    return true;
}

bool uploadHighScore(int *score, int *highScore)
{
    if (*score > *highScore) {
        FILE *storeNewRecord = fopen("./record.txt", "w");
        if (storeNewRecord == NULL) {
            printf("failed to open file 'record'\n");
            return false;
        }
        fprintf(storeNewRecord, "%u", *score);
        fclose(storeNewRecord);
        *highScore = *score;
    }
    return true;
}

void handleMovement(int *currentFrame, int *frameCounter, int frameSpeed, int numFrames) {   
    if (++*frameCounter >= frameSpeed) {
        *frameCounter = 0;
        *currentFrame = (*currentFrame + 1) % numFrames;
    }
}

bool pauseGame(bool *isPaused, t_player *player, Font mainFont) {
    if (IsKeyPressed(KEY_P) && player->level != 0)
        *isPaused = !*isPaused;
    if (*isPaused) {
        const char *text = "GAME PAUSED";
        Vector2 textSize = MeasureTextEx(mainFont, text, 80, 1);
        Vector2 position = { WIDTH / 2 - textSize.x / 2, HEIGHT / 2 - textSize.y / 2 };
        BeginDrawing();
        ClearBackground(PINK);
        DrawTextEx(mainFont, text, position , 80, 1, BLUE);
        EndDrawing();
        return true;
    }
    return false;
}

void printHighscore(int highScore, Font mainFont) {
    const char *string = TextFormat("HIGHSCORE: %06u", highScore);
    Vector2 stringSize = MeasureTextEx(mainFont, string, MAINFONT, 1);
    DrawTextEx(mainFont, string, (Vector2){ WIDTH / 2 - stringSize.x / 2, 10 }, MAINFONT, 1, RED);
}

void printScore(t_player *player, Font mainFont) {
    const char *string = TextFormat("SCORE: %06u", player->score);
    Vector2 stringSize = MeasureTextEx(mainFont, string, MAINFONT, 1);
    DrawTextEx(mainFont, string, (Vector2){ WIDTH - stringSize.x - 10, 10 }, MAINFONT, 1, RED);
}

void printLives(t_player *player, Font mainFont) {
    const char *string = TextFormat("LIVES: %02u", player->lives);
    Vector2 stringSize = MeasureTextEx(mainFont, string, MAINFONT, 1);
    DrawTextEx(mainFont, string, (Vector2){ WIDTH - stringSize.x - 10, 50 }, MAINFONT, 1, GREEN);
}

void printTotalCoins(t_player *player, Font mainFont) {
    const char *string = TextFormat("COINS: %03u", player->coinsTaken);
    Vector2 stringSize = MeasureTextEx(mainFont, string, MAINFONT, 1);
    DrawTextEx(mainFont, string, (Vector2){ WIDTH - stringSize.x - 10, 90 }, MAINFONT, 1, YELLOW);
}

void printTotalShots(t_player *player, Font mainFont) {
    const char *string;
    if (player->shots)
        string = TextFormat("SHOTS REMAINING: %02u", player->shots);
    else 
        string = TextFormat("SHOTS: EMPTY");
    Vector2 stringSize = MeasureTextEx(mainFont, string, MAINFONT, 1);
    DrawTextEx(mainFont, string, (Vector2) { WIDTH - stringSize.x - 10, 130 }, MAINFONT, 1, BLUE);
}

void printTime(Font mainFont, double timer) {
    const char *string = TextFormat("TIME LEFT: %02u", (int)timer);
    Vector2 stringSize = MeasureTextEx(mainFont, string, 40, 1);
    DrawTextEx(mainFont, string, (Vector2){ WIDTH / 2 - stringSize.x / 2, 10 }, 40, 1, RED);
}
