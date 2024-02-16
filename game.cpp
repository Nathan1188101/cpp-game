#include <iostream> 
#include <ctime>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "Enemy.h"
#include "Player.h"

using namespace std;

const int WIDTH = 800, HEIGHT = 600;

SDL_Window* window = nullptr; 
SDL_Renderer* renderer = nullptr; 
SDL_Texture* playerText; 
SDL_Rect srcR, destR; 

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
    renderer = SDL_CreateRenderer(window, -1, 0);//-1 parameter indicates that the first available rendering driver should be used. In the 0 position is where we indicate additional rendering flags, 0 indicates NO additional flags are used

    if(renderer == nullptr)
    {
        return false; 
    }

    //setting screen bounds 
    SDL_Rect screenBounds; 
    SDL_GetDisplayUsableBounds(0, &screenBounds);
    int screenWidth = screenBounds.w; 
    int screenHeight = screenBounds.h; 

    //player texture
    SDL_Surface* tmpSurface = IMG_Load("assets/idle.png");
    if(!tmpSurface){
        cout << "Failed to load player image: " << IMG_GetError() << endl;
        return false; 
    }
    playerText = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface); //don't need anymore so we delete the tmp 

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

void restrictPlayer(Player& player){

    if(player.x < 0)
    {
         player.x = 0; 
    }
    if(player.x + player.width > WIDTH)
    {
        player.x = WIDTH - player.width; 
    }
    if(player.y < 0)
    {
        player.y = 0; 
    }
    if(player.y > HEIGHT)
    {
        player.y = HEIGHT - player.height; //taking the height and subtracting the players height keeps them within the View of the window
    }
    
}

void movePlayer(Player& player)
{

    //player control (common to use this Uint8 data type (that represents an 8-bit unsigned integer) for keyboard strokes)
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if(currentKeyStates[SDL_SCANCODE_D]) //currentKeyStates is a pointer, checking if d key has been pressed
        {
            player.x += 1;
        }
        if(currentKeyStates[SDL_SCANCODE_A]) //checking if A key has been pressed
        {
            player.x -= 1;
        }
         if(currentKeyStates[SDL_SCANCODE_W]) //checking if A key has been pressed
        {
            player.y -= 1;
        }
        if(currentKeyStates[SDL_SCANCODE_S]) //checking if A key has been pressed
        {
            player.y += 1;
        }

}

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    return SDL_HasIntersection(&a, &b) == SDL_TRUE; 
}

int main(int argc, char *argv[]){

    srand(time(NULL)); 

    //SDL_Event is used to represent events that occur in the program, like user input events (keyboard and mouse), window events (resizing, closing)
    SDL_Event windowEvent; 
    int playerX = rand() % WIDTH;
    int playerY = rand() % HEIGHT;
    int enemyX = rand() % WIDTH;
    int enemyY = rand() % HEIGHT;
    bool quit = false;

    //creating enemy object
    Enemy enemy(enemyX, enemyY); 
    //creating player
    Player player(playerX, playerY); 

    init(); 

    //set render draw color to red 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
    SDL_RenderClear(renderer); // this will clear the display and draw its new color we set above

    while(!quit)
    {
        while(SDL_PollEvent(&windowEvent))
        {
            if(SDL_QUIT == windowEvent.type)
                {
                    quit = true;
                }
        }

        movePlayer(player);
        restrictPlayer(player); 

        SDL_Rect enemyRect = enemy.getRect(); 
        SDL_Rect playerRect = player.getRect(); 

        if(checkCollision(playerRect, enemyRect ))
        {
            cout << "COLLISION" << endl; 
            enemy.x = rand() % WIDTH; 
            enemy.y = rand() % WIDTH;
        }
        
        //set render draw color to red 
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderClear(renderer); // this will clear the display and draw its new color we set above

        SDL_RenderCopy(renderer, playerText, NULL, &playerRect);

        //common to first draw objects and then present
        player.draw(renderer);
        enemy.draw(renderer); 
        SDL_RenderPresent(renderer); 


    }

    close();
    return EXIT_SUCCESS;

}