#include "game.h"

void ResetTiles(){
    for (int i = 0; i < COLS; i++) {
        for(int j = 0; j < ROWS; j++) {
            grid[i][j] = (sTile){
                .x = i,
                .y = j,
                .isMine = false,
                .isRevealed = false,
                .isFlagged = false,
                .nearbyMineCount = -1,
                .first_reveal = false,
            };
        }
    }
    return;
}

void ResizeGrid(){
    grid.resize(ROWS);
    for (int i = 0; i < ROWS; i++) {
        grid[i].resize(COLS);
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = {i, j, false, false, false, -1, false};
        }
    }
}

void firstRevealSurround(int x, int y){
    grid[x][y].first_reveal = true;

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < COLS && ny < ROWS) {
            grid[nx][ny].first_reveal = true;
        }
    }
    return;
}

void placeMine(){
    int count = 0;

    while (count++ < MINES) {
        int x = GetRandomValue(0, COLS - 1);
        int y = GetRandomValue(0, ROWS - 1);
        if (!(grid[x][y].isMine) && !grid[x][y].first_reveal) {
            grid[x][y].isMine = true;
        }
    }

    for (int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
            if (!grid[i][j].isMine){
                grid[i][j].nearbyMineCount = CountNearbyMines(i, j);
            }
        }
    }
    return;
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
    return (x >= 0 && x < COLS && y >= 0 && y < ROWS);
}

void RevealTile(int x, int y){
    if(grid[x][y].isFlagged || grid[x][y].isRevealed) {
        if (grid[x][y].isFlagged && grid[x][y].nearbyMineCount == 0){
            grid[x][y].isFlagged = false;
            RevealTile(x,y);
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
        return;
    }

    if(grid[x][y].isMine){
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
        isGameOver = true;
        return;
    }
    return;
}

void ToggleFlag(int x, int y){
    if (grid[x][y].isRevealed){
        return;
    }

    grid[x][y].isFlagged = !grid[x][y].isFlagged;

    return;
}

bool CheckWin(){
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (!grid[i][j].isMine && !grid[i][j].isRevealed) {
                return false;
            }
        }
    }
    return true;
}

void SetDifficulty(int difficulty){
    switch (difficulty){
        case 0:                 // Easy
            SCREEN_WIDTH = 400;
            SCREEN_HEIGHT = 400;
            TILE_WIDTH = 40;
            TILE_HEIGHT = 40;
            COLS = 10;
            ROWS = 10;
            MINES = 10;
            break;
        case 1:                 // Medium
            SCREEN_WIDTH = 600;
            SCREEN_HEIGHT = 600;
            TILE_WIDTH = 30;
            TILE_HEIGHT = 30;
            COLS = 20;
            ROWS = 20;
            MINES = 40;
            break;
        case 2:                 // Hard
            SCREEN_WIDTH = 900;
            SCREEN_HEIGHT = 900;
            TILE_WIDTH = 30;
            TILE_HEIGHT = 30;
            COLS = 30;
            ROWS = 30;
            MINES = 150;
            break;
    }
    currentDifficulty = difficulty;
    ResizeGrid();
    GameReset(); 
}

void countFlag(){
    int sum = 0;
    flagCount = MINES;
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (grid[i][j].isFlagged) {
                sum++;
            }
        }
    }
    flagCount -= sum;
}
