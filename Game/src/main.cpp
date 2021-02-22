/**@mainpage  Breakout
* <table>
* <tr><th>Project  <td>Breakout
* <tr><th>Author   <td>JunfengZhou
* </table>
* @section   Project details
* This project is a simple breakout game that was built with SDL2. Main reference of this project is https://learnopengl.com/.
*
* @section   Instructions
* -# This project was built on MacOS.
* -# You have to have SDL2, SDL_image, SDL_ttf, SDL_mixer loaded in your environment.
*
* @section            How to play
* -# Use A/D or Left/Right Arrow on your key board to switch levels and control your paddle.
* -# Use Space to start the game.
* -# Use Q on your key board to quit the game.
*
**********************************************************************************
*/

/**@file  main.cpp
* @brief       Main function of the project.
* @details  Interface of the main function.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include "Game.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main()
{
    std::string lang;
    std::cout << "Input your language, you can choose between English and Chinese" << std::endl;
    std::cin >> lang;
    // Initialize SDL components
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_Window* window = SDL_CreateWindow("Breakout", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Game logic
    {
        float dt = 0.0f,  tempdt = 0.0f;
        
        int frameCounter = 0;
        float frameCountTimer = 0.0f;
        bool running = true;
        bool buttons[3] = {};
        
        float lag = 0.0f;
        
        Game game(WINDOW_WIDTH, WINDOW_HEIGHT, renderer, lang);
        game.Init();
        
        // Continue looping and processing events until user exits
        while (running)
        {
            auto startTime = std::chrono::high_resolution_clock::now();
            
            // Process inputs
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_q)
                    {
                        running = false;
                    }
                    else if(event.key.keysym.sym == SDLK_a)
                        buttons[Buttons::PaddleLeft] = true;
                    else if(event.key.keysym.sym == SDLK_d)
                        buttons[Buttons::PaddleRight] = true;
                    else if(event.key.keysym.sym == SDLK_LEFT)
                        buttons[Buttons::PaddleLeft] = true;
                    else if(event.key.keysym.sym == SDLK_RIGHT)
                        buttons[Buttons::PaddleRight] = true;
                    else if(event.key.keysym.sym == SDLK_SPACE)
                        buttons[Buttons::Confirm] = true;
                }
                else if (event.type == SDL_KEYUP)
                {
                    if(event.key.keysym.sym == SDLK_a)
                        buttons[Buttons::PaddleLeft] = false;
                    else if(event.key.keysym.sym == SDLK_d)
                        buttons[Buttons::PaddleRight] = false;
                    else if(event.key.keysym.sym == SDLK_LEFT)
                        buttons[Buttons::PaddleLeft] = false;
                    else if(event.key.keysym.sym == SDLK_RIGHT)
                        buttons[Buttons::PaddleRight] = false;
                    else if(event.key.keysym.sym == SDLK_SPACE)
                        buttons[Buttons::Confirm] = false;
                }
            }
            // Update with fixed timestep
            lag += dt;
            while(lag >= 1000.0f / 60.0f)
            {
                game.ProcessInput(dt, buttons);
                game.Update(dt);
                lag -= 1000.0f / 60.0f;
            }
            
            // Render
            // Clear the window to black
            SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
            SDL_RenderClear(renderer);
            
            game.Render();
            
            // Present the backbuffer
            SDL_RenderPresent(renderer);
            
            
            // Calculate frame time
            auto stopTime = std::chrono::high_resolution_clock::now();
            tempdt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
            
            // Frame capping and calculate frame time again
            if(tempdt < 1000.0f / 60.0f)
            {
                SDL_Delay(1000.0f / 60.0f - tempdt);
                stopTime = std::chrono::high_resolution_clock::now();
                dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
            }
            else
                dt = tempdt;
            
            
            // Frame counting
            if((frameCountTimer += dt) > 1000.0f)
            {
                std::cout << "FPS " << frameCounter << std::endl;
                frameCounter = 0;
                frameCountTimer = 0.0f;
            }
            else
            {
                frameCounter ++;
            }
        }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
