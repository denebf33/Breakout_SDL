/**@file  BallObject.cpp
* @brief       Source code of BallObject
* @details  Define all functions of class BallObject.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/

#include "BallObject.hpp"

BallObject::BallObject():GameObject(), radius(12.5f), stuck(true){};
BallObject::BallObject(TinyMath::Vec2 pos, float radius, TinyMath::Vec2 velocity, SDL_Surface* sprite, SDL_Renderer* renderer):GameObject(pos, TinyMath::Vec2(radius * 2, radius * 2), sprite, renderer, TinyMath::Vec3(255, 255, 255), velocity), radius(radius), stuck(true){};

TinyMath::Vec2 BallObject::Move(float dt, int window_width)
{
    if(!this->stuck)
    {
        this->dest.x += this->velocity.x * dt;
        this->dest.y += this->velocity.y * dt;
        
        if(this->dest.x <= 0.0f)
        {
            Mix_PlayChannel(-1, ResourceManager::GetInstance()->GetSoundEffect("bleepSolid"), 0);
            this->velocity.x = -this->velocity.x;
            this->dest.x = 0.0f;
        }
        else if(this->dest.x + this->dest.w >= window_width)
        {
            Mix_PlayChannel(-1, ResourceManager::GetInstance()->GetSoundEffect("bleepSolid"), 0);
            this->velocity.x = -this->velocity.x;
            this->dest.x = window_width - this->dest.w;
        }
        
        if(this->dest.y <= 0.0f)
        {
            Mix_PlayChannel(-1, ResourceManager::GetInstance()->GetSoundEffect("bleepSolid"), 0);
            this->velocity.y = -this->velocity.y;
            this->dest.y = 0.0f;
        }
    }
    
    return TinyMath::Vec2(this->dest.x, this->dest.y);
}

void BallObject::Reset(TinyMath::Vec2 position, TinyMath::Vec2 velocity)
{
    this->dest.x = position.x;
    this->dest.y = position.y;
    this->velocity = velocity;
    this->stuck = true;
}
