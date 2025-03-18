#include "game.h"


void GameStartUp(){
    InitAudioDevice();

    Image flag = LoadImage("images/flag.png");

    ImageResize(&flag, TILE_WIDTH - 10, TILE_HEIGHT - 10);
    texture_flag = LoadTextureFromImage(flag);
    UnloadImage(flag);

    Image bomb = LoadImage("images/bomb.png");

    ImageResize(&bomb, TILE_WIDTH, TILE_HEIGHT);
    texture_bomb = LoadTextureFromImage(bomb);
    UnloadImage(bomb);

    GameReset();
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

}

void GameRender(){

    if (gameState == MAIN_MENU) {
        RenderMainMenu();
        return;
    }
    RenderBoard();
    RenderTiles();
    RenderGameOver();

}

void GameShutDown(){
    CloseAudioDevice();

}

void GameReset(){
    ResetTiles();

}

void RenderTiles(){
    for (int i = 0; i < COLS; i++){
        for (int j = 0; j < ROWS; j++){

            RenderTile(grid[i][j]);

        }
    }
}

void RenderTile(sTile tile){
    Vector2 mousePos = GetMousePosition();

    int hoverCol = mousePos.x / TILE_WIDTH;
    int hoverRow = mousePos.y / TILE_HEIGHT;

    Color MineColors[] = {
        {0, 0, 0, 255},
        {20, 150, 60, 255},     // 1 - Dark Green
        {30, 70, 180, 255},     // 2 - Dark Blue
        {40, 160, 160, 255},    // 3 - Teal
        {200, 180, 40, 255},    // 4 - Golden Yellow
        {200, 100, 20, 255},    // 5 - Burnt Orange
        {180, 40, 40, 255},     // 6 - Deep Red
        {100, 30, 120, 255},    // 7 - Dark Purple
        {180, 40, 140, 255}     // 8 - Deep Magenta
    };

    if(tile.isRevealed){

        if(tile.isMine) {

            DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, RED);
            DrawTexture(texture_bomb, tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, WHITE);

        } 
        else {
            if (((tile.x + tile.y) % 2 == 0)){

                if (tile.nearbyMineCount > 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, 
                        tile.y * TILE_HEIGHT, 
                        TILE_WIDTH, 
                        TILE_HEIGHT, 
                        DARK_BROWN
                    );
                    DrawText(
                        TextFormat("%d", tile.nearbyMineCount),
                        tile.x * TILE_WIDTH + 14, 
                        tile.y * TILE_HEIGHT + 5, 
                        TILE_HEIGHT - 4, 
                        MineColors[tile.nearbyMineCount]
                    );
                } 
                if (tile.nearbyMineCount == 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, 
                        tile.y * TILE_HEIGHT, 
                        TILE_WIDTH, 
                        TILE_HEIGHT, 
                        DARK_BROWN
                    );
                }

            } 
            else {
                if (tile.nearbyMineCount > 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, 
                        tile.y * TILE_HEIGHT, 
                        TILE_WIDTH, 
                        TILE_HEIGHT, 
                        LIGHT_BROWN
                    );
                    DrawText(
                        TextFormat("%d", tile.nearbyMineCount),
                        tile.x * TILE_WIDTH + 14, 
                        tile.y * TILE_HEIGHT + 5, 
                        TILE_HEIGHT - 4, 
                        MineColors[tile.nearbyMineCount]
                    );
                } 
                if (tile.nearbyMineCount == 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, 
                        tile.y * TILE_HEIGHT, 
                        TILE_WIDTH, 
                        TILE_HEIGHT, 
                        LIGHT_BROWN
                    );
                }

            }
        }
    } 
    if (tile.isFlagged){
        DrawTexture(texture_flag, tile.x * TILE_WIDTH + 5,
            tile.y * TILE_HEIGHT + 5, 
            WHITE
        );
    }  
    if (tile.x == hoverCol && tile.y == hoverRow) {
        DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT,
            TILE_WIDTH, TILE_HEIGHT,
            Color{255, 255, 255, 100}
        );
    }


}

