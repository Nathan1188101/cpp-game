//header file for enemy, here we define enemy related functions and variables 
#ifndef ENEMY_H
#define ENEMY_H 

#include<SDL2/SDL.h> 

class Enemy{
    public:
        //constructor for enemy object
        Enemy(int x, int y);
        //define methods under public (these define the behaviour of the class)
        void draw(SDL_Renderer* renderer); 
        SDL_Rect getRect() const; 
        int x, y; 
    
    private: 
        const int height = 50; 
        const int width = 50; 
        //int x, y; 

};

#endif 