#include <iostream>
#include "game.h"

using namespace std;

Texture2D texture_flag;
Texture2D texture_bomb;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool isGameOver = false;

sTile grid[COLS][ROWS];

GameState gameState = MAIN_MENU;

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