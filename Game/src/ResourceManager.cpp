/**@file  ResourceManager.cpp
* @brief       Source code of ResourceManager
* @details  Define all functions of class ResourceManager
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include "ResourceManager.hpp"

std::shared_ptr<ResourceManager> ResourceManager::singletonPtr = nullptr;
ResourceManager::ResourceManager()
{
    
}

int ResourceManager::startUp(std::string lang)
{
    if(singletonPtr==nullptr){
        singletonPtr = std::shared_ptr<ResourceManager>(new ResourceManager());
    }
    
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    IMG_Init(IMG_INIT_JPG);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    LoadLevel("../Assets/Levels/one.lvl", 1);
    LoadLevel("../Assets/Levels/two.lvl", 2);
    LoadLevel("../Assets/Levels/three.lvl", 3);
    LoadLevel("../Assets/Levels/four.lvl", 4);
    
    if(lang == "Chinese")
    {
        LoadFont("../Assets/Fonts/Song.ttf", 20, "scoreFont");
        LoadFont("../Assets/Fonts/Song.ttf", 30, "noticeFont1");
        LoadFont("../Assets/Fonts/Song.ttf", 40, "resultFont");
        
        LoadText("../Assets/Strings/String_ch.txt");
    }
    else if(lang == "English")
    {
        LoadFont("../Assets/Fonts/DejaVuSansMono.ttf", 20, "scoreFont");
        LoadFont("../Assets/Fonts/DejaVuSansMono.ttf", 30, "noticeFont1");
        LoadFont("../Assets/Fonts/DejaVuSansMono.ttf", 40, "resultFont");
        
        LoadText("../Assets/Strings/String_eng.txt");
    }
    else
    {
        SDL_Log("Wrong language input");
        return 0;
    }
    
    
    LoadPic("../Assets/Img/block.png", "brick");
    LoadPic("../Assets/Img/block_solid.png", "brick_solid");
    LoadPic("../Assets/Img/background.jpg", "background");
    LoadPic("../Assets/Img/paddle.png", "paddle");
    LoadPic("../Assets/Img/awesomeface.png", "face");
    
    LoadSoundEffect("../Assets/Sounds/bleepSolid.wav", "bleepSolid");
    LoadSoundEffect("../Assets/Sounds/bleepBrick.wav", "bleepBrick");
    LoadSoundEffect("../Assets/Sounds/bleepPaddle.wav", "bleepPaddle");
    
    LoadMusic("../Assets/Sounds/backgroundMusic.mp3", "bgm");
    
    return 1;
}

ResourceManager::~ResourceManager()
{
    for(auto pairs : spriteSheet)
    {
        SDL_FreeSurface(pairs.second);
    }
    
    for(auto pairs : fontSheet)
    {
        TTF_CloseFont(pairs.second);
    }
    
    for(auto pairs : soundEffectSheet)
    {
        Mix_FreeChunk(pairs.second);
    }
    
    for(auto pairs : musicSheet)
    {
        Mix_FreeMusic(pairs.second);
    }
    
    fontSheet.clear();
    levelSheet.clear();
    spriteSheet.clear();
    
    TTF_Quit();
    IMG_Quit();
    Mix_CloseAudio();
}

SDL_Surface* ResourceManager::GetSurface(std::string surfaceName)
{
    return spriteSheet[surfaceName];
}

std::vector<std::vector<int>> ResourceManager::GetLevel(int levelCode)
{
    return levelSheet[levelCode];
}

TTF_Font* ResourceManager::GetFont(std::string fontName)
{
    return fontSheet[fontName];
}

Mix_Chunk* ResourceManager::GetSoundEffect(std::string soundEffectName)
{
    return soundEffectSheet[soundEffectName];
}

Mix_Music* ResourceManager::GetMusic(std::string musicName)
{
    return musicSheet[musicName];
}
std::string ResourceManager::GetString(int stringCode)
{
    return textSheet[stringCode];
}

bool ResourceManager::LoadPic(const char *file, std::string name)
{
    if(SDL_Surface* temp = IMG_Load(file))
    {
        spriteSheet.emplace(name, temp);
        std::string str = " is allocated";
        SDL_Log("%s", (name + str).c_str());
        return true;
    }
    else
    {
        std::string str = "Fail to allocate ";
        SDL_Log("%s", (str + name).c_str());
        return false;
    }
}

bool ResourceManager::LoadLevel(const char *file, int levelCode)
{
    int tileCode;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<int>> tileData;
    
    if(fstream)
    {
        while(std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<int> row;
            while(sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        
        if(tileData.size() > 0)
        {
            levelSheet.emplace(levelCode, tileData);
            std::string str = "level map is loaded";
            SDL_Log("%s", (std::to_string(levelCode) + str).c_str());
            return true;
        }
        std::string str = "Fail to load level ";
        SDL_Log("%s", (str + std::to_string(levelCode)).c_str());
        return false;
    }
    std::string str = "Fail to load level ";
    SDL_Log("%s", (str + std::to_string(levelCode)).c_str());
    return false;
}

bool ResourceManager::LoadFont(const char *file, int size, std::string name)
{
    if(TTF_Font* font = TTF_OpenFont(file, size))
    {
        fontSheet.emplace(name, font);
        std::string str = " font loaded";
        SDL_Log("%s", (name + str).c_str());
        return true;
    }
    else
    {
        std::string str = "Fail to load font ";
        SDL_Log("%s", (str + name).c_str());
        return false;
    }
}

bool ResourceManager::LoadSoundEffect(const char *file, std::string name)
{
    if(Mix_Chunk* soundEffect = Mix_LoadWAV(file))
    {
        soundEffectSheet.emplace(name, soundEffect);
        std::string str = " soundEffect loaded";
        SDL_Log("%s", (name + str).c_str());
        return true;
    }
    else
    {
        std::string str = "Fail to load soundEffect ";
        SDL_Log("%s", (str + name).c_str());
        return false;
    }
}

bool ResourceManager::LoadMusic(const char *file, std::string name)
{
    if(Mix_Music* music = Mix_LoadMUS(file))
    {
        musicSheet.emplace(name, music);
        std::string str = " music loaded";
        SDL_Log("%s", (name + str).c_str());
        return true;
    }
    else
    {
        std::string str = "Fail to load music ";
        SDL_Log("%s", (str + name).c_str());
        return false;
    }
}

bool ResourceManager::LoadText(const char *file)
{
    std::ifstream in(file);
    std::string line;
    int stringCode = 0;
    
    if(in)
    {
        while(std::getline(in, line))
        {
            textSheet.emplace(stringCode, line);
            ++stringCode;
        }
        SDL_Log("Language package loaded");
        return true;
    }
    SDL_Log("Fail to load language package");
    return false;
}
