#ifndef FP_GFX_TYPES_H
#define FP_GFX_TYPES_H

#include "FpVector2D.h"
#include "FpSize2D.h"
#include <cstdint>
#include <type_traits> // make_signed

namespace fp
{
namespace gfx
{

using Pixel = uint32_t;
using Coord = fp::Vector2d<Pixel>;
using Resolution = fp::Vector2d<Pixel>;
using Size2D = fp::Size2D<Pixel>;
using Offset2D = fp::Vector2d< typename std::make_signed<Pixel>::type >;
struct Rectangle
{
    Rectangle(const Coord& upperLeft_, const Coord& lowerRight_) :
        upperLeft(upperLeft_),
        lowerRight(lowerRight_)
        {}
    Rectangle(const Coord& upperLeft_, const Size2D& size) : 
        upperLeft(upperLeft_), 
        lowerRight({upperLeft_.x + size.w -1, upperLeft.y + size.h - 1})
        {}
    Pixel getNumPixels() const { return (lowerRight.x - upperLeft.x + 1) * (lowerRight.y - upperLeft.y + 1); }
    Pixel width() const{return lowerRight.x - upperLeft.x + 1;}
    Pixel height() const{return lowerRight.y - upperLeft.y + 1;}
    Coord upperLeft;
    Coord lowerRight;
};

} // namespace gfx
} // namespace fp
inline fp::gfx::Coord operator+(const fp::gfx::Coord& pix, const fp::gfx::Offset2D& off)
{
    return fp::gfx::Coord(pix.x + off.x, pix.y + off.y);
}

#endif