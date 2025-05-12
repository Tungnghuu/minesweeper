#pragma once
#include "game_types.h"

void ResetTiles();
void ResizeGrid();
void PlaceMine();
void FirstRevealSurround(int x, int y);
void ToggleFlag(int x, int y);
void RevealTile(int x, int y);
int CountNearbyMines(int x, int y);
bool isTileValid(int x, int y);
bool CheckWin();