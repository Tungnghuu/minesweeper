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
        {0, 0, 0, 255},         // 0 - BLANK (index start from 1)
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
        if(tile.isMine){
            DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, RED);
            DrawTexture(texture_bomb, tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, WHITE);
        } 
        else {
            if( (tile.x + tile.y) % 2 == 0 ){
                if(tile.nearbyMineCount > 0) {
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
                if(tile.nearbyMineCount == 0) {
                    DrawRectangle(tile.x * TILE_WIDTH, 
                        tile.y * TILE_HEIGHT, 
                        TILE_WIDTH, 
                        TILE_HEIGHT, 
                        DARK_BROWN
                    );
                }
            }
            else {
                if(tile.nearbyMineCount > 0){
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
                if(tile.nearbyMineCount == 0){
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

    if(tile.isFlagged){
        DrawTexture(texture_flag, tile.x * TILE_WIDTH + 5, tile.y * TILE_HEIGHT + 5, WHITE);
    }

    if(tile.x == hoverCol && tile.y == hoverRow) {
        DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, Color{255, 255, 255, 100});
    }

}

void RenderBoard(){
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            Color tileColor = ((row + col) % 2 == 0) ? LIGHT_GREEN : DARK_GREEN;
            DrawRectangle(col * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, tileColor);
        }
    }

}

void RenderGameOver(){
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 50, Color{0, 0, 0, 100});
    int titleFontSize = SCREEN_HEIGHT * 0.1;
    int textFontSize = SCREEN_HEIGHT * 0.04;
    
    DrawText("Game Over!", 
        SCREEN_WIDTH / 2 - MeasureText("Game Over!", titleFontSize) / 2,
        SCREEN_HEIGHT / 2 - titleFontSize - 20,
        titleFontSize,
        RED
    );
    DrawText("Press Any Key to return to Main Menu",
        SCREEN_WIDTH / 2 - MeasureText("Press Any Key to return to Main Menu", textFontSize) / 2,
        SCREEN_HEIGHT / 2,
        textFontSize,
        RED
    );

}

void RenderMainMenu(){
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, LIGHT_GREEN);

    DrawText("Minesweeper", 
        SCREEN_WIDTH / 2 - MeasureText("Minesweeper", 40) / 2, 
        SCREEN_HEIGHT / 2 - 60, 
        40, 
        DARKGRAY
    );
    DrawText("Press ENTER to Start", 
        SCREEN_WIDTH / 2 - MeasureText("Press ENTER to Start", 20) / 2, 
        SCREEN_HEIGHT / 2, 
        20, 
        DARKGRAY
    );

}

void RenderWin(){
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 50, Color{0, 0, 0, 100});
    int titleFontSize = SCREEN_HEIGHT * 0.1;
    int textFontSize = SCREEN_HEIGHT * 0.04;

    DrawText("You Win!",
        SCREEN_WIDTH / 2 - MeasureText("You Win!", titleFontSize) / 2,
        SCREEN_HEIGHT / 2 - titleFontSize - 20,
        titleFontSize,
        GREEN
    );
    DrawText("Press Any Key to return to Main Menu",
        SCREEN_WIDTH / 2 - MeasureText("Press Any Key to return to Main Menu", textFontSize) / 2,
        SCREEN_HEIGHT / 2,
        textFontSize,
        GREEN
    );

}

void RenderDifficultyMenu(int x, int y){
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, LIGHT_GREEN);

    const char* options[] = {"Easy", "Medium", "Hard"};
    int optionCount = 3;
    int fontSize = 30;
    int spacing = 50;

    for(int i = 0; i < optionCount; i++){
        int textWidth = MeasureText(options[i], fontSize);
        int textX = SCREEN_WIDTH / 2 - textWidth / 2;
        int textY = SCREEN_HEIGHT / 2 - (optionCount * spacing) / 2 + i * spacing;

        bool isHovered = x >= textX && x <= textX + textWidth && y >= textY && y <= textY + fontSize;

        Color textColor = (isHovered) ? YELLOW : DARKGRAY;
        DrawText(
            options[i],
            textX,
            textY,
            fontSize,
            textColor
        );
    }
    DrawText(
        "Select Difficulty",
        SCREEN_WIDTH / 2 - MeasureText("Select Difficulty", 40) / 2,
        SCREEN_HEIGHT / 2 - (optionCount * spacing) / 2 - 60,
        40,
        DARKGRAY
    );

}

