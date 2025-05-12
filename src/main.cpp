#include <iostream>
#include <vector>
#include "game.h"

using std::vector;
using std::cout;

Texture2D texture_flag;
Texture2D texture_bomb;
Music music;
Sound sound0;
Sound sound1;
Sound sound2;
Sound sound3;
Sound soundFlag;
vector<vector<sTile>> grid(20, vector<sTile>(20));
GameState gameState = MAIN_MENU;
GameState PreviousGameState;

float masterVolume = 0.5f;
float musicVolume = 0.5f;
float sfxVolume = 0.5f;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 800;
int TILE_WIDTH;
int TILE_HEIGHT;
int COLS;
int ROWS;
int MINES;

int flagCount = 0;
int startTime = 0;
int elapsedTime = 0;
int currentDifficulty = 0;

int highScoreEasy = INT_MAX;
int highScoreMedium = INT_MAX;
int highScoreHard = INT_MAX;



int main(){
    cout << "Hello World!" << '\n';

    InitWindow(800, 800, "Raylib::Minesweeper");
    GameStartUp();

    while( !WindowShouldClose() ){
        GameUpdate();
        SetSoundVolume(sound0, sfxVolume);
        SetSoundVolume(sound1, sfxVolume);
        SetSoundVolume(sound2, sfxVolume);
        SetSoundVolume(sound3, sfxVolume);
        SetSoundVolume(soundFlag, sfxVolume);
        UpdateMusicStream(music);

        BeginDrawing(); 

            GameRender();

        EndDrawing();

    }

    GameShutDown();
    CloseWindow();

    return 0;
}