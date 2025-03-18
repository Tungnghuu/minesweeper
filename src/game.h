#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define COLS 20
#define ROWS 20

#define LIGHT_GREEN Color{170, 215, 81, 255} 
#define DARK_GREEN Color{162, 209, 73, 255}
#define LIGHT_BROWN Color{215, 184, 153, 255}
#define DARK_BROWN Color{229, 194, 159, 255}

const int TILE_WIDTH = 40;
const int TILE_HEIGHT = 40;
const int MINES = 60;

typedef struct {
    int x;
    int y;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int nearbyMineCount;
} sTile;

extern sTile grid[COLS][ROWS];
extern bool isGameOver;
extern Texture2D texture_flag;
extern Texture2D texture_bomb;
extern int dx[];
extern int dy[];

enum GameState {
    MAIN_MENU,
    PLAYING,
    GAME_OVER
};
extern GameState gameState;

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

#endif // GAME_H