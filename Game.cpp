//
// Created by mossy on 7/22/2025.
//
#include<SDL3/SDL.h>
#include "Game.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

Game::Game() {
    this->window = nullptr;
    this->mIsRunning = false;
    this->mPaddlePosition = Vector2(0, 300);
    this->mOPaddlePosition = Vector2(810, 300);
}

bool Game::Initialize() {
    this->window = SDL_CreateWindow("SDL3 Window", 800, 600, 0);
    if (!window) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return false;
    }
    this->mRenderer = SDL_CreateRenderer(
        window,
        NULL
        );
    if (!this->mRenderer) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        return false;
    }
    std::srand(static_cast<unsigned int>(std::time(nullptr))); //seed rand stream

    for (int i = 0; i < mBallCount; ++i) {
        float vx = static_cast<float>((std::rand() % 400) - 200);
        float vy = static_cast<float>((std::rand() % 400) - 200);
        mBallCollection.push_back(Ball{mBallSpawnPoint, Vector2(vx, vy)});
    }

    this->mIsRunning = true;
    return true;
}

void Game::RunLoop() {
    while (this->mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown() {
    SDL_DestroyRenderer(this->mRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                this->mIsRunning = false;
                break;
        }
    }
    const bool* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_ESCAPE]) {
        this->mIsRunning = false;
    }
    this->mPaddleDir = 0;
    this->mOPaddleDir = 0;
    if (keys[SDL_SCANCODE_W])
        mPaddleDir -= 1;
    if (keys[SDL_SCANCODE_S])
        mPaddleDir += 1;
    if (keys[SDL_SCANCODE_I])
        mOPaddleDir -= 1;
    if (keys[SDL_SCANCODE_K])
        mOPaddleDir += 1;

}

void Game::UpdateGame() {
    Uint64 targetTicks = SDL_GetTicks() + 16;
    while (SDL_GetTicks() < targetTicks);
    float deltaTime = (SDL_GetTicks() - this->mTicksCount) / 1000.0f;
    this->mTicksCount = SDL_GetTicks();

    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    if (this->mPaddleDir != 0) {
        mPaddlePosition.y += mPaddleDir * 300.0f * deltaTime;
        if (mPaddlePosition.y < (mPaddleH/2.0f + thickness)) {
            mPaddlePosition.y = mPaddleH/2.0f + thickness;
        } else if (mPaddlePosition.y > (600 - mPaddleH/2.0f - thickness)) {
            mPaddlePosition.y = (600 - mPaddleH/2.0f - thickness);
        }
    }
    if (this->mOPaddleDir != 0) {
        mOPaddlePosition.y += mOPaddleDir * 300.0f * deltaTime;
        if (mOPaddlePosition.y < (mPaddleH/2.0f + thickness)) {
            mOPaddlePosition.y = mPaddleH/2.0f + thickness;
        } else if (mOPaddlePosition.y > (600 - mPaddleH/2.0f - thickness)) {
            mOPaddlePosition.y = (600 - mPaddleH/2.0f - thickness);
        }
    }
    for (auto& ball : mBallCollection) {
        ball.mBallPosition.x += ball.mBallVel.x * deltaTime;
        ball.mBallPosition.y += ball.mBallVel.y * deltaTime;
        if (ball.mBallPosition.y <= (thickness + thickness) && ball.mBallVel.y < 0.0f) {
            ball.mBallVel.y *= -1;
        }
        if (ball.mBallPosition.y >= 600 && ball.mBallVel.y > 0.0f) {
            ball.mBallVel.y *= -1;
        }

        float diffR = std::abs(ball.mBallPosition.y - mOPaddlePosition.y);
        if (diffR <= mPaddleH / 2.0 &&
            ball.mBallPosition.x >= 775.0f && ball.mBallPosition.x <= 780.0f &&
            ball.mBallVel.x > 0.0f) {
            ball.mBallVel.x *= -1;
            }

        float diffL = std::abs(ball.mBallPosition.y  - mPaddlePosition.y);
        if (
            diffL <= mPaddleH / 2.0f &&
            ball.mBallPosition.x <= 25.0f && ball.mBallPosition.x >= 20.0f &&
            ball.mBallVel.x < 0.0f
        ) {
            ball.mBallVel.x *= -1;
        }
        else if (ball.mBallPosition.x <= 0.0f || ball.mBallPosition.x >= 800.0f) {
            ball.mBallPosition = Vector2(400, 300);
        }
    }

}

void Game::DrawWalls() {
    SDL_FRect topWall {
        0,
        0,
        1024,
        thickness
    };

    SDL_FRect bottomWall {
        0,
        600 - thickness,
        1024,
        thickness
    };

    SDL_RenderFillRect(this->mRenderer, &topWall);
    SDL_RenderFillRect(this->mRenderer, &bottomWall);
}

void Game::DrawBalls() {
    for (auto& ball : mBallCollection) {
        SDL_FRect rect {
            ball.mBallPosition.x - thickness/2,
            ball.mBallPosition.y - thickness/2,
            thickness,
            thickness
        };
        SDL_RenderFillRect(this->mRenderer, &rect);
    }
}

void Game::DrawPaddles() {
    SDL_FRect paddle {
        this->mPaddlePosition.x + thickness/2,
        this->mPaddlePosition.y - thickness*2,
        thickness,
        thickness * 4
    };
    SDL_FRect oPaddle {
        this->mOPaddlePosition.x - thickness*2,
        this->mOPaddlePosition.y - thickness*2,
        thickness,
        thickness * 4
    };
    this->mPaddleH = thickness * 4;
    SDL_RenderFillRect(this->mRenderer, &paddle);
    SDL_RenderFillRect(this->mRenderer, &oPaddle);
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 255, 255);
    SDL_RenderClear(this->mRenderer); //clear back buffer
    SDL_SetRenderDrawColor(this->mRenderer, 255, 255, 255, 255);
    DrawWalls();
    DrawBalls();
    DrawPaddles();
    SDL_RenderPresent(this->mRenderer); //swap front and back buffer
}
