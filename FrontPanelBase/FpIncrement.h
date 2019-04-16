#ifndef FP_INCREMENT_H
#define FP_INCREMENT_H

namespace fp
{

template< class T >
class Increment
{
public:
    Increment() : 
        m_increment()
    {}

    void set(const T& increment)
    {
        m_increment += increment;
    }

    const T& value() const
    {
        return m_increment;
    }

    bool hasChanged() const
    {
        return 0 != m_increment;
    }

    void resetState()
    {
        m_increment = 0;
    }

private:
    T m_increment;
};

} // namespace fp
#endif