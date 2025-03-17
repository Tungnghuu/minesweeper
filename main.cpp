#include <iostream>
#include <raylib.h>

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define COLS 20
#define ROWS 20

const int TILE_WIDTH = 40;
const int TILE_HEIGHT = 40;
const int MINES = 60;
bool isGameOver = false;
Texture2D texture_flag;
Texture2D texture_bomb;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

typedef struct {
    int x;
    int y;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int nearbyMineCount;

} sTile;

sTile grid[COLS][ROWS];

enum GameState{
    MAIN_MENU,
    PLAYING,
    GAME_OVER
};

GameState gameState = MAIN_MENU;

void RenderMainMenu();
void RenderGameOver();
void ToggleFlag(int x, int y);
bool isTileValid(int x, int y);
void RevealTile(int x, int y);
int CountNearbyMines(int x, int y);
void ResetTiles();
void RenderTile(sTile tile);
void RenderTiles();
void GameStartUp();
void GameUpdate();
void GameRender();
void GameShutDown();
void GameReset();
void RenderBoard();

int main () {

    cout << "Hello World!" << endl;


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib:: Minesweeper");
    SetTargetFPS(60);

    GameStartUp();

    while (!WindowShouldClose()){
        
        GameUpdate();

        BeginDrawing(); 

            GameRender();

        EndDrawing();

    }

    GameShutDown();
    CloseWindow();

    return 0;
}

void GameStartUp(){
    InitAudioDevice();

    Image flag = LoadImage("flag.png");
    ImageResize(&flag, TILE_WIDTH, TILE_HEIGHT);
    texture_flag = LoadTextureFromImage(flag);
    UnloadImage(flag);

    Image bomb = LoadImage("bomb.png");
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
        if (IsKeyPressed(KEY_ENTER)) {
            gameState = PLAYING;
            GameReset();
        }
        return;
    }

    if (gameState == GAME_OVER) {
        if (IsKeyPressed(KEY_ENTER)) {
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

    if(tile.isRevealed){

        if(tile.isMine) {
            DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, RED);
            DrawTexture(texture_bomb, tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, WHITE);
        } 
        
        else {

            if (((tile.x + tile.y) % 2 == 0)){

                if (tile.nearbyMineCount > 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, Color{229, 194, 159, 255});
                    DrawText(TextFormat("%d", tile.nearbyMineCount), tile.x * TILE_WIDTH + 14, tile.y * TILE_HEIGHT + 5, TILE_HEIGHT - 4, DARKGRAY );
                } if (tile.nearbyMineCount == 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, Color{229, 194, 159, 255});
                }
            } 

            else {

                if (tile.nearbyMineCount > 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, Color{215, 184, 153, 255});
                    DrawText(TextFormat("%d", tile.nearbyMineCount), tile.x * TILE_WIDTH + 14, tile.y * TILE_HEIGHT + 5, TILE_HEIGHT - 4, DARKGRAY );
                } if (tile.nearbyMineCount == 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, Color{215, 184, 153, 255});
                }
            }
        }
    } 

    if (tile.isFlagged){
        DrawTexture(texture_flag, tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, WHITE);
    }  

    if (tile.x == hoverCol && tile.y == hoverRow) {
        DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, Color{255, 255, 255, 100});
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
            Color tileColor = ((row + col) % 2 == 0) ? Color{170, 215, 81, 255} : Color{162, 209, 73, 255};
            DrawRectangle(col * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, tileColor);
        }
    }
}
void RenderGameOver(){
    if (isGameOver) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{0, 0, 0, 100});
        DrawText("Game Over!", SCREEN_WIDTH / 2 - MeasureText("Game Over!", 40) / 2, SCREEN_HEIGHT / 2 - 20, 40, RED);
        DrawText("Press ENTER to return to Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to return to Main Menu", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, RED);
    }
}
void RenderMainMenu() {
    ClearBackground(RAYWHITE);
    DrawText("Minesweeper", SCREEN_WIDTH / 2 - MeasureText("Minesweeper", 40) / 2, SCREEN_HEIGHT / 2 - 60, 40, DARKGRAY);
    DrawText("Press ENTER to Start", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to Start", 20) / 2, SCREEN_HEIGHT / 2, 20, DARKGRAY);
}
