/**@file  TinyMath.cpp
* @brief       Source code of TinyMath
* @details  Defined classes and functions of vector calculations.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/
#include "TinyMath.hpp"

TinyMath::Vec3::Vec3():x(0.0f), y(0.0f), z(0.0f){}
TinyMath::Vec3::Vec3(int x, int y, int z):x(x), y(y), z(z){}

TinyMath::Vec3 TinyMath::Vec3::operator+(const Vec3& rhs)
{
    return  Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

TinyMath::Vec3& TinyMath::Vec3::operator+=(const Vec3 &rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    
    return *this;
}

TinyMath::Vec3 TinyMath::Vec3::operator*(int rhs)
{
    return Vec3(x * rhs, y * rhs, z * rhs);
}

TinyMath::Vec2::Vec2():x(0.0f), y(0.0f){}
TinyMath::Vec2::Vec2(float x, float y):x(x), y(y){}

TinyMath::Vec2 TinyMath::Vec2::operator+(const Vec2& rhs)
{
    return  Vec2(x + rhs.x, y + rhs.y);
}

TinyMath::Vec2 TinyMath::Vec2::operator+(float rhs)
{
    return  Vec2(x + rhs, y + rhs);
}

TinyMath::Vec2& TinyMath::Vec2::operator+=(const Vec2 &rhs)
{
    x += rhs.x;
    y += rhs.y;
    
    return *this;
}

TinyMath::Vec2 TinyMath::Vec2::operator*(float rhs)
{
    return Vec2(x * rhs, y * rhs);
}

TinyMath::Vec2 TinyMath::Vec2::operator-(const Vec2& rhs)
{
    return TinyMath::Vec2(x - rhs.x, y - rhs.y);
}

TinyMath::Vec2 TinyMath::Clamp(TinyMath::Vec2 value, TinyMath::Vec2 min, TinyMath::Vec2 max)
{
    return TinyMath::Vec2(std::max(min.x, std::min(max.x, value.x)), std::max(min.y, std::min(max.y, value.y)));
}

float TinyMath::Length(TinyMath::Vec2 vec)
{
    return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
}

TinyMath::Vec2 TinyMath::Normalize(Vec2 vec)
{
    float mod = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
    return Vec2(vec.x / mod, vec.y / mod);
}

float TinyMath::Dot(Vec2 vec1, Vec2 vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

TinyMath::Direction TinyMath::VectorDirection(TinyMath::Vec2 target)
{
    Vec2 compass[] =
    {
        Vec2(0.0f, 1.0f),
        Vec2(1.0f, 0.0f),
        Vec2(0.0f, -1.0f),
        Vec2(-1.0f, 0.0f)
    };
    float max = 0.0f;
    int best_match = -1;
    for(int i = 0; i < 4; i++)
    {
        float dot_product = TinyMath::Dot(TinyMath::Normalize(target), compass[i]);
        if(dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}
