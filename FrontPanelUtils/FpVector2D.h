#ifndef FP_VECTOR_2D_H
#define FP_VECTOR_2D_H

#include <cstdint>
#include <limits>

namespace fp
{

template<typename T>
struct Vector2d
{
    Vector2d() :
        x(0),
        y(0)
    {}
    Vector2d(const Vector2d& other) :
        x(other.x),
        y(other.y)
    {}
    Vector2d(const T& _x, const T& _y) :
        x(_x),
        y(_y)
    {}
    bool operator!=(const Vector2d<T>& rhs) const
    {
        return (x != rhs.x) || (y != rhs.y);
    }
    bool operator==(const Vector2d<T>& rhs) const
    {
        return (x == rhs.x) && (y == rhs.y);
    }
    Vector2d& operator=(const T& val)
    {
        x = val;
        y = val;
        return *this;
    }
    Vector2d operator+(const Vector2d<T>& rhs) const
    {
        return Vector2d(x + rhs.x, y + rhs.y);
    }

    Vector2d inc() const
    {
        return Vector2d(x+1, y+1);
    }
    T x;
    T y;
    static const T ALL;
};

template<typename T>
Vector2d<T> operator*(const Vector2d<T>& vec, unsigned int val)
{
    return Vector2d<T>(vec.x * val, vec.y * val);
}


// This makes linker happy
template<typename T>
const T Vector2d<T>::ALL = std::numeric_limits<T>::max();

} // namespace fp
#endif