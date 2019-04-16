#ifndef FP_VALUE_H
#define FP_VALUE_H

namespace fp
{

template< class T >
class Value
{
public:
    Value() : 
        m_value(),
        m_hasChanged(false)
    {}

    void set(const T& newVal)
    {
        if( m_value != newVal)
        {
            m_hasChanged = true;
            m_value = newVal;
        }
    }

    const T& value() const
    {
        return m_value;
    }

    bool hasChanged() const
    {
        return m_hasChanged;
    }

    void resetState()
    {
        m_hasChanged = false;
    }

private:
    T m_value;
    bool m_hasChanged;
};

} // namespace fp
#endif