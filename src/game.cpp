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

    if (gameState == MAIN_MENU) {
        if (GetKeyPressed() != 0) {
            gameState = PLAYING;
            GameReset();
        }
        return;
    }

    if (gameState == GAME_OVER) {
        if (GetKeyPressed() != 0) {
            isGameOver = false;
            gameState = MAIN_MENU;
            GameReset();
        }
        return;
    }


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
    }

    if (isGameOver) {
        gameState = GAME_OVER;
    }

    if (CheckWin()) {
        gameState = WON;
    }

    if (gameState == WON) {
        RenderWin();
        if (GetKeyPressed() != 0) {
            gameState = MAIN_MENU;
            GameReset();
        }
        return;
    }
}

void GameRender(){

    if (gameState == MAIN_MENU) {
        RenderMainMenu();
        return;
    }
    RenderBoard();
    RenderTiles();
    RenderGameOver();
    if (gameState == WON) {
        RenderWin();
        return;
    }
}

void GameShutDown(){
    CloseAudioDevice();

}

void GameReset(){
    ResetTiles();
    
}
bool CheckWin() {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (!grid[i][j].isMine && !grid[i][j].isRevealed) {
                return false;
            }
        }
    }
    return true;
}