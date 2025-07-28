//
// Created by mossy on 7/22/2025.
//
#include<SDL3/SDL.h>
#include "Game.h"

#include <cmath>

Game::Game() {
    this->window = nullptr;
    this->mIsRunning = false;
    this->mPaddlePosition = Vector2(0, 300);
    this->mBallPosition = Vector2(400, 300);
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
    if (keys[SDL_SCANCODE_W])
        mPaddleDir -= 1;
    if (keys[SDL_SCANCODE_S])
        mPaddleDir += 1;

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
    mBallPosition.x += mBallVel.x * deltaTime;
    mBallPosition.y += mBallVel.y * deltaTime;
    if (mBallPosition.y <= (thickness + thickness) && mBallVel.y < 0.0f) {
        mBallVel.y *= -1;
    }
    if (mBallPosition.y >= 600 && mBallVel.y > 0.0f) {
        mBallVel.y *= -1;
    }

    if (mBallPosition.x >= 800 && mBallVel.x > 0.0f) {
        mBallVel.x *= -1;
    }

    float diff = std::abs(mBallPosition.y  - mPaddlePosition.y);
    if (
        diff <= mPaddleH / 2.0f &&
        mBallPosition.x <= 25.0f && mBallPosition.x >= 20.0f &&
        mBallVel.x < 0.0f
    ) {
        mBallVel.x *= -1;
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

    SDL_FRect rightWall {
        800 - thickness,
        0,
        thickness,
        600
    };
    SDL_RenderFillRect(this->mRenderer, &topWall);
    SDL_RenderFillRect(this->mRenderer, &bottomWall);
    SDL_RenderFillRect(this->mRenderer, &rightWall);
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 255, 255);
    SDL_RenderClear(this->mRenderer); //clear back buffer
    SDL_SetRenderDrawColor(this->mRenderer, 255, 255, 255, 255);
    DrawWalls();
    SDL_FRect ball {
        this->mBallPosition.x - thickness/2,
        this->mBallPosition.y - thickness/2,
        thickness,
        thickness
    };
    SDL_FRect paddle {
        this->mPaddlePosition.x + thickness/2,
        this->mPaddlePosition.y - thickness*2,
        thickness,
        thickness * 4
    };
    this->mPaddleH = thickness * 4;
    SDL_RenderFillRect(this->mRenderer, &ball);
    SDL_RenderFillRect(this->mRenderer, &paddle);
    SDL_RenderPresent(this->mRenderer); //swap front and back buffer
}
