/**@file  GameObject.hpp
* @brief       Header of GameObject.cpp
* @details  Declare a class to represent all interactable objects in the game.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/
#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "TinyMath.hpp"
#include "ResourceManager.hpp"

/**@class GameObject
 *@brief Class of all interactable objects in the game.
 *@details Used to represent player, ball, bricks in the game.
*/
class GameObject
{
public:
    TinyMath::Vec2 velocity;///< Velocity of this object. TinyMath::Vec2(0, 0) for bricks.
    TinyMath::Vec3 color;///< Color of this object. Used to render bricks with different colors.
    bool isSolid;///< If this object is a brick, whether it is solid.
    bool destroyed;///< If this object is a brick, whether it is destryed.
    
    SDL_Surface* surface;///< Surface of this object, used to create corresponding texture.
    SDL_Texture* sprite;///< Create by this->surface.
    SDL_Renderer* renderer;///< Current renderer.
    SDL_Rect dest;///< Store position and size of this object.
    
    GameObject();///< Empty constructor.
    ~GameObject();///< Destructor, free all allocated memory or other resource of this object.
    
    /**@brief Constructor of GameObject
     *@param[in] pos Position of the object.
     *@param[in] size Size of the object.
     *@param[in] surface Surface to create texture.
     *@param[in] renderer Current renderer.
     *@param[in] color Color of the object. Only works on bricks.
     *@param[in] velocity Initial velocity of the object.
     *@par Example:
     *@code
     *  GameObject* obj = new GameObject(pos, size, ResourceManager::GetInstance()->GetSurface("brick_solid"), renderer, TinyMath::Vec3(204, 204, 179));
     *@endcode
    */
    GameObject(TinyMath::Vec2 pos, TinyMath::Vec2 size, SDL_Surface* surface, SDL_Renderer* renderer, TinyMath::Vec3 color = TinyMath::Vec3(255, 255, 255), TinyMath::Vec2 velocity = TinyMath::Vec2(0.0f, 0.0f));
    
    virtual void Draw();///< Funtion to draw this object. Call in main loop.
};

#endif /* GameObject_hpp */
