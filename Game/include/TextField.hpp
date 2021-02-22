/**@file  TextField.hpp
* @brief       Header of TextField.hpp
* @details  Declare a class to manage all text fields in the game.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/

#ifndef TextField_hpp
#define TextField_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include "TinyMath.hpp"

/**@class TextField
 *@brief Class of text fields.
 *@details Contains the attributes and functions of all text fields.
*/
class TextField{
public:
    SDL_Renderer* renderer;///< Current renderer.
    TTF_Font* font;///< Font for this text field.
    SDL_Surface* surface;///< Surface of this text field.
    SDL_Texture* texture;///< Texture of texts.
    SDL_Rect rect{};///< Rect to store position and size of the text field.
    int width, height;///< Height and width of the screen.
    std::string lang;///< Language of this text field, choose between "Chinese" and "English".
    bool center;///< Whether this text field rendered on the center of the x-axis of the screen.
    
    /**@brief Constructor of TextField.
     *@param[in] position Position of this text field.
     *@param[in] renderer Current renderer.
     *@param[in] font Font of this text field, stored in ResourceManager.
     *@param[in] lang Language of this text field.
     *@param[in] width Width of the screen.
     *@param[in] height Height of the screen.
     *@param[in] center Whether this text field rendered on the center of the x-axis of the screen.
     *@par Example:
     *@code
     *  TextField* scoreField = new TextField(TinyMath::Vec2(width - 100, 0), this->renderer, ResourceManager::GetInstance()->GetFont("scoreFont"), lang);
     *@endcode
    */
    TextField(TinyMath::Vec2 position, SDL_Renderer* renderer, TTF_Font* font, std::string lang, int width, int height, bool center = false);
    TextField();///< Empty constructor.
    
    ~TextField();///< Destructor, free all allocated memory and other resources.
    
    void Draw();///< Draw this text field into the renderer. Call in the main loop.
    
    /**@brief Set the text of this text field.
     *@param[in] str The text you want to set.
     *@par Example:
     *@code
     *  textFields["lifeField"]->SetText(ResourceManager::GetInstance()->GetString(0) + std::to_string(this->lives));
     *@endcode
    */
    void SetText(std::string str);
};

#endif /* TextField_hpp */
