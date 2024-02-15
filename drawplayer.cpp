#include <iostream> 
#include <SDL2/SDL.h>

using namespace std;

const int WIDTH = 800, HEIGHT = 600;
const int Player_Height = 20; 
const int Player_Width = 20; 

SDL_Window* window = nullptr; 
SDL_Renderer* renderer = nullptr; 

//initializing windows and rendering 
bool init(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        //if initialization fails return false
        return false; 
    }

    //creating and defining the window
    window = SDL_CreateWindow(
        "Draw Character",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (window == nullptr) {
        return false;
    }

 /**
     * Good note about the rendering flags: 
     *  
     * owever, you can specify flags to control rendering behavior, such as enabling hardware acceleration (SDL_RENDERER_ACCELERATED),
     *  enabling vsync (SDL_RENDERER_PRESENTVSYNC),
     *  or allowing rendering to a texture (SDL_RENDERER_TARGETTEXTURE).
     *  By bitwise ORing these flags together, you can combine multiple flags if needed.
     * 
    */
   //This rendering library allows us to render 2d graphics! (so to show something in the window we need to render it)
    renderer = SDL_CreateRenderer(window, -1, 0);//-1 parameter indicates that the first available rendering driver should be used
                                                //in the 0 position is where we indicate additional rendering flags, 0 indicates NO additional flags are used
    if(renderer == nullptr)
    {
        return false; 
    }

    //setting screen bounds 
    SDL_Rect screenBounds; 
    SDL_GetDisplayUsableBounds(0, &screenBounds);
    int screenWidth = screenBounds.w; 
    int screenHeight = screenBounds.h; 

    return true; 

}

//need to set up a close function for the window, it's not a default thing
void close(){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window); //destroy from memory
    renderer = nullptr; //pointing render back to null
    window = nullptr; //pointing window back to null

    SDL_Quit(); 

}

void drawPlayer(int x, int y){         //position x and y, then player hitbox(?) dimensions
    SDL_Rect playerRect = {x, y, Player_Width, Player_Height};
    //setting color
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);

}

void restrictPlayer(int& x, int& y){

    if(x < 0)
    {
         x = 0; 
    }
    if(y < 0)
    {
        y = 0; 
    }
    if(x > )


}

int main(int argc, char *argv[]){

    //SDL_Event is used to represent events that occur in the program, like user input events (keyboard and mouse), window events (resizing, closing)
    SDL_Event windowEvent; 
    int playerX = 0;
    int playerY = HEIGHT - Player_Height;
    bool quit = false;

    //initializing SDL libraries
    //SDL_Init(SDL_INIT_EVERYTHING); 

    init(); 

  

    //set render draw color to red 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
    SDL_RenderClear(renderer); // this will clear the display and draw its new color we set above

    //common to first draw objects and then present
    drawPlayer(playerX, playerY);
    SDL_RenderPresent(renderer); 

    while(!quit)
    {
        while(SDL_PollEvent(&windowEvent))
        {
            if(SDL_QUIT == windowEvent.type)
                {
                    quit = true;
                }
        }

        //player control (common to use this Uint8 data type (that represents an 8-bit unsigned integer) for keyboard strokes)
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if(currentKeyStates[SDL_SCANCODE_D]) //currentKeyStates is a pointer, checking if d key has been pressed
        {
            playerX += 1;
        }
        if(currentKeyStates[SDL_SCANCODE_A]) //checking if A key has been pressed
        {
            playerX -= 1;
        }
         if(currentKeyStates[SDL_SCANCODE_W]) //checking if A key has been pressed
        {
            playerY -= 1;
        }
        if(currentKeyStates[SDL_SCANCODE_S]) //checking if A key has been pressed
        {
            playerY += 1;
        }

        restrictPlayer(playerX, playerY); 
     
        //set render draw color to red 
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderClear(renderer); // this will clear the display and draw its new color we set above

        //common to first draw objects and then present
        drawPlayer(playerX, playerY);
        SDL_RenderPresent(renderer); 

    }



    close();
    return EXIT_SUCCESS;

}