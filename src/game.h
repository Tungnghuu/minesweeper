#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <string>
#include <vector>

#define LIGHT_GREEN Color {170, 215, 81, 255} 
#define DARK_GREEN Color {162, 209, 73, 255}
#define LIGHT_BROWN Color {215, 184, 153, 255}
#define DARK_BROWN Color {229, 194, 159, 255}
#define DARK_YELLOW Color {74, 117, 44, 255}

typedef struct{
    int x;
    int y;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int nearbyMineCount;
    bool first_reveal;
} sTile;

extern int currentDifficulty;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int COLS;
extern int ROWS;
extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern int MINES;
extern int flagCount;
extern std::vector<std::vector<sTile>> grid;

extern bool isGameOver;
extern Texture2D texture_flag;
extern Texture2D texture_bomb;
extern int dx[];
extern int dy[];
extern int startTime;
extern int elapsedTime;

extern int highScoreEasy;
extern int highScoreMedium;
extern int highScoreHard;

enum GameState {
    MAIN_MENU,
    CHOOSING_DIFFICULTY,
    FIRST_REVEAL,
    PLAYING,
    GAME_OVER,
    WON
};

extern GameState gameState;

void RenderDifficultyMenu(int x, int y);
void firstRevealSurround(int x, int y);
void placeMine();
void LoadImage();
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
bool CheckWin();
void RenderWin();
void ResizeGrid();
void SetDifficulty(int difficulty);
void RenderDifficultyMenu(int x, int y);
void RenderUI();
void countFlag();

void SaveHighScores();
void LoadHighScores();

#endif