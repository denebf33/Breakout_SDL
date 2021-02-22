/**@file  GameLevel.hpp
* @brief       Header of GameLevel.cpp
* @details  Declare a class to represent all levels in the game.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/
#ifndef GameLevel_hpp
#define GameLevel_hpp

#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <istream>
#include <sstream>
#include "GameObject.hpp"
#include "ResourceManager.hpp"

/**@class GameLevel
 *@brief Class of all levels in the game.
 *@details Class to store, initialize and render levels.
*/
class GameLevel
{
public:
    SDL_Renderer* renderer;///< Current renderer.
    std::vector<GameObject*> Bricks;///< std::vector to store all bricks in this level.
    
    GameLevel();///< Empty contructor.
    
    /**@brief Load level from level data.
     *@param[in] levelCode Index of the level.
     *@param[in] levelWidth Equal to the width of the screen.
     *@param[in] levelHeight Half of the height of the screen.
     *@param[in] renderer Current renderer.
     *@par Example:
     *@code
     *  one->Load(1, this->width, this->height / 2, this->renderer);
     *@endcode
    */
    void Load(int levelCode, int levelWidth, int levelHeight, SDL_Renderer* renderer);
    void Draw();///< Draw this level. Call in the main loop.
    bool IsCompleted();///< Check if this level is completed.
    ~GameLevel();///< Destructor, free all allocated memory or other resources.
    
private:
    
    /**@brief Initialize this level. Called in the contructor.
     *@param[in] tileData Data that called from ResourceManager
     *@param[in] levelWidth Equal to the width of the screen.
     *@param[in] levelHeight Half of the height of the screen.
     *@param[in] renderer Current renderer.
     *@par Example:
     *@code
     *  this->Init(ResourceManager::GetInstance()->GetLevel(levelCode), levelWidth, levelHeight, renderer);
     *@endcode
    */
    void Init(std::vector<std::vector<int>> tileData, int levelWidth, int levelHeight, SDL_Renderer* renderer);
};

#endif /* GameLevel_hpp */
