#pragma once
#include "game_types.h"
#include "game_audio.h"
#include "game_render.h"
#include "game_logic.h"
#include "game_file.h"

void GameStartUp();
void GameUpdate();
void GameRender();
void GameShutDown();
void GameReset();
void GameSetDifficulty(int difficulty);