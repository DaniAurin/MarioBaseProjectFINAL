
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>
#include <string>
#include "GameScreenManager.h"
//globals
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
//functions
bool InitSDL();
int ExitSDL();
void Render();
bool Update();
int main(int argc, char* args[])
{
    if (InitSDL()) {
        game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
        g_old_time = SDL_GetTicks();
        bool quit = false;
        while (!quit) {
            Render();
            quit = Update();
        }
    }
    ExitSDL();
    return 0;
}
bool InitSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize. Error: " << SDL_GetError();
        return false;
    }
    else {
        g_window = SDL_CreateWindow("Mario SDL",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        if (g_window == nullptr) {
            std::cout << "SDL window was not created. Error: " << SDL_GetError();
            return false;
        }
    }
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer != nullptr) {
        int imageFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imageFlags) & imageFlags)) {
            std::cout << "SDL image could not initialize. Error: " << IMG_GetError();
            return false;
        }
    }
    else {
        std::cout << "Renderer could not initialize. Error: " << SDL_GetError();
        return false;
    }

    return true;
}
int ExitSDL()
{
    delete game_screen_manager;
    game_screen_manager = nullptr;
    SDL_DestroyWindow(g_window);
    g_window = nullptr;
    IMG_Quit();
    SDL_Quit();
    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;
    return 0;
}

void Render()
{
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(g_renderer);
    game_screen_manager->Render();
    SDL_RenderPresent(g_renderer);
}





bool Update()
{
    Uint32 new_time = SDL_GetTicks();
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type) {
    case SDL_QUIT:
        return true;
        break;
    }
    game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
    g_old_time = new_time;
    return false;
}
