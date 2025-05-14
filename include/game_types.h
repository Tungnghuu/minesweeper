#pragma once
#include <raylib.h>
#include <string>
#include <vector>

enum GameState {
    MAIN_MENU,
    CHOOSING_DIFFICULTY,
    FIRST_REVEAL,
    PLAYING,
    SETTING,
    GAME_OVER,
    WON
};

typedef struct {
    int x;
    int y;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int nearbyMineCount;
    bool first_reveal;
} sTile;

extern GameState gameState;
extern GameState PreviousGameState;
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

extern int dx[];
extern int dy[];

extern int highScoreEasy;
extern int highScoreMedium;
extern int highScoreHard;

extern int startTime;
extern int elapsedTime;