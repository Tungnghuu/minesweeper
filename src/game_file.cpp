#include "../include/game_file.h"
#include "../include/game_types.h"
#include "../include/game_render.h"
#include "../include/game_audio.h"

using namespace std;

void LoadImage(){
    Image flag = LoadImage("images/flag.png");
    ImageResize(&flag, TILE_WIDTH - 10, TILE_HEIGHT - 10);
    texture_flag = LoadTextureFromImage(flag);
    UnloadImage(flag);

    Image bomb = LoadImage("images/bomb.png");
    ImageResize(&bomb, TILE_WIDTH, TILE_HEIGHT);
    texture_bomb = LoadTextureFromImage(bomb);
    UnloadImage(bomb);

}

void LoadSoundFX(){
    sound0 = LoadSound("sound/0.wav");
    sound1 = LoadSound("sound/1.wav");
    sound2 = LoadSound("sound/2.wav");
    sound3 = LoadSound("sound/3.wav");
    soundFlag = LoadSound("sound/flag.wav");

}

void UnloadSoundFX(){
    UnloadSound(sound0);
    UnloadSound(sound1);
    UnloadSound(sound2);
    UnloadSound(sound3);
    UnloadSound(soundFlag);
}

void SaveHighScores(){
    ofstream file("data/highscores.txt");
    if (file.is_open()) {
        file << highScoreEasy << '\n';
        file << highScoreMedium << '\n';
        file << highScoreHard << '\n';
        file.close();
    }

}

void LoadHighScores(){
    ifstream file("data/highscores.txt");
    if (file.is_open()) {
        file >> highScoreEasy;
        file >> highScoreMedium;
        file >> highScoreHard;
        file.close();
    }

}
