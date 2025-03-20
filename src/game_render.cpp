#include "game.h"


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

    Color MineColors[] = {
        {0, 0, 0, 255},
        {20, 150, 60, 255},     // 1 - Dark Green
        {30, 70, 180, 255},     // 2 - Dark Blue
        {40, 160, 160, 255},    // 3 - Teal
        {200, 180, 40, 255},    // 4 - Golden Yellow
        {200, 100, 20, 255},    // 5 - Burnt Orange
        {180, 40, 40, 255},     // 6 - Deep Red
        {100, 30, 120, 255},    // 7 - Dark Purple
        {180, 40, 140, 255}     // 8 - Deep Magenta
    };

    if(tile.isRevealed){

        if(tile.isMine) {

            DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, RED);
            DrawTexture(texture_bomb, tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, WHITE);

        } 
        else {
            if (((tile.x + tile.y) % 2 == 0)){

                if (tile.nearbyMineCount > 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, 
                        tile.y * TILE_HEIGHT, 
                        TILE_WIDTH, 
                        TILE_HEIGHT, 
                        DARK_BROWN
                    );
                    DrawText(
                        TextFormat("%d", tile.nearbyMineCount),
                        tile.x * TILE_WIDTH + 14, 
                        tile.y * TILE_HEIGHT + 5, 
                        TILE_HEIGHT - 4, 
                        MineColors[tile.nearbyMineCount]
                    );
                } 
                if (tile.nearbyMineCount == 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, 
                        tile.y * TILE_HEIGHT, 
                        TILE_WIDTH, 
                        TILE_HEIGHT, 
                        DARK_BROWN
                    );
                }

            } 
            else {
                if (tile.nearbyMineCount > 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, 
                        tile.y * TILE_HEIGHT, 
                        TILE_WIDTH, 
                        TILE_HEIGHT, 
                        LIGHT_BROWN
                    );
                    DrawText(
                        TextFormat("%d", tile.nearbyMineCount),
                        tile.x * TILE_WIDTH + 14, 
                        tile.y * TILE_HEIGHT + 5, 
                        TILE_HEIGHT - 4, 
                        MineColors[tile.nearbyMineCount]
                    );
                } 
                if (tile.nearbyMineCount == 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, 
                        tile.y * TILE_HEIGHT, 
                        TILE_WIDTH, 
                        TILE_HEIGHT, 
                        LIGHT_BROWN
                    );
                }

            }
        }
    } 
    if (tile.isFlagged){
        DrawTexture(texture_flag, tile.x * TILE_WIDTH + 5,
            tile.y * TILE_HEIGHT + 5, 
            WHITE
        );
    }  
    if (tile.x == hoverCol && tile.y == hoverRow) {
        DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT,
            TILE_WIDTH, TILE_HEIGHT,
            Color{255, 255, 255, 100}
        );
    }


}


void RenderBoard(){
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            Color tileColor = ((row + col) % 2 == 0) ? LIGHT_GREEN : DARK_GREEN;
            DrawRectangle(col * TILE_WIDTH, row * TILE_HEIGHT, 
                TILE_WIDTH, 
                TILE_HEIGHT, 
                tileColor
            );
        }
    }
}

void RenderGameOver(){
    if (isGameOver) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{0, 0, 0, 100});
        DrawText("Game Over!", 
            SCREEN_WIDTH / 2 - MeasureText("Game Over!", 40) / 2,
            SCREEN_HEIGHT / 2 - 20,
            40,
            RED
        );
        DrawText("Press Any Key to return to Main Menu",
            SCREEN_WIDTH / 2 - MeasureText("Press Any Key to return to Main Menu", 20) / 2,
            SCREEN_HEIGHT / 2 + 20, 
            20, 
            RED
        );
    }
}

void RenderMainMenu() {
    ClearBackground(LIGHT_GREEN);
    DrawText("Minesweeper", 
        SCREEN_WIDTH / 2 - MeasureText("Minesweeper", 40) / 2, 
        SCREEN_HEIGHT / 2 - 60, 
        40, 
        DARKGRAY
    );
    DrawText("Press Any Key to Start", 
        SCREEN_WIDTH / 2 - MeasureText("Press Any Key to Start", 20) / 2, 
        SCREEN_HEIGHT / 2, 
        20, 
        DARKGRAY
    );
}
void RenderWin()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{0, 0, 0, 100});
    DrawText("You Win!",
        SCREEN_WIDTH / 2 - MeasureText("You Win!", 40) / 2,
        SCREEN_HEIGHT / 2 - 20,
        40,
        GREEN
    );
    DrawText("Press Any Key to return to Main Menu",
        SCREEN_WIDTH / 2 - MeasureText("Press Any Key to return to Main Menu", 20) / 2,
        SCREEN_HEIGHT / 2 + 20, 20, GREEN
    );
}