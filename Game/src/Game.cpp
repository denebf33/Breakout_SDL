/**@file  Game.cpp
* @brief       Scouce code of Game
* @details  Defined the specific game logic-related class and functions.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/

#include "Game.hpp"

Game::Game(int width, int height, SDL_Renderer* renderer, std::string lang):state(GameState::GAME_MENU), width(width), height(height), renderer(renderer), lang(lang)
{
    
}
Game::~Game()
{
    SDL_DestroyTexture(backgroundTexture);
    delete player;
    delete ball;
    for(auto txt : textFields)
    {
        delete txt.second;
    }
    for(auto l : levels)
    {
        delete l;
    }
}

void Game::Init()
{
    ResourceManager::GetInstance()->startUp(lang);

    GameLevel* one = new GameLevel();
    one->Load(1, this->width, this->height / 2, this->renderer);
    GameLevel* two = new GameLevel();
    two->Load(2, this->width, this->height / 2, this->renderer);
    GameLevel* three = new GameLevel();
    three->Load(3, this->width, this->height / 2, this->renderer);
    GameLevel* four = new GameLevel();
    four->Load(4, this->width, this->height / 2, this->renderer);
    
    this->levels.push_back(one);
    this->levels.push_back(two);
    this->levels.push_back(three);
    this->levels.push_back(four);
    this->level = 0;
    
    this->score = 0;
    
    backgroundTexture = SDL_CreateTextureFromSurface(this->renderer, ResourceManager::GetInstance()->GetSurface("background"));
    
    TinyMath::Vec2 playerPos = TinyMath::Vec2(this->width / 2 - PLAYER_SIZE.x / 2, this->height - PLAYER_SIZE.y);
    player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetInstance()->GetSurface("paddle"), renderer);
    
    TinyMath::Vec2 ballPos = playerPos + TinyMath::Vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetInstance()->GetSurface("face"), renderer);
    
    TextField* lifeField = new TextField(TinyMath::Vec2(0, 0), this->renderer, ResourceManager::GetInstance()->GetFont("scoreFont"), lang, width, height);
    textFields.emplace("lifeField", lifeField);
    
    TextField* scoreField = new TextField(TinyMath::Vec2(width - 100, 0), this->renderer, ResourceManager::GetInstance()->GetFont("scoreFont"), lang, width, height);
    textFields.emplace("scoreField", scoreField);
    
    TinyMath::Vec2 notice1Pos(120, 300);
    TinyMath::Vec2 notice2Pos(160, 350);
    TinyMath::Vec2 resultPos(280, 250);
    
    if(lang == "Chinese")
    {
        notice1Pos = TinyMath::Vec2(240, 300);
        notice2Pos = TinyMath::Vec2(280, 350);
        resultPos = TinyMath::Vec2(400, 250);
    }
    
    TextField* noticeField1 = new TextField(notice1Pos, this->renderer, ResourceManager::GetInstance()->GetFont("noticeFont1"), lang, width, height, true);
    textFields.emplace("noticeField1", noticeField1);
    
    TextField* noticeField2 = new TextField(notice2Pos, this->renderer, ResourceManager::GetInstance()->GetFont("scoreFont"), lang, width, height, true);
    textFields.emplace("noticeField2", noticeField2);
    
    TextField* resultField = new TextField(resultPos, this->renderer, ResourceManager::GetInstance()->GetFont("resultFont"), lang, width, height, true);
    textFields.emplace("resultField", resultField);
    
    textFields["lifeField"]->SetText(ResourceManager::GetInstance()->GetString(0) + std::to_string(this->lives));
    textFields["scoreField"]->SetText(ResourceManager::GetInstance()->GetString(1) + std::to_string(this->score));
    textFields["noticeField1"]->SetText(ResourceManager::GetInstance()->GetString(2));
    textFields["noticeField2"]->SetText(ResourceManager::GetInstance()->GetString(3));
    
    Mix_PlayMusic(ResourceManager::GetInstance()->GetMusic("bgm"), -1);
}

void Game::Render()
{
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    this->levels[this->level]->Draw();
    player->Draw();
    ball->Draw();
    textFields["lifeField"]->Draw();
    textFields["scoreField"]->Draw();
    
    if(this->state == GameState::GAME_MENU || this->state == GameState::GAME_END)
    {
        textFields["noticeField1"]->Draw();
        textFields["noticeField2"]->Draw();
    }
    
    if(this->state == GameState::GAME_END)
    {
        textFields["resultField"]->Draw();
    }
}

void Game::ProcessInput(float dt, const bool buttons[3])
{
    float localDt = dt/1000.0f;
    if(this->state == GameState::GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * localDt;
        
        if(buttons[Buttons::PaddleLeft])
        {
            if(player->dest.x >= 0)
            {
                player->dest.x -= velocity;
                if(ball->stuck)
                    ball->dest.x -= velocity;
            }
        }
        if(buttons[Buttons::PaddleRight])
        {
            if(player->dest.x <= this->width - player->dest.w)
            {
                player->dest.x += velocity;
                if(ball->stuck)
                    ball->dest.x += velocity;
            }
        }
        if(buttons[Buttons::Confirm])
            ball->stuck = false;
    }
    
    if(this->state == GameState::GAME_MENU || this->state == GameState::GAME_END)
    {
        if(buttons[Buttons::PaddleRight] && !rightKeyBool)
        {
            rightKeyBool = true;
            this->level = (this->level + 1) % 4;
        }
        
        if(!buttons[Buttons::PaddleRight])
            rightKeyBool = false;
            
        
        if(buttons[Buttons::PaddleLeft] && !leftKeyBool)
        {
            leftKeyBool = true;
            if(this->level > 0)
                --this->level;
            else
                this->level = 3;
        }
        if(!buttons[Buttons::PaddleLeft])
            leftKeyBool = false;
        
        if(buttons[Buttons::Confirm])
        {
            this->state = GameState::GAME_ACTIVE;
        }
    }
}

void Game::Update(float dt)
{
    float localDt = dt / 1000.0f;
    
    ball->Move(localDt, this->width);
    this->DoCollisions();
    
    if(ball->dest.y >= this->height)
    {
        --this->lives;
        std::stringstream ss;
        ss << this->lives;
        textFields["lifeField"]->SetText(ResourceManager::GetInstance()->GetString(0) + ss.str());
        
        if(this->lives == 0)
        {
            this->ResetLevel();
            this->state = GameState::GAME_END;
            textFields["resultField"]->SetText(ResourceManager::GetInstance()->GetString(4));
        }
        this->ResetPlayer();
    }
    
    if(this->state == GameState::GAME_ACTIVE && this->levels[this->level]->IsCompleted())
    {
        this->ResetPlayer();
        this->ResetLevel();
        this->state = GameState::GAME_END;
        textFields["resultField"]->SetText(ResourceManager::GetInstance()->GetString(5));
    }
}

TinyMath::Collision CheckCollision(BallObject &one, GameObject &two)
{
    TinyMath::Vec2 center(one.dest.x + one.radius, one.dest.y + one.radius);
    
    TinyMath::Vec2 aabb_half_extents(two.dest.w / 2, two.dest.h / 2);
    TinyMath::Vec2 aabb_center(two.dest.x + aabb_half_extents.x, two.dest.y + aabb_half_extents.y);
    
    TinyMath::Vec2 difference = center - aabb_center;
    TinyMath::Vec2 clamped = Clamp(difference, TinyMath::Vec2(0, 0) - aabb_half_extents, aabb_half_extents);
    TinyMath::Vec2 closest = aabb_center + clamped;
    
    difference = closest - center;
    
    if(TinyMath::Length(difference) <= one.radius && !(difference.x == 0 && difference.y == 0))
    {
        return std::make_tuple(true, TinyMath::VectorDirection(difference), difference);
    }
    else
        return std::make_tuple(false, TinyMath::Direction::UP, TinyMath::Vec2(0, 0));
}

void Game::DoCollisions()
{
    // Wall collision
    for(GameObject* box : this->levels[this->level]->Bricks)
    {
        if(!box->destroyed)
        {
            TinyMath::Collision collision = CheckCollision(*ball, *box);
            if(std::get<0>(collision))
            {
                if(!box->isSolid)
                {
                    box->destroyed = true;
                    std::string str;
                        
                    this->textFields["scoreField"]->SetText(ResourceManager::GetInstance()->GetString(1) + std::to_string(++this->score));
                    Mix_PlayChannel(-1, ResourceManager::GetInstance()->GetSoundEffect("bleepBrick"), 0);
                }
                else
                {
                    Mix_PlayChannel(-1, ResourceManager::GetInstance()->GetSoundEffect("bleepSolid"), 0);
                }
                
                TinyMath::Direction dir = std::get<1>(collision);
                TinyMath::Vec2 diff_vector = std::get<2>(collision);
                
                if(dir == TinyMath::Direction::LEFT || dir == TinyMath::Direction::RIGHT)
                {
                    ball->velocity.x = -ball->velocity.x;
                    float penetration = ball->radius - std::abs(diff_vector.x);
                    
                    if(dir == TinyMath::Direction::LEFT)
                        ball->dest.x += penetration;
                    else
                        ball->dest.x -= penetration;
                }
                else
                {
                    ball->velocity.y = -ball->velocity.y;
                    float penetration = ball->radius - std::abs(diff_vector.y);
                    
                    if(dir == TinyMath::Direction::UP)
                        ball->dest.y -= penetration;
                    else
                        ball->dest.y += penetration;
                }
            }
        }
    }
    
    //Player collision
    TinyMath::Collision result = CheckCollision(*ball, *player);
    if(!ball->stuck && std::get<0>(result))
    {
        float centerBoard = player->dest.x + player->dest.w / 2;
        float distance = (ball->dest.x + ball->radius) - centerBoard;
        float percentage = distance / (player->dest.w / 2);
        
        float strength = 2.0f;
        TinyMath::Vec2 lastVelocity = ball->velocity;
        ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        ball->velocity.y = -1 * abs(ball->velocity.y);
        ball->velocity = TinyMath::Normalize(ball->velocity) * TinyMath::Length(lastVelocity);
        
        Mix_PlayChannel(-1, ResourceManager::GetInstance()->GetSoundEffect("bleepPaddle"), 0);
    }
}

void Game::ResetLevel()
{
    if(this->level == 0)
        this->levels[0]->Load(1, this->width, this->height / 2, renderer);
    else if(this->level == 1)
        this->levels[1]->Load(2, this->width, this->height / 2, renderer);
    if(this->level == 2)
        this->levels[2]->Load(3, this->width, this->height / 2, renderer);
    if(this->level == 3)
        this->levels[3]->Load(4, this->width, this->height / 2, renderer);
    
    this->lives = 3;
    this->score = 0;
    this->textFields["lifeField"]->SetText(ResourceManager::GetInstance()->GetString(0) + std::to_string(this->lives));
    this->textFields["scoreField"]->SetText(ResourceManager::GetInstance()->GetString(1) + std::to_string(this->score));
}

void Game::ResetPlayer()
{
    player->dest.w = PLAYER_SIZE.x;
    player->dest.h = PLAYER_SIZE.y;
    player->dest.x = this->width / 2 - PLAYER_SIZE.x / 2;
    player->dest.y = this->height - PLAYER_SIZE.y;
    
    ball->Reset(TinyMath::Vec2(player->dest.x, player->dest.y) + TinyMath::Vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}
