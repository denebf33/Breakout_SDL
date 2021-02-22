/**@file  GameLevel.cpp
* @brief       Source code of GameLevel
* @details  Define all functions of class GameLevel.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/

#include "GameLevel.hpp"
void GameLevel::Load(int levelCode, int levelWidth, int levelHeight, SDL_Renderer* renderer)
{
    for(auto b : Bricks)
    {
        delete b;
    }
    this->Bricks.clear();

    if(ResourceManager::GetInstance()->GetLevel(levelCode).size() > 0)
        this->Init(ResourceManager::GetInstance()->GetLevel(levelCode), levelWidth, levelHeight, renderer);
}
GameLevel::~GameLevel()
{
    for(auto b : Bricks)
    {
        delete b;
    }
    Bricks.clear();
}

void GameLevel::Init(std::vector<std::vector<int>> tileData, int levelWidth, int levelHeight, SDL_Renderer* renderer)
{
    int height = tileData.size();
    int width = tileData[0].size();
    float unit_width = levelWidth / static_cast<float>(width);
    float unit_height = levelHeight / height;
    
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            if(tileData[y][x] == 1)
            {
                TinyMath::Vec2 pos(unit_width * x, unit_height * y);
                TinyMath::Vec2 size(unit_width, unit_height);
                GameObject* obj = new GameObject(pos, size, ResourceManager::GetInstance()->GetSurface("brick_solid"), renderer, TinyMath::Vec3(204, 204, 179));
                obj->isSolid = true;
                this->Bricks.push_back(obj);
            }
            else if(tileData[y][x] > 1)
            {
                TinyMath::Vec3 color = TinyMath::Vec3(255, 255, 255);
                if(tileData[y][x] == 2)
                    color = TinyMath::Vec3(51, 153, 255);
                else if(tileData[y][x] == 3)
                    color = TinyMath::Vec3(0, 179, 0);
                else if(tileData[y][x] == 4)
                    color = TinyMath::Vec3(204, 204, 102);
                else if(tileData[y][x] == 5)
                    color = TinyMath::Vec3(255, 128, 0);
                
                TinyMath::Vec2 pos(unit_width * x, unit_height * y);
                TinyMath::Vec2 size(unit_width, unit_height);
                
                this->Bricks.push_back(new GameObject(pos, size, ResourceManager::GetInstance()->GetSurface("brick"), renderer, color));
                
            }
        }
    }
}

void GameLevel::Draw()
{
    for(GameObject* tile : this->Bricks)
    {
        if(!tile->destroyed)
            tile->Draw();
    }
}

bool GameLevel::IsCompleted()
{
    for(GameObject* tile : this->Bricks)
    {
        if(!tile->isSolid && !tile->destroyed)
            return false;
    }
    
    return true;
}

GameLevel::GameLevel(){};
