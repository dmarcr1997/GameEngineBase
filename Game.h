//
// Created by mossy on 7/22/2025.
//

#ifndef GAME_H
#define GAME_H


class SDL_Window;
class SDL_Renderer;

struct Vector2 {
    float x;
    float y;
};

class Game {
public:
    Game();

    bool Initialize();

    void RunLoop();

    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame();

    void DrawWalls(float thickness);

    void GenerateOutput();

    SDL_Window* window;
    SDL_Renderer* mRenderer;
    Vector2 mPaddlePosition;
    Vector2 mBallPosition;
    bool mIsRunning;
};



#endif //GAME_H
