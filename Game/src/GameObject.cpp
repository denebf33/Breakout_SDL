/**@file  GameObject.cpp
* @brief       Source code of GameObject
* @details  Define all functions in class GameObject.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/

#include "GameObject.hpp"
GameObject::GameObject(): velocity(0.0f, 0.0f), color(255, 255, 255), sprite(), isSolid(false), destroyed(false){
    this->dest.x = 0;
    this->dest.y = 0;
    this->dest.w = 0;
    this->dest.h = 0;
};

GameObject::GameObject(TinyMath::Vec2 pos, TinyMath::Vec2 size, SDL_Surface* surface, SDL_Renderer* renderer, TinyMath::Vec3 color, TinyMath::Vec2 velocity): velocity(velocity), surface(surface), renderer(renderer), color(color), isSolid(false), destroyed(false){
    this->sprite = SDL_CreateTextureFromSurface(this->renderer, this->surface);
    SDL_SetTextureColorMod(sprite, color.x, color.y, color.z);
    this->dest.x = pos.x;
    this->dest.y = pos.y;
    this->dest.w = size.x;
    this->dest.h = size.y;
};
GameObject::~GameObject()
{
    SDL_DestroyTexture(this->sprite);
}

void GameObject::Draw()
{
    SDL_RenderCopy(this->renderer, this->sprite, NULL, &dest);
}
