/**@file  Game.hpp
* @brief       Header of Game.cpp
* @details  Declared the game class and some related enums or const variables.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include <tuple>
#include <string>
#include "GameLevel.hpp"
#include "BallObject.hpp"
#include "TinyMath.hpp"
#include "TextField.hpp"

/**@enum Gamestate
 *@brief Represent current game state.
*/
enum GameState{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_END
};

/**@enum Gamestate
 *@brief Represent key input state.
*/
enum Buttons
{
    PaddleLeft = 0,
    PaddleRight,
    Confirm
};

const TinyMath::Vec2 PLAYER_SIZE(100, 20); ///< Size of the player.
const float PLAYER_VELOCITY(500.0f);///< Velocity of the player.
const TinyMath::Vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);///< Initial veclocity of the ball.
const float BALL_RADIUS(12.5f);///< Radius of the ball.

/**@class Game
 *@brief Class of the game logic.
 *@details Contains the main logic of the game. Should be instantiated before the game loop.
*/
class Game
{
public:
    GameState state;///< Variable represents current game state.
    SDL_Renderer* renderer;///< Current renderer.
    int width, height;///< Size of the screen.
    std::vector<GameLevel*> levels;///< All loaded game levels.
    int level;///< Current game level.
    SDL_Texture* backgroundTexture;///< Texture of background picture.
    GameObject *player;///< Unique pointer of the player.
    BallObject *ball;///< Unique pointer of the ball.
    std::unordered_map<std::string, TextField*> textFields;///< All generated textField.
    
    int lives = 3;///< Remaining lives. Default 3.
    int score;///< Current score.
    
    /**@brief Constructor of Game class.
     *@param[in] width The width of the screen.
     *@param[in] height The height of the screen.
     *@param[in] renderer Current renderer.
     *@param[in] lang Language of the game, "English" or "Chinese".
     *@par Example:
     *@code
     *  Clamp(800, 600, renderer, "Chinese");
     *@endcode
    */
    Game(int width, int height, SDL_Renderer* renderer, std::string lang);
    
    /**@brief Destructor of Game class.
     *@details Free all pointers and other allocated menmory.
    */
    ~Game();
    
    /**@brief Initialize funtion of Game class.
     *@details Call this function after the Game class is instantiated.
    */
    void Init();
    
    /**@brief Update function
     *@details Should be called in the main loop.
     *@param[in] dt  Delta time of main loop.
    */
    void Update(float dt);
    
    /**@brief Render function
     *@details Should be called each frame.
    */
    void Render();
    
    /**@brief Process player's input
     *@param[in] dt Delta time of main loop.
     *@param[in] buttons[3] Arrays of key states.
    */
    void ProcessInput(float dt, const bool buttons[3]);
    
    /**@brief Collision check function
     *@details Should be called in the Update() function.\n
     *Check all the bricks and process the collision logic.
    */
    void DoCollisions();
    
    void ResetLevel();///< Reset current level and score.
    void ResetPlayer();///< Reset Player's position.
    
private:
    bool rightKeyBool = false;//< Help process "on key down" events.
    bool leftKeyBool = false;//< Help process "on key down" events.
    std::string lang;//< Current language setting.
};

#endif /* Game_hpp */
