#include "game.h"

void GameStartUp(){
    InitAudioDevice();
}

void LoadImage(){
    Image flag = LoadImage("images/flag.png");
    ImageResize(&flag, TILE_WIDTH - 10, TILE_HEIGHT - 10);
    texture_flag = LoadTextureFromImage(flag);
    UnloadImage(flag);

    Image bomb = LoadImage("images/bomb.png");
    ImageResize(&bomb, TILE_WIDTH, TILE_HEIGHT);
    texture_bomb = LoadTextureFromImage(bomb);
    UnloadImage(bomb);
}

void GameUpdate(){ 
    Vector2 mousePos = GetMousePosition();
    int col = mousePos.x / TILE_WIDTH;
    int row = mousePos.y / TILE_HEIGHT;

    // MAIN MENU

    if (gameState == MAIN_MENU){
        SCREEN_HEIGHT = 800;
        SCREEN_WIDTH = 800;
        SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        if (GetKeyPressed() != 0){
            gameState = /*FIRST_REVEAL*/ CHOOSING_DIFFICULTY;
        }
        return;
    }

    //CHOOSING DIFFICULTY

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
                mousePos.y >= textY && mousePos.y <= textY + fontSize) {
                
                SetDifficulty(i);
                gameState = FIRST_REVEAL;
                SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                LoadImage();
                break;
            }
        }
        return;
    }

    // FIRST REVEAL

    if (gameState == FIRST_REVEAL){                     
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (isTileValid(col, row)){
                firstRevealSurround(col,row);
                placeMine();
                RevealTile(col,row);
                gameState = PLAYING;
            }
        } 
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            if (isTileValid(col, row)){
                ToggleFlag(col, row);
            }
        } 
        return;
    }

    // START PLAYING
    
    if(gameState == PLAYING) { 
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

        if (isGameOver) {
            gameState = GAME_OVER;
        }
        return;
    }

    // GAME OVER

    if (gameState == GAME_OVER) {
        if (GetKeyPressed() != 0) {
            isGameOver = false;
            gameState = MAIN_MENU;
        }
        return;
    }

    // WIN STATE

    if (gameState == WON) {
        if (GetKeyPressed() != 0) {
            gameState = MAIN_MENU;
        }
        return;
    }
    return;
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
    RenderGameOver();
    if(gameState == WON){
        RenderWin();
        return;
    }
    return;
}

void GameShutDown(){
    CloseAudioDevice();
}

void GameReset(){
    ResetTiles();
}

void ResizeGrid(){
    grid.resize(ROWS);
    for (int i = 0; i < ROWS; i++) {
        grid[i].resize(COLS);
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = {i, j, false, false, false, -1, false};
        }
    }
}