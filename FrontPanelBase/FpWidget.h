#ifndef FP_WIDGET_H
#define FP_WIDGET_H

#include "FpVector2D.h"

namespace fp
{

const uint8_t IdxAll = Vector2d<uint8_t>::ALL;


struct Widget
{
    Widget(uint8_t _id, const Vector2d<uint8_t>& _vec = {0,0}) :
       id(_id),
       coord(_vec)
    {}
    Widget(uint8_t _id, uint8_t x) :
       id(_id),
       coord({x, 0})
    {}
    Widget(uint8_t _id, uint8_t x, uint8_t y) :
       id(_id),
       coord({x, y})
    {}
    bool operator==(const Widget& rhs) const noexcept
    {
       return (id == rhs.id) && (coord == rhs.coord);
    }
    bool operator<(const Widget& rhs) const noexcept
    {
       if(id < rhs.id) return true;
       if(coord.x < rhs.coord.x) return true;
       return coord.y < rhs.coord.y;
    }
    uint8_t id;
    Vector2d<uint8_t> coord;
};

template<class WTopology, typename Function>
void forWidget(const Widget& w, Function&& f)
{
   if(w.id > WTopology::Id::eLast)
   {
      return;
   }
   const auto DIM = WTopology::getDim(static_cast<typename WTopology::Id>(w.id));
   Vector2d<uint8_t> start(w.coord);
   Vector2d<uint8_t> end(w.coord.inc());
   if(w.coord.x == Vector2d<uint8_t>::ALL)
   {
      start.x = 0;
      end.x = DIM.x;
   }
   if(w.coord.y == Vector2d<uint8_t>::ALL)
   {
      start.y = 0;
      end.y = DIM.y;                
   }
   for(auto x = start.x; x < end.x; ++x)
   {
      for(auto y = start.y; y < end.y; ++y)
      {
         f(Widget(w.id, Vector2d<uint8_t>(x, y)));
      }
   } 
}

} //namespace fp
#endif