void ResetTiles(){
    for (int i = 0; i < COLS; i++) {
        for(int j = 0; j < ROWS; j++) {
            grid[i][j] = (sTile)
            {
                .x = i,
                .y = j,
                .isMine = false,
                .isRevealed = false,
                .isFlagged = false,
                .nearbyMineCount = -1,
            };
        }
    }

    int count = 0;
    while (count < MINES) {
        int x = GetRandomValue(0, COLS - 1);
        int y = GetRandomValue(0, ROWS - 1);
        if (!(grid[x][y].isMine)) {
            grid[x][y].isMine = true;
            count++;
        }
    }

    for (int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
            if (!grid[i][j].isMine){
                grid[i][j].nearbyMineCount = CountNearbyMines(i, j);
            }
        }
    }
}

int CountNearbyMines(int x, int y){

    int mineCount = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < ROWS && ny < COLS && grid[nx][ny].isMine) {
            mineCount++;
        }
    }
    return mineCount;
}

bool isTileValid(int x, int y){
    return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}

void RevealTile(int x, int y){
    if(grid[x][y].isFlagged || grid[x][y].isRevealed) {
        if (grid[x][y].isFlagged && grid[x][y].nearbyMineCount == 0){
            grid[x][y].isFlagged = false;
        }
        return;
    }

    grid[x][y].isRevealed = true;

    if (grid[x][y].nearbyMineCount == 0){
        for (int i = 0; i < 8; i++) {

            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < COLS && ny < ROWS && !grid[nx][ny].isMine && !grid[nx][ny].isRevealed)  {
                RevealTile(nx,ny);
            }
        }
    }

    if(grid[x][y].isMine){

        isGameOver = true;

        for (int i = 0 ;i < COLS; i++){
            for (int j = 0; j < ROWS; j++){
                if(grid[i][j].isMine && !grid[i][j].isFlagged){
                    grid[i][j].isRevealed = true;
                }
                if(grid[i][j].isFlagged && !grid[i][j].isMine){
                    grid[i][j].isFlagged = false;
                    
                }
            }
        }
    
    }

}

void ToggleFlag(int x, int y){

    if (grid[x][y].isRevealed){
        return;
    }
    
    grid[x][y].isFlagged = !grid[x][y].isFlagged;

}

void RenderBoard(){
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            Color tileColor = ((row + col) % 2 == 0) ? LIGHT_GREEN : DARK_GREEN;
            DrawRectangle(col * TILE_WIDTH, row * TILE_HEIGHT, 
                TILE_WIDTH, 
                TILE_HEIGHT, 
                tileColor
            );
        }
    }
}

void RenderGameOver(){
    if (isGameOver) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{0, 0, 0, 100});
        DrawText("Game Over!", 
            SCREEN_WIDTH / 2 - MeasureText("Game Over!", 40) / 2,
            SCREEN_HEIGHT / 2 - 20,
            40,
            RED
        );
        DrawText("Press Any Key to return to Main Menu",
            SCREEN_WIDTH / 2 - MeasureText("Press Any Key to return to Main Menu", 20) / 2,
            SCREEN_HEIGHT / 2 + 20, 20, RED
        );
    }
}

void RenderMainMenu() {
    ClearBackground(RAYWHITE);
    DrawText("Minesweeper", 
        SCREEN_WIDTH / 2 - MeasureText("Minesweeper", 40) / 2, 
        SCREEN_HEIGHT / 2 - 60, 
        40, 
        DARKGRAY
    );
    DrawText("Press Any Key to Start", 
        SCREEN_WIDTH / 2 - MeasureText("Press Any Key to Start", 20) / 2, 
        SCREEN_HEIGHT / 2, 
        20, 
        DARKGRAY
    );
}
