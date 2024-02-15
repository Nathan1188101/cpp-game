#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 50;
const int PLAYER_SPEED = 5;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    gWindow = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    SDL_Quit();
}

void drawPlayer(int x, int y) {
    SDL_Rect playerRect = { x, y, PLAYER_WIDTH, PLAYER_HEIGHT };
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(gRenderer, &playerRect);
}

int main(int argc, char* args[]) {
    if (!init()) {
        return -1;
    }

    bool quit = false;
    SDL_Event e;
    int playerX = 0;
    int playerY = SCREEN_HEIGHT - PLAYER_HEIGHT;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        //retrieves current state of keyboard 
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            playerX -= PLAYER_SPEED;
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            playerX += PLAYER_SPEED;
        }

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);

        drawPlayer(playerX, playerY);

        SDL_RenderPresent(gRenderer);
    }

    close();
    return 0;
}