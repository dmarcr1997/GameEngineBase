//
// Created by mossy on 7/22/2025.
//

#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL_video.h>


class Game {
public:
    Game();

    bool Initialize();

    void RunLoop();

    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window* window;
    bool mIsRunning;
};



#endif //GAME_H
