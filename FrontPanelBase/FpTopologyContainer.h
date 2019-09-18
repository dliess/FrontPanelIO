#ifndef FP_TOPOLOGY_CONTAINER_H
#define FP_TOPOLOGY_CONTAINER_H

#include <cstdint>
#include "FpWidget.h"

namespace fp
{

template <class DataType, class Topology>
class TopologyContainer
{
public:
    TopologyContainer()
    {
        for(int i = 0; i <=  static_cast<int>(Topology::Id::eLast); ++i)
        {
            const typename Topology::Id wId = static_cast<typename Topology::Id>(i);
            m_holder[i] = new DataType[Topology::getDim(wId).x * Topology::getDim(wId).y](); //the () at the end is for zero initialization
        }
    }
    ~TopologyContainer()
    {
        for(int i = 0; i <=  Topology::Id::eLast; ++i)
        {
            delete[] m_holder[i];
        }
    }
    TopologyContainer(const TopologyContainer&) = delete;

    TopologyContainer(TopologyContainer&& rhs)
    {
        for(int i = 0; i <=  Topology::Id::eLast; ++i)
        {
            m_holder[i] = rhs.m_holder[i];
            rhs.m_holder[i] = nullptr;
        }
    }

    DataType *get(const Widget &w)
    {
        if(w.id > Topology::Id::eLast)
        {
            return nullptr;
        }
        const auto wId = static_cast<typename Topology::Id>(w.id);
        if(w.coord.x >= Topology::getDim(wId).x || w.coord.y >= Topology::getDim(wId).y)
        {
            return nullptr;
        }
        return &(m_holder[wId][w.coord.x * Topology::getDim(wId).y + w.coord.y]);
    }

    const DataType *get(const Widget &w) const
    {
        if(w.id > Topology::Id::eLast)
        {
            return nullptr;
        }
        const auto wId = static_cast<typename Topology::Id>(w.id);
        if(w.coord.x >= Topology::getDim(wId).x || w.coord.y >= Topology::getDim(wId).y)
        {
            return nullptr;
        }
        return &(m_holder[wId][w.coord.x * Topology::getDim(wId).y + w.coord.y]);
    }

    template<class Visitor>
    void forEach(Visitor&& visitor)
    {
        for(int i = 0; i <=  static_cast<int>(Topology::Id::eLast); ++i)
        {
            const typename Topology::Id wId = static_cast<typename Topology::Id>(i);
            const auto DIM = Topology::getDim(wId);
            for(uint8_t x = 0; x < DIM.x; ++x)
            {
                for(uint8_t y = 0; y < DIM.y; ++y)
                {
                    Widget widget(wId, Vector2d<uint8_t>(x, y));
                    DataType* data = get(widget);
                    if(data)
                    {
                        visitor(*data, widget);
                    }
                }
            }
        }
    }
    template<class Visitor>
    void forWidget(const Widget &widget, Visitor&& visitor)
    {
        if(widget.id > Topology::Id::eLast)
        {
            return;
        }
        const auto DIM = Topology::getDim(static_cast<typename Topology::Id>(widget.id));
        Vector2d<uint8_t> start(widget.coord);
        Vector2d<uint8_t> end(widget.coord.inc());
        if(widget.coord.x == Vector2d<uint8_t>::ALL)
        {
            start.x = 0;
            end.x = DIM.x;
        }
        if(widget.coord.y == Vector2d<uint8_t>::ALL)
        {
            start.y = 0;
            end.y = DIM.y;                
        }
        for(auto x = start.x; x < end.x; ++x)
        {
            for(auto y = start.y; y < end.y; ++y)
            {
                Widget actWidget(widget.id, Vector2d<uint8_t>(x, y));
                DataType* data = get(actWidget);
                if(data)
                {
                    visitor(*data, actWidget);
                }
            }
        }
    }
private:
    DataType* m_holder[Topology::Id::eLast+1];
};

} // namespace fp
#endif