#ifndef FP_SIZE_2D_H
#define FP_SIZE_2D_H

namespace fp
{

template<typename T>
struct Size2D
{
    Size2D() : w(0), h(0) {}
    Size2D(T _w, T _h) : w(_w), h(_h) {}
    T w;
    T h;
};

template<typename T>
Size2D<T> operator*(const Size2D<T>& vec, unsigned int val)
{
    return Size2D<T>(vec.w * val, vec.h * val);
}

} // namespace fp
#endif