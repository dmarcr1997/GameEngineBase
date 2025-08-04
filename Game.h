//
// Created by mossy on 7/22/2025.
//

#ifndef GAME_H
#define GAME_H
#include <vector>

class SDL_Window;
class SDL_Renderer;

struct Vector2 {
    float x;
    float y;
};

struct Ball {
    Vector2 mBallPosition;
    Vector2 mBallVel;
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

    void DrawBalls();

    void DrawPaddles();

    void GenerateOutput();

    SDL_Window* window;
    SDL_Renderer* mRenderer;
    int mTicksCount;
    Vector2 mPaddlePosition;
    Vector2 mOPaddlePosition;
    std::vector<Ball> mBallCollection;
    Vector2 mBallSpawnPoint = { 400, 300};
    int mBallCount = 3;
    float thickness = 15;
    int mPaddleH;
    int mPaddleDir;
    int mOPaddleDir;
    bool mIsRunning;
};



#endif //GAME_H
