#include <iostream>
#include <raylib.h>

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define COLS 12
#define ROWS 12

const int TILE_WIDTH = SCREEN_WIDTH / COLS;
const int TILE_HEIGHT = SCREEN_HEIGHT / ROWS;
const int MINES = 15;

typedef struct {
    int x;
    int y;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int nearbyMineCount;

} sTile;

sTile grid[COLS][ROWS];

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

int main () {

    cout << "Hello World" << endl;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib:: MineSweeper");
    SetTargetFPS(60);

    GameStartUp();

    while (!WindowShouldClose()){
        
        GameUpdate();

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            
            GameRender();

        EndDrawing();

    }

    GameShutDown();
    CloseWindow();

    return 0;
}

void GameStartUp(){
    InitAudioDevice();

    GameReset();
}

void GameUpdate(){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        Vector2 mousePos = GetMousePosition();
        int col = mousePos.x / TILE_WIDTH;
        int row = mousePos.y / TILE_HEIGHT;

        if (isTileValid(col, row)){
            RevealTile(col, row);
        }
    }

}

void GameRender(){

    RenderTiles();

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
    if(tile.isRevealed){
        if(tile.isMine) {
            DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, RED);
        } else {
            if (tile.nearbyMineCount > 0) {
                DrawText(TextFormat("%d", tile.nearbyMineCount), tile.x * TILE_WIDTH + 17, tile.y * TILE_HEIGHT + 5, TILE_HEIGHT - 4, DARKGRAY );
            }
        }
    }
    DrawRectangleLines(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, RAYWHITE);


}

void ResetTiles(){
    for (int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
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
        int x = GetRandomValue(0, ROWS);
        int y = GetRandomValue(0, COLS);
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
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
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
    return x >= 0 && x < COLS && y > 0 && y < ROWS;
}
void RevealTile(int x, int y){
    if(grid[x][y].isFlagged || grid[x][y].isRevealed) {
        return;
    }

    grid[x][y].isRevealed = true;

    if(grid[x][y].isMine){
        //game over;
    }
}