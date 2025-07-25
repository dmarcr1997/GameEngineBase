//
// Created by mossy on 7/22/2025.
//
#include<SDL3/SDL.h>
#include "Game.h"

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
}

void Game::UpdateGame() {
    SDL_Log("UPDATE GAME");
}

void Game::DrawWalls(const float thickness) {
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
    const int thickness = 15;
    SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 255, 255);
    SDL_RenderClear(this->mRenderer); //clear back buffer
    SDL_SetRenderDrawColor(this->mRenderer, 255, 255, 255, 255);
    DrawWalls(thickness);
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
    SDL_RenderFillRect(this->mRenderer, &ball);
    SDL_RenderFillRect(this->mRenderer, &paddle);
    SDL_RenderPresent(this->mRenderer); //swap front and back buffer
}
