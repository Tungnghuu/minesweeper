#pragma once
#include <raylib.h>
#include "game_types.h"

#define LIGHT_GREEN Color {170, 215, 81, 255} 
#define DARK_GREEN Color {162, 209, 73, 255}
#define LIGHT_BROWN Color {215, 184, 153, 255}
#define DARK_BROWN Color {229, 194, 159, 255}
#define DARKER_GREEN Color {74, 117, 44, 255}

extern Texture2D texture_flag;
extern Texture2D texture_bomb;

void RenderTile(sTile tile);
void RenderTiles();
void RenderBoard();
void RenderMainMenu();
void RenderGameOver();
void RenderWin();
void RenderDifficultyMenu(int x, int y);
void RenderUI();
void RenderSetting();
void countFlag();