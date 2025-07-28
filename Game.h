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

    void DrawWalls();

    void GenerateOutput();

    SDL_Window* window;
    SDL_Renderer* mRenderer;
    int mTicksCount;
    Vector2 mPaddlePosition;
    Vector2 mBallPosition;
    Vector2 mBallVel = {-200.0f, 235.0f };
    float thickness = 15;
    int mPaddleH;
    int mPaddleDir;
    bool mIsRunning;
};



#endif //GAME_H
