/**@file  TextField.cpp
* @brief       Source code of TextField.
* @details  Define all functions of class TextField.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/

#include "TextField.hpp"

TextField::TextField(TinyMath::Vec2 position, SDL_Renderer* renderer, TTF_Font* font, std::string lang, int width, int height, bool center):renderer(renderer), font(font), lang(lang),width(width), height(height), center(center)
{
    if(lang == "English")
        this->surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
    else if(lang == "Chinese")
        this->surface = TTF_RenderUTF8_Solid(font,"0", {0xFF, 0xFF, 0xFF, 0xFF});
        
    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
    
    int tempWidth;
    int tempHeight;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &tempWidth, &tempHeight);
    
    if(this->center)
    {
        rect.x = width / 2 - tempWidth / 2;
    }
    else
    {
        rect.x = static_cast<int>(position.x);
    }
    
    rect.y = static_cast<int>(position.y);
    rect.w = tempWidth;
    rect.h = tempHeight;
}
TextField::TextField()
{
    
}

TextField::~TextField()
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void TextField::Draw()
{
    SDL_RenderCopy(renderer, this->texture, nullptr, &rect);
}

void TextField::SetText(std::string str)
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    if(lang == "English")
        this->surface = TTF_RenderText_Solid(font, str.c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
    else if(lang == "Chinese")
        this->surface = TTF_RenderUTF8_Solid(font,str.c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
    
    
    
    int tempWidth;
    int tempHeight;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &tempWidth, &tempHeight);
    
    if(this->center)
    {
        rect.x = width / 2 - tempWidth / 2;
    }
    
    rect.w = tempWidth;
    rect.h = tempHeight;
}
