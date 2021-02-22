/**@file  TinyMath.hpp
* @brief       Header of TinyMath.cpp
* @details  Declared a namespace of vector calculations.
* @author     JunfengZhou
* @date        2021-2-22
* @version     V1.0
**********************************************************************************
* @attention
* Platform: MacOS \n
*
**********************************************************************************
*/
#ifndef TinyMath_hpp
#define TinyMath_hpp

#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <iostream>

/**@brief Namespace of TinyMath.
 *  This namespace contains all computation-realated enums/ functions/ classs/ types\n
 *  Make sure use TinyMath:: before call members in this namespace.
 */
namespace TinyMath{
/**@enum Direction
 *@brief Define Direnction enum.
*/
enum Direction{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

/**@class Vec3
 *@brief Class of three-dimensional vectors.
 *@details Mainly used to represent colors.
*/
class Vec3{
public:
    int x, y, z;
    
    Vec3();
    Vec3(int x, int y, int z);
    
    Vec3 operator+(Vec3 const& rhs);
    Vec3& operator+=(Vec3 const& rhs);
    Vec3 operator*(int rhs);
};

/**@class Vec2
 *@brief Class of two-dimensional vectors.
 *@details Mainly used to represent position, size, velocity and direction.
*/
class Vec2{
public:
    float x, y;
    
    Vec2();
    Vec2(float x, float y);
    
    Vec2 operator+(Vec2 const& rhs);
    Vec2 operator+(float rhs);
    Vec2& operator+=(Vec2 const& rhs);
    Vec2 operator*(float rhs);
    Vec2 operator-(Vec2 const& rhs);
};

/**@brief Clamp a two-dimensional vector.
 *@param[in] value Two-dimensional vector that need to be clamped.
 *@param[in] min Lower limit of the new vector.
 *@param[in] max Upper limit of the new vector.
 *@return A two-dimensional vector that was clamped between min vector and max vector.
 *@par Example:
 *@code
 *  Clamp(Vec2(1, 3), Vec2(1, 1), Vec2(4, 3));
 *@endcode
*/
Vec2 Clamp(Vec2 value, Vec2 min, Vec2 max);

/**@brief Calculate the magnitude of a two-dimensional vector
 *@param[in] vec Two-dimensional vector that need to be calculated.
 *@return A float that represents the magnitude of vec.
 *@par Example:
 *@code
 *  Length(Vec2(1, 1);
 *@endcode
*/
float Length(Vec2 vec);

/**@brief Calculate the dot product of two two-dimensional vectors
 *@param[in] vec1 The first two-dimensional vector of the dot product.
 *@param[in] vec2 The second two-dimensional vector of the dot product.
 *@return A float of result of the dot product.
 *@par Example:
 *@code
 *  Dot(Vec2(1, 1), Vec2(3, 3));
 *@endcode
*/
float Dot(Vec2 vec1, Vec2 vec2);

/**@brief Normalize a two-dimensional vector
 *@param[in] vec The two-dimensional vector that need to be normalized.
 *@return A float of result of the dot product.
 *@par Example:
 *@code
 *  Normalize(Vec2(3, 3));
 *@endcode
*/
Vec2 Normalize(Vec2 vec);

/**@brief Calculate the corresponding bounce direction of a two-dimensional vector.
 *@param[in] target The two-dimensional vector to be calculated.
 *@return A enum of Direction.
 *@par Example:
 *@code
 *  VectorDirection(Vec2(0.6, 0.8));
 *@endcode
*/
Direction VectorDirection(Vec2 target);

/**@brief Define Collision type.
 *@details  This type stores information of each collision detection, including whether
 *  the collision detected, the direction of the collision, and the collision point.
 */
typedef std::tuple<bool, Direction, Vec2> Collision;
}

#endif /* TinyMath_hpp */
