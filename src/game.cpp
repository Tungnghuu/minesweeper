#include "game.h"

void GameStartUp(){
    InitAudioDevice();

    LoadImage();
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

    if (gameState == MAIN_MENU) {                       
        if (GetKeyPressed() != 0) {
            gameState = /*FIRST_REVEAL*/ CHOOSING_DIFFICULTY;
            
        }
        return;
    }

    if (gameState == CHOOSING_DIFFICULTY){
        GameReset();
        gameState = FIRST_REVEAL;
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