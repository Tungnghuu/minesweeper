#include "game.h"

void GameStartUp(){
    InitAudioDevice();
    SetExitKey(0);
    SetTargetFPS(60);
    LoadHighScores();
    GameSetDifficulty(1);
    LoadSoundFX();

    music = LoadMusicStream("sound/Google_Minesweeper_Music.mp3");
    SetMusicVolume(music,musicVolume);
    PlayMusicStream(music);
}

void GameUpdate(){ 
    Vector2 mousePos = GetMousePosition();
    int col = mousePos.x / TILE_WIDTH;
    int row = mousePos.y / TILE_HEIGHT;
    
    if (gameState == MAIN_MENU){
        ResumeMusicStream(music);
        startTime = 0;
        elapsedTime = 0;
        SCREEN_HEIGHT = 800;
        SCREEN_WIDTH = 800;
        SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        if(IsKeyPressed(KEY_ENTER)){
            gameState = CHOOSING_DIFFICULTY;
        }
        if(IsKeyPressed(KEY_ESCAPE)){
            PreviousGameState = MAIN_MENU;
            gameState = SETTING;
        }
        return;
    }
    
    if (gameState == CHOOSING_DIFFICULTY) {
        const char* options[] = {"Easy", "Medium", "Hard"};
        int optionCount = 3;
        int fontSize = 30;
        int spacing = 50;
        
        for (int i = 0; i < optionCount; i++) {
            int textWidth = MeasureText(options[i], fontSize);
            int textX = SCREEN_WIDTH / 2 - textWidth / 2;
            int textY = SCREEN_HEIGHT / 2 - (optionCount * spacing) / 2 + i * spacing;
            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            mousePos.x >= textX && mousePos.x <= textX + textWidth &&
            mousePos.y >= textY && mousePos.y <= textY + fontSize){
                
                GameSetDifficulty(i);
                currentDifficulty = i;
                gameState = FIRST_REVEAL;
                SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT + 50);
                LoadImage();
                break;
            }
        }
        
        if(IsKeyPressed(KEY_ESCAPE)){
            PreviousGameState = CHOOSING_DIFFICULTY;
            gameState = SETTING;
        }

        return;
    }

    if (gameState == FIRST_REVEAL){
        PauseMusicStream(music);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (isTileValid(col, row)){
                FirstRevealSurround(col,row);
                PlaceMine();
                RevealTile(col,row);
                gameState = PLAYING;
            }
        } 
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            if (isTileValid(col, row)){
                ToggleFlag(col, row);
            }
        } 
        if(IsKeyPressed(KEY_ESCAPE)){
            PreviousGameState = FIRST_REVEAL;
            gameState = SETTING;
        }
        return;
    }

    if(gameState == PLAYING) { 
        PauseMusicStream(music);
        if(startTime == 0){
            startTime = GetTime();
        }
        elapsedTime = (int)(GetTime() - startTime);

        if (elapsedTime > 999) {
            elapsedTime = 999;
        }
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (isTileValid(col, row)){
                RevealTile(col, row);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            if (isTileValid(col, row)){
                ToggleFlag(col, row);
            }
        }
        
        if (CheckWin()) {
            gameState = WON;
        }

        if(IsKeyPressed(KEY_ESCAPE)){
            PreviousGameState = PLAYING;
            gameState = SETTING;
        }
        return;
    }

    if(gameState == SETTING){
        ResumeMusicStream(music);
        if(IsKeyPressed(KEY_ESCAPE)){
            gameState = PreviousGameState;
        }
        return;
    }

    if (gameState == GAME_OVER) {
        ResumeMusicStream(music);
        if (GetKeyPressed() != 0) {
            gameState = MAIN_MENU;
            PreviousGameState = GAME_OVER;
        }
        return;
    }

    if (gameState == WON){
        ResumeMusicStream(music);
        if (currentDifficulty == 0 && elapsedTime < highScoreEasy) {
            highScoreEasy = elapsedTime;
            SaveHighScores();
        } else if (currentDifficulty == 1 && elapsedTime < highScoreMedium) {
            highScoreMedium = elapsedTime;
            SaveHighScores();
        } else if (currentDifficulty == 2 && elapsedTime < highScoreHard) {
            highScoreHard = elapsedTime;
            SaveHighScores();
        }
    
        if (GetKeyPressed() != 0) {
            gameState = MAIN_MENU;
            PreviousGameState = WON;
        }
        return;
    }

}

void GameRender(){
    
    if (gameState == MAIN_MENU) {
        RenderMainMenu();
        return;
    }

    if(gameState == CHOOSING_DIFFICULTY){
        Vector2 mousePos = GetMousePosition();
        RenderDifficultyMenu(mousePos.x,mousePos.y);
        return;
    }
    RenderBoard();
    RenderTiles();
    RenderUI();
    if(gameState == SETTING){
        if(PreviousGameState == MAIN_MENU){
            RenderMainMenu();
        }
        else if(PreviousGameState == CHOOSING_DIFFICULTY){
            RenderDifficultyMenu(0,0);
        }
        RenderSetting();

        return;
    }

    if (gameState == GAME_OVER){
        RenderGameOver();
    }

    if(gameState == WON){
        RenderWin();
        return;
    }

}

void GameShutDown(){
    StopMusicStream(music);
    UnloadMusicStream(music);
    UnloadSoundFX();
    CloseAudioDevice();

}

void GameReset(){
    ResetTiles();

}

void GameSetDifficulty(int difficulty){
    switch (difficulty){
        case 0:                 // Easy
            SCREEN_WIDTH = 400;
            SCREEN_HEIGHT = 400;
            TILE_WIDTH = 40;
            TILE_HEIGHT = 40;
            COLS = 10;
            ROWS = 10;
            MINES = 10;
            break;
        case 1:                 // Medium
            SCREEN_WIDTH = 600;
            SCREEN_HEIGHT = 600;
            TILE_WIDTH = 30;
            TILE_HEIGHT = 30;
            COLS = 20;
            ROWS = 20;
            MINES = 50;
            break;
        case 2:                 // Hard
            SCREEN_WIDTH = 900;
            SCREEN_HEIGHT = 900;
            TILE_WIDTH = 30;
            TILE_HEIGHT = 30;
            COLS = 30;
            ROWS = 30;
            MINES = 150;
            break;
    }
    currentDifficulty = difficulty;
    ResizeGrid();
    GameReset(); 

}
