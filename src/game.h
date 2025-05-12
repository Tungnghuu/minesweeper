#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <fstream>
#include <string>
#include <vector>

#define LIGHT_GREEN Color {170, 215, 81, 255} 
#define DARK_GREEN Color {162, 209, 73, 255}
#define LIGHT_BROWN Color {215, 184, 153, 255}
#define DARK_BROWN Color {229, 194, 159, 255}
#define DARKER_GREEN Color {74, 117, 44, 255}

enum GameState {
    MAIN_MENU,
    CHOOSING_DIFFICULTY,
    FIRST_REVEAL,
    PLAYING,
    SETTING,
    GAME_OVER,
    WON
};
extern GameState gameState;
extern GameState PreviousGameState;

typedef struct{
    int x;
    int y;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int nearbyMineCount;
    bool first_reveal;
} sTile;
extern std::vector<std::vector<sTile>> grid;

extern int currentDifficulty;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int COLS;
extern int ROWS;
extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern int MINES;
extern int flagCount;

extern Texture2D texture_flag;
extern Texture2D texture_bomb;
extern Music music;
extern Sound sound0;
extern Sound sound1;
extern Sound sound2;
extern Sound sound3;
extern Sound soundFlag;

extern int dx[];
extern int dy[];
extern int startTime;
extern int elapsedTime;

extern int highScoreEasy;
extern int highScoreMedium;
extern int highScoreHard;

extern float masterVolume;
extern float musicVolume;
extern float sfxVolume;

void GameStartUp();
void GameUpdate();
void GameRender();
void GameShutDown();
void GameReset();
void GameSetDifficulty(int difficulty);

void ResetTiles();
void ResizeGrid();
void PlaceMine();
void FirstRevealSurround(int x, int y);
void ToggleFlag(int x, int y);
void RevealTile(int x, int y);
int CountNearbyMines(int x, int y);
bool isTileValid(int x, int y);
bool CheckWin();

void RenderTile(sTile tile);
void RenderTiles();
void RenderBoard();
void RenderMainMenu();
void RenderGameOver();
void RenderWin();
void RenderDifficultyMenu(int x, int y);
void RenderUI();
void countFlag();
void RenderSetting();

void LoadImage();
void SaveHighScores();
void LoadHighScores();
void LoadSoundFX();
void UnloadSoundFX();

#endif