void RenderUI(){
    countFlag();

    char flagText[50];
    sprintf(flagText,": %d", flagCount);

    char timerText[50];
    sprintf(timerText, "Time: %03d", elapsedTime);

    char highScoreText[50];
    int HighScores[] = {highScoreEasy, highScoreMedium, highScoreHard};

    if(HighScores[currentDifficulty] == INT_MAX){
        sprintf(highScoreText, "High Score: --");
    } else {
        sprintf(highScoreText, "High Score: %03d", HighScores[currentDifficulty]);
    }

    DrawRectangle(
        0,
        SCREEN_HEIGHT,
        SCREEN_WIDTH,
        50,
        DARKER_GREEN
    );
    
    DrawTexture(
        texture_flag,
        20,
        SCREEN_HEIGHT + 10,
        WHITE
    );
    
    DrawText(
        flagText,
        60,
        SCREEN_HEIGHT + 15,
        20,
        RAYWHITE
    );

    DrawText(
        timerText,
        SCREEN_WIDTH - 100,
        SCREEN_HEIGHT + 15,
        20,
        RAYWHITE
    );

    DrawText(
        highScoreText,
        SCREEN_WIDTH / 2 - MeasureText(highScoreText, 20) / 2,
        SCREEN_HEIGHT + 15,
        20,
        RAYWHITE
    );
}

void countFlag(){
    int sum = 0;
    flagCount = MINES;
    
    for(int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
            if(grid[i][j].isFlagged){
                sum++;
            }
        }
    }
    flagCount -= sum;

}

void RenderSetting(){
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{0, 0, 0, 150});

    int rectWidth = 300;
    int rectHeight = 350;
    int rectX = (SCREEN_WIDTH - rectWidth) / 2;
    int rectY = (SCREEN_HEIGHT - rectHeight) / 2;

    DrawRectangle(rectX, rectY, rectWidth, rectHeight, DARK_BROWN);
    DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, RAYWHITE);

    DrawText("Settings", 
        rectX + rectWidth / 2 - MeasureText("Settings", 30) / 2, 
        rectY + 20, 
        30, 
        RAYWHITE
    );

    const char *labels[] = {"Master Volume:", "Music Volume:", "SFX Volume:"};
    float *volumes[] = {&masterVolume, &musicVolume, &sfxVolume};
    int sliderWidth = 200;
    int sliderHeight = 20;
    int sliderYStart = rectY + 80;
    int sliderSpacing = 70;

    for (int i = 0; i < 3; i++) {
        DrawText(labels[i], 
            rectX + 20, 
            sliderYStart + i * sliderSpacing - 20, 
            20, 
            RAYWHITE
        );

        int sliderX = rectX + 50;
        int sliderY = sliderYStart + i * sliderSpacing;
        DrawRectangle(sliderX, sliderY, sliderWidth, sliderHeight, DARKER_GREEN);

        DrawRectangle(sliderX, sliderY, (int)(sliderWidth * (*volumes[i])), sliderHeight, LIGHT_GREEN);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            if (mousePos.x >= sliderX && mousePos.x <= sliderX + sliderWidth &&
                mousePos.y >= sliderY && mousePos.y <= sliderY + sliderHeight) {
                *volumes[i] = (mousePos.x - sliderX) / (float)sliderWidth;

                if (i == 0) SetMasterVolume(*volumes[i]); // Master Volume
                else if (i == 1) SetMusicVolume(music, *volumes[i]); // Music Volume
            }
        }

        char volumeText[20];
        sprintf(volumeText, "%d%%", (int)(*volumes[i] * 100));
        DrawText(volumeText, sliderX + sliderWidth + 10, sliderY, 17, RAYWHITE);
    }

    const char* quitText = "Quit to Main Menu";
    int quitTextWidth = MeasureText(quitText, 20);
    int quitTextX = rectX + rectWidth / 2 - quitTextWidth / 2;
    int quitTextY = sliderYStart + 3 * sliderSpacing;

    DrawText(quitText, quitTextX, quitTextY, 20, RAYWHITE);

    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        mousePos.x >= quitTextX && mousePos.x <= quitTextX + quitTextWidth &&
        mousePos.y >= quitTextY && mousePos.y <= quitTextY + 20) {
        gameState = MAIN_MENU;
    }
}
