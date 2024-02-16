#include "Enemy.h"

//:: basically means for

//Enemy::Enemy is basically saying were creating a constructor for the enemy class 
Enemy::Enemy(int x, int y) : x(x), y(y) {}

void Enemy::draw(SDL_Renderer* renderer){

    SDL_Rect enemyRect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //red
    SDL_RenderFillRect(renderer, &enemyRect);
    
}

SDL_Rect Enemy::getRect() const{

    SDL_Rect rect;
    rect.x = x; //x position
    rect.y = y; //y position
    rect.w = width; //width
    rect.h = height; //height

    return rect; 
    
}