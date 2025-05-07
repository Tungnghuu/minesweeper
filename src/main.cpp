#include <iostream>
#include <vector>
#include "game.h"

using namespace std;

Texture2D texture_flag;
Texture2D texture_bomb;
vector<vector<sTile>> grid(20, vector<sTile>(20));
GameState gameState = MAIN_MENU;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 800;
int TILE_WIDTH;
int TILE_HEIGHT;
int COLS;
int ROWS;
int MINES;

int flagCount = 0;

int startTime = 0;
int elapsedTime = 0;

int currentDifficulty = 0;

bool isGameOver = false;

int main(){
    InitWindow(800, 800, "Raylib:: Minesweeper");
    SetTargetFPS(60);
    GameStartUp();

    SetDifficulty(1);

    while (!WindowShouldClose()) {
        GameUpdate();

        BeginDrawing(); 
            GameRender();
        EndDrawing();
    }

    GameShutDown();
    CloseWindow();

    return 0;
}