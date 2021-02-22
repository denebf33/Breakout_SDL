/**@file  BallObject.hpp
* @brief       Header of BallObject.cpp
* @details  Declare a class that derived from GameObject class, to represent the ball in the game.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/

#ifndef BallObject_hpp
#define BallObject_hpp

#include <stdio.h>
#include "GameObject.hpp"

/**@class BallObject
 *@brief Derived form the class GameObject. Represents the ball in the game.
 *@details Class to store data of the ball, and the Move() and Reset() function of it.
*/
class BallObject : public GameObject
{
public:
    float radius;///< Radius of the ball.
    bool stuck;///< Whether the ball is stucked in the paddle.
    
    BallObject();///< Empty constructor.
    
    /**@brief Contructor of BallObject
     *@param[in] pos Position of the ball.
     *@param[in] radius Radius of the ball.
     *@param[in] velocity Initial velocity of the ball.
     *@param[in] sprite The sprite of the ball. Stored in ResourceManager.
     *@param[in] renderer Current renderer.
     *@par Example:
     *@code
     *  BallObject* ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetInstance()->GetSurface("face"), renderer);
     *@endcode
    */
    BallObject(TinyMath::Vec2 pos, float radius, TinyMath::Vec2 velocity, SDL_Surface* sprite, SDL_Renderer* renderer);
    
    /**@brief Move the ball
     *@param[in] dt Delta time of the main loop.
     *@param[in] window_width Width of the window.
     *@par Example:
     *@code
     *  ball->Move(localDt, this->width);
     *@endcode
    */
    TinyMath::Vec2 Move(float dt, int window_width);
    
    /**@brief Reset the ball.
     *@param[in] position Reset position.
     *@param[in] velocity Reset initial velocity.
     *@par Example:
     *@code
     *  ball->Reset(TinyMath::Vec2(player->dest.x, player->dest.y) + TinyMath::Vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
     *@endcode
    */
    void Reset(TinyMath::Vec2 position, TinyMath::Vec2 velocity);
};
#endif /* BallObject_hpp */
