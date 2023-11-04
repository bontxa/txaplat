#include "include/txaplat.h"

void welcomeScreen(t_player *player, t_splashScreen *splashScreen, Sound *music) {

    if (!player->isLevelCreated) {
        player->isLevelCreated = true;
        splashScreen->splashScreen = LoadTexture("./assets/sprites/splash/welcomeScreen.png");
        splashScreen->position = (Vector2){ 0, 0 };
        splashScreen->increment = 0.2f;
    }

    if (splashScreen->position.y > 10 || splashScreen->position.y < -10)
        splashScreen->increment *= -1;

    splashScreen->position.y += splashScreen->increment;

    if (!IsSoundPlaying(*music)) {
        SetSoundVolume(*music, 0.2f);
        PlaySound(*music);
    }

    BeginDrawing();
    ClearBackground((Color){ 208, 4, 27, 255 });
    DrawTexture(splashScreen->splashScreen, splashScreen->position.x, splashScreen->position.y, WHITE);

    
    EndDrawing();
    if(IsKeyPressed(KEY_ENTER)) {
        UnloadTexture(splashScreen->splashScreen);
        player->isLevelCreated = false;
        player->level = 1;
    }

    if (IsKeyPressed(KEY_C)) {
        UnloadTexture(splashScreen->splashScreen);
        player->isLevelCreated = false;
        player->level = 0.1f;
    }
}


void runScreen(t_player *player, t_splashScreen *splashScreen, Font mainFont) {

    const char *string1 = "GO FOR THE";
    const char *string2 = "20 SEC RUN!";
    Vector2 stringSize1 = MeasureTextEx(mainFont, string1, 100, 1);
    Vector2 stringSize2 = MeasureTextEx(mainFont, string2, 100, 1);


    BeginDrawing();
    ClearBackground((Color){ 19, 0, 215, 255 });
    DrawTexture(splashScreen->splashScreen, splashScreen->position.x, splashScreen->position.y, WHITE);
    DrawTextEx(mainFont, string1, (Vector2){ WIDTH / 2 - stringSize1.x / 2 + 250, HEIGHT / 2 - stringSize1.y / 2 - 100 }, 100, 1, YELLOW);
    DrawTextEx(mainFont, string2, (Vector2){ WIDTH / 2 - stringSize2.x / 2 + 250, HEIGHT / 2 - stringSize2.y / 2 + 100 }, 100, 1, YELLOW);
    EndDrawing();

    WaitTime(2);
    UnloadTexture(splashScreen->splashScreen);
    player->isLevelCreated = false;
    player->level = 1.1f;
}

void createDemoEnd(Font mainFont) {

    const char *text1 = "END OF DEMO,";
    const char *text2 = "THANKS FOR PLAYING!";
    const char *text4 = "Stay tuned for updates:";
    const char *text5 = "https://bontxa.itch.io/txaplat";
    const char *text3 = "HIT ENTER TO CONTINUE";

    Vector2 text1Size = MeasureTextEx(mainFont, text1, 40, 1);
    Vector2 text2Size = MeasureTextEx(mainFont, text2, 40, 1);
    Vector2 text3Size = MeasureTextEx(mainFont, text3, 40, 1);
    Vector2 text4Size = MeasureTextEx(mainFont, text4, 40, 1);
    Vector2 text5Size = MeasureTextEx(mainFont, text5, 40, 1);

    Vector2 position3 = { WIDTH / 2 - text3Size.x / 2, HEIGHT / 2 - text3Size.y / 2 };
    Vector2 position2 = { WIDTH / 2 - text2Size.x / 2, position3.y - text2Size.y - 100};
    Vector2 position1 = { WIDTH / 2 - text1Size.x / 2, position2.y - text1Size.y - 100 };
    Vector2 position4 = { WIDTH / 2 - text4Size.x / 2, position3.y + text3Size.y + 100 };
    Vector2 position5 = { WIDTH / 2 - text5Size.x / 2, position4.y + text4Size.y + 100 };
    BeginDrawing();
    
    ClearBackground(YELLOW);
    DrawTextEx(mainFont, text1, position1 , 40, 1, RED);
    DrawTextEx(mainFont, text2, position2 , 40, 1, RED);
    DrawTextEx(mainFont, text3, position3 , 40, 1, BLUE);
    DrawTextEx(mainFont, text4, position4 , 40, 1, BLUE);
    DrawTextEx(mainFont, text5, position5 , 40, 1, MAGENTA);
    
    EndDrawing();
}

