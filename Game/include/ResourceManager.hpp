/**@file  ResourceManager.hpp
* @brief       Header of ResourceManager.cpp
* @details  Declare a singleton class to manage all resources in the game.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <memory>
#include <iterator>
#include <unordered_map>
#include <iostream>
#include <SDL2_image/SDL_image.h>
#include <fstream>
#include <string>
#include <istream>
#include <sstream>
#include <vector>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

/**@class ResourceManager
 *@brief A singleton class to manage all resources in the game.
 *@details Contains store structure and load, call functions of pics, sound, ttfs, and strings.
*/
class ResourceManager{
public:
    /**@brief ResourceManager singleton function
     *@details Use ResourceManager::GetInstance() to get a singleton pointer.
    */
    static ResourceManager* GetInstance()
    {
        if(singletonPtr==nullptr){
            singletonPtr = std::shared_ptr<ResourceManager>(new ResourceManager());
        }
        return singletonPtr.get();
    }
    
    /**@brief Start up function should be called after the singleton is created. Called in the Game::Init() function.
     *@param[in] lang The language to load, you can choose between "English" and "Chinese".
     *@par Example:
     *@code
     *  ResourceManager::GetInstance()->startUp("Chinese");
     *@endcode
    */
    int startUp(std::string lang);
    
    /**@brief Get a surface from the spriteSheet.
     *@param[in] surfaceName Name of the surface you want to get.
     *@par Example:
     *@code
     *  Surface* brickSurface = ResourceManager::GetInstance()->GetSurface("brick");
     *@endcode
    */
    SDL_Surface* GetSurface(std::string surfaceName);
    
    /**@brief Get a level data from the levelSheet.
     *@param[in] levelCode The level you want to get.
     *@par Example:
     *@code
     *  std::vector<std::vector<int>> levelOneData = ResourceManager::GetInstance()->GetLevel(0);
     *@endcode
    */
    std::vector<std::vector<int>> GetLevel(int levelCode);
    
    /**@brief Get a font from the fontSheet.
     *@param[in] fontName The font you want to get.
     *@par Example:
     *@code
     *  TTF_Font* fontTitle = ResourceManager::GetInstance()->GetFont("titleFont");
     *@endcode
    */
    TTF_Font* GetFont(std::string fontName);
    
    /**@brief Get a sound effect from the soundEffectSheet.
     *@param[in] soundEffectName The sound effect you want to get.
     *@par Example:
     *@code
     *  Mix_Chunk* bounceEffect = ResourceManager::GetInstance()->GetSoundEffect("bounceEffect");
     *@endcode
    */
    Mix_Chunk* GetSoundEffect(std::string soundEffectName);
    
    /**@brief Get a music from the soundEffectSheet.
     *@param[in] musicName The music you want to get.
     *@par Example:
     *@code
     *  Mix_Music* bgm = ResourceManager::GetInstance()->GetSoundEffect("bgm");
     *@endcode
    */
    Mix_Music* GetMusic(std::string musicName);
    
    /**@brief Get a string from the textSheet.
     *@param[in] stringCode The number of the certain text you want to get.
     *@par Example:
     *@code
     *  std::string str = ResourceManager::GetInstance()->GetString(0);
     *@endcode
    */
    std::string GetString(int stringCode);
    
    /**@brief Load a .png or .jpg file into a Surface*
     *@details The path should be relative to the ./bin/breakout folder.
     *@param[in] file File path of the pic.
     *@param[in] name Name of the pic.
     *@par Example:
     *@code
     *  LoadPic("./Assets/Img/block.png", "brick");
     *@endcode
    */
    bool LoadPic(const char *file, std::string name);
    
    /**@brief Load a .lvl file into a std::vector<std::vector<int>>*
     *@details The path should be related to the ./bin/breakout  file.
     *@param[in] file File path of the level file.
     *@param[in] levelCode Index of the level.
     *@par Example:
     *@code
     *  LoadLevel("./Assets/Levels/one.lvl", 1);
     *@endcode
    */
    bool LoadLevel(const char *file, int levelCode);
    
    /**@brief Load a .ttf file into a TTF_Font*
     *@details The path should be relative to the ./bin/breakout file.
     *@param[in] file File path of the font.
     *@param[in] fontSize The size of the font.
     *@param[in] name Name of the font.
     *@par Example:
     *@code
     *  LoadFont("./Assets/Fonts/Song.ttf", 20, "scoreFont");
     *@endcode
    */
    bool LoadFont(const char *file, int fontSize, std::string name);
    
    /**@brief Load a .wav into Mix_Chunk*
     *@details The path should be relative to the ./bin/breakout file.
     *@param[in] file File path of the sound effect.
     *@param[in] name Name of the sound effect.
     *@par Example:
     *@code
     *  LoadSoundEffect("./Assets/Sounds/bleepSolid.wav", "bleepSolid");
     *@endcode
    */
    bool LoadSoundEffect(const char *file, std::string name);
    
    /**@brief Load a .mp3 into Mix_Music*
     *@details The path should be relative to the ./bin/breakout file.
     *@param[in] file File path of the music.
     *@param[in] name Name of the music.
     *@par Example:
     *@code
     *  LoadMusic("./Assets/Sounds/backgroundMusic.mp3", "bgm");
     *@endcode
    */
    bool LoadMusic(const char *file, std::string name);
    
    /**@brief Load a .txt into some std::string
     *@details The path should be relative to the ./bin/breakout folder.
     *@param[in] file File path of the .txt file.
     *@par Example:
     *@code
     *  LoadText("./Assets/Strings/String_ch.txt");
     *@endcode
    */
    bool LoadText(const char *file);
    ~ResourceManager();
    std::unordered_map<std::string, SDL_Surface*> spriteSheet;
private:
    ResourceManager();
    static std::shared_ptr<ResourceManager> singletonPtr;
    std::unordered_map<int, std::vector<std::vector<int>>> levelSheet;///< unordered_map to store all Surface*
    std::unordered_map<std::string, TTF_Font*> fontSheet;///< unordered_map to store all TTF_Font*
    std::unordered_map<std::string, Mix_Chunk*> soundEffectSheet;///< unordered_map to store all Mix_Chunk*
    std::unordered_map<std::string, Mix_Music*> musicSheet;///< unordered_map to store all Mix_Music*
    std::unordered_map<int, std::string> textSheet;///< unordered_map to store all std::string of game texts
};
#endif
