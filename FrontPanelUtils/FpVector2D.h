#ifndef FP_VECTOR_2D_H
#define FP_VECTOR_2D_H

#include <cstdint>
#include <limits>

namespace fp
{

template<typename T>
struct Vector2d
{
    constexpr Vector2d() noexcept:
        x(0),
        y(0)
    {}
    constexpr Vector2d(const Vector2d& other) noexcept:
        x(other.x),
        y(other.y)
    {}
    constexpr Vector2d(const T& _x, const T& _y) noexcept:
        x(_x),
        y(_y)
    {}
    constexpr bool operator!=(const Vector2d<T>& rhs) const noexcept
    {
        return (x != rhs.x) || (y != rhs.y);
    }
    constexpr bool operator==(const Vector2d<T>& rhs) const noexcept
    {
        return (x == rhs.x) && (y == rhs.y);
    }
    constexpr Vector2d& operator=(const T& val) noexcept
    {
        x = val;
        y = val;
        return *this;
    }
    constexpr Vector2d operator+(const Vector2d<T>& rhs) const noexcept
    {
        return Vector2d(x + rhs.x, y + rhs.y);
    }

    constexpr Vector2d inc() const noexcept
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