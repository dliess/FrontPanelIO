#ifndef FP_INCREMENT_H
#define FP_INCREMENT_H

#include <type_traits>
namespace fp
{


template< class T, std::enable_if_t<std::is_integral<T>::value, bool> = true >
class Increment
{
public:
    void set(const T& increment) noexcept
    {
        m_increment += increment;
    }

    T value() const noexcept
    {
        return m_increment / static_cast<T>(m_divider);
    }

    bool hasChanged() const noexcept
    {
        return value() != 0;
    }

    void resetState() noexcept
    {
        m_increment = m_increment % static_cast<T>(m_divider);
    }

    void setDivider(const std::make_unsigned_t<T>& divider) noexcept
    {
        if(divider > 0)
        {
            m_divider = divider;
        }
    }

private:
    T m_increment {0};
    std::make_unsigned_t<T> m_divider {1};
};

} // namespace fp
#endif