#ifndef FP_CALLBACK_STACK_H
#define FP_CALLBACK_STACK_H

#include <cstdint> // uint8_t
#include <array>
#include <optional>

namespace fp
{

template <class Data, unsigned int Size>
class CallbackStack
{
public:
    CallbackStack() :
        m_data(),
        m_topIndex(0),
        m_botIndex(0)
    {}
    void pushBack(const Data& data)
    {
        if(m_data[m_topIndex])
        {
            incTopIndex();
        }
        m_data[m_topIndex] = data;
    }
    std::optional<Data> getActual() const
    {
        return actual();
    }
    std::optional<Data>& actual()
    {
        return m_data[m_topIndex];
    }
    const std::optional<Data>& actual() const
    {
        return m_data[m_topIndex];
    }

    void remove(const Data& data)
    {
        uint8_t const tmpTopIndex = m_topIndex;
        if(m_data[m_topIndex] == data)
        {
            m_data[m_topIndex].reset();
            decTopIndex();
        }
        for(uint8_t i = decIndex(tmpTopIndex); i != decIndex(m_botIndex); i = decIndex(i))
        {
            if(m_data[i] == data)
            {
                for(uint8_t j = i; j != tmpTopIndex; j = incIndex(j))
                {
                    m_data[j] = m_data[incIndex(j)];
                    m_data[incIndex(j)].reset();
                }
                decTopIndex();
            }
        }
    }
private:
    std::array<std::optional<Data>, Size> m_data;
    int8_t  m_topIndex;
    int8_t  m_botIndex;
    void incTopIndex()
    {
        m_topIndex = incIndex(m_topIndex); 
        if(m_topIndex == m_botIndex)
        { 
            m_botIndex = incIndex(m_botIndex);
        }
    }
    void decTopIndex()
    {
        if(m_topIndex != m_botIndex)
        {
            m_topIndex = decIndex(m_topIndex);
        }
    }
    uint8_t incIndex(uint8_t index)
    {
        ++index;
        if(index >= Size)
        {
            index=0;
        }
        return index;
    }
    uint8_t decIndex(uint8_t index)
    {
        if(index == 0)
        {
            index = Size - 1;
        }
        else
        {
            --index;
        }
        return index;
    }
};

template <class Data>
class CallbackStack<Data, 0>
{
};

template <class Data>
class CallbackStack<Data, 1>
{
public:
    void pushBack(const Data& data)
    {
        m_data = data;
    }
    std::optional<Data> getActual() const
    {
        return actual();
    }
    std::optional<Data>& actual()
    {
        return m_data;
    }
    const std::optional<Data>& actual() const
    {
        return m_data;
    }
    void remove(const Data& data)
    {
        if(m_data == data)
        {
            m_data.reset();
        } 
    }
private:
    std::optional<Data> m_data;
};

template <class Data>
class CallbackStack<Data, 2>
{
public:
    void pushBack(const Data& data)
    {
        if(m_data[1])
        {
            m_data[0] = m_data[1];
            m_data[1] = data;
        }
        else if(m_data[0])
        {
            m_data[1] = data;
        }
        else
        {
            m_data[0] = data;
        }
    }
    std::optional<Data> getActual()
    {
        return actual();
    }
    std::optional<Data>& actual()
    {
        if(m_data[1])
        {
            return m_data[1];
        }
        else
        {
            return m_data[0];
        }
    }
    const std::optional<Data>& actual() const
    {
        if(m_data[1])
        {
            return m_data[1];
        }
        else
        {
            return m_data[0];
        }
    }
    void remove(const Data &data)
    {
        if(m_data[1] == data)
        {
            m_data[1].reset();
        }
        if(m_data[0] == data)
        {
            m_data[0] = m_data[1];
            m_data[0].reset();
        }
    }
private:
    std::array<std::optional<Data>, 2> m_data;
};

} // namespace fp
#endif