void creditScreen(t_player *player, Font mainFont) {

    const char *text1 = "CREDITS";
    const char *text2 = "GAME POWERED BY raylib: www.raylib.com";
    const char *text3 = "SOUNDTRACK:";
    const char *text4 = "\"DarxieLand\" Kevin MacLeod (incompetech.com)";
    const char *text5 = "Licensed under Creative Commons: By Attribution 4.0 License";
    const char *text6 = "http://creativecommons.org/licenses/by/4.0/";
    const char *text7 = "\"Bet You Can ver 2\" Kevin MacLeod (incompetech.com)";
    const char *text8 = "FONT:";
    const char *text9 = "Font \"8-bit-hud\" (https://fontstruct.com/fontstructors/1297912/lspl)";
    const char *text10 = "Copyright (c) 2018-2023, \"lSPl\"";
    const char *text11 = "Licensed under the SIL Open Font License, Version 1.1";
    const char *text12 = "http://scripts.sil.org/OFL";
    const char *text13 = "SEE ALSO THE CREDITS.TXT FILE IN MAIN FOLDER";
    const char *text14 = "PRESS ENTER TO RETURN TO MAIN MENU";


    Vector2 text1Size = MeasureTextEx(mainFont, text1, 40, 1);
    Vector2 text2Size = MeasureTextEx(mainFont, text2, 35, 1);
    Vector2 text3Size = MeasureTextEx(mainFont, text3, 40, 1);
    Vector2 text4Size = MeasureTextEx(mainFont, text4, 35, 1);
    Vector2 text5Size = MeasureTextEx(mainFont, text5, 30, 1);
    Vector2 text6Size = MeasureTextEx(mainFont, text6, 30, 1);
    Vector2 text7Size = MeasureTextEx(mainFont, text7, 35, 1);
    Vector2 text8Size = MeasureTextEx(mainFont, text8, 40, 1);
    Vector2 text9Size = MeasureTextEx(mainFont, text9, 35, 1);
    Vector2 text10Size = MeasureTextEx(mainFont, text10, 30, 1);
    Vector2 text11Size = MeasureTextEx(mainFont, text11, 30, 1);
    Vector2 text12Size = MeasureTextEx(mainFont, text12, 30, 1);
    Vector2 text13Size = MeasureTextEx(mainFont, text13, 40, 1);
    Vector2 text14Size = MeasureTextEx(mainFont, text14, 40, 1);

    Vector2 position1 = { WIDTH / 2 - text1Size.x / 2, 40 };
    Vector2 position2 = { WIDTH / 2 - text2Size.x / 2, position1.y + text1Size.y + 30 };
    Vector2 position3 = { WIDTH / 2 - text3Size.x / 2, position2.y + text2Size.y + 50 };
    Vector2 position4 = { WIDTH / 2 - text4Size.x / 2, position3.y + text3Size.y + 20 };
    Vector2 position5 = { WIDTH / 2 - text5Size.x / 2, position4.y + text4Size.y + 20 };
    Vector2 position6 = { WIDTH / 2 - text6Size.x / 2, position5.y + text5Size.y + 20 };
    Vector2 position7 = { WIDTH / 2 - text7Size.x / 2, position6.y + text4Size.y + 40 };
    Vector2 position8 = { WIDTH / 2 - text5Size.x / 2, position7.y + text7Size.y + 20 };
    Vector2 position9 = { WIDTH / 2 - text6Size.x / 2, position8.y + text5Size.y + 20 };
    Vector2 position10 = { WIDTH / 2 - text8Size.x / 2, position9.y + text6Size.y + 50 };
    Vector2 position11 = { WIDTH / 2 - text9Size.x / 2, position10.y + text8Size.y + 20 };
    Vector2 position12 = { WIDTH / 2 - text10Size.x / 2, position11.y + text9Size.y + 20 };
    Vector2 position13 = { WIDTH / 2 - text11Size.x / 2, position12.y + text10Size.y + 20 };
    Vector2 position14 = { WIDTH / 2 - text12Size.x / 2, position13.y + text11Size.y + 20 };
    Vector2 position15 = { WIDTH / 2 - text13Size.x / 2, position14.y + text12Size.y + 50 };
    Vector2 position16 = { WIDTH / 2 - text14Size.x / 2, position15.y + text13Size.y + 20 };

    BeginDrawing();
    
    ClearBackground(YELLOW);
    DrawTextEx(mainFont, text1, position1 , 40, 1, BLUE);
    DrawTextEx(mainFont, text2, position2 , 35, 1, RED);
    DrawTextEx(mainFont, text3, position3 , 40, 1, MAGENTA);
    DrawTextEx(mainFont, text4, position4 , 35, 1, MAGENTA);
    DrawTextEx(mainFont, text5, position5 , 30, 1, MAGENTA);
    DrawTextEx(mainFont, text6, position6 , 30, 1, MAGENTA);
    DrawTextEx(mainFont, text7, position7 , 35, 1, MAGENTA);
    DrawTextEx(mainFont, text5, position8 , 30, 1, MAGENTA);
    DrawTextEx(mainFont, text6, position9 , 30, 1, MAGENTA);
    DrawTextEx(mainFont, text8, position10 , 40, 1, RED);
    DrawTextEx(mainFont, text9, position11 , 35, 1, RED);
    DrawTextEx(mainFont, text10, position12 , 30, 1, RED);
    DrawTextEx(mainFont, text11, position13 , 30, 1, RED);
    DrawTextEx(mainFont, text12, position14 , 30, 1, RED);
    DrawTextEx(mainFont, text13, position15 , 40, 1, BLUE);
    DrawTextEx(mainFont, text14, position16 , 40, 1, MAGENTA);

    if (IsKeyPressed(KEY_ENTER))
        player->level = 0;
    
    EndDrawing();
}