//
// Created by mossy on 7/22/2025.
//
#include<SDL3/SDL.h>
#include "Game.h"

Game::Game() {
    this->window = nullptr;
    this->mIsRunning = false;
}

bool Game::Initialize() {
    this->window = SDL_CreateWindow("SDL3 Window", 800, 600, 0);
    if (!window) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
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

void Game::GenerateOutput() {
    SDL_Log("GENERATE OUTPUT");
    SDL_Log("GAME END");
    // this->mIsRunning = false;
}
