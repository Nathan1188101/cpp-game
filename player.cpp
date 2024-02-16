#include "Player.h"

Player::Player(int x, int y) : x(x), y(y) {} 

void Player::draw(SDL_Renderer* renderer){

    SDL_Rect playerRect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//setting color
    SDL_RenderFillRect(renderer, &playerRect);

}

SDL_Rect Player::getRect() const{

    SDL_Rect rect;
    rect.x = x; //x position
    rect.y = y; //y position
    rect.w = width; //width
    rect.h = height; //height

    return rect; 
    
}

