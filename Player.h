//header file for player definitions 
#ifndef PLAYER_H
#define PLAYER_H 

#include<SDL2/SDL.h> 

class Player{

    public: 
        Player(int x, int y); //constructor 
        void draw(SDL_Renderer* renderer); //method definitions 
        SDL_Rect getRect() const; 
        int x, y; 
        const int height = 30;
        const int width = 30; 
    
};

#endif