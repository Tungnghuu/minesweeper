#include "game.h"

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