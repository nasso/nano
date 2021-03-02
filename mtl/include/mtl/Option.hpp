/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Option
*/

#ifndef OPTION_HPP_
#define OPTION_HPP_

#include <cassert>
#include <utility>

namespace mtl {

template <typename T>
class Option {
public:
    static const Option<T> NONE();

    Option(const T& val)
        : m_some(true)
    {
        new (&m_value) T(val);
    }

    Option(T&& val)
        : m_some(true)
    {
        new (&m_value) T(std::move(val));
    }

    template <class... Args>
    Option(Args&&... args)
    {
        emplace(std::forward<Args>(args)...);
    }

    Option()
    {
    }

    Option(const Option<T>& other)
    {
        *this = other;
    }

    Option(Option<T>&& other)
        : m_some(other.m_some)
    {
        if (m_some) {
            new (&m_value) T(std::move(other.m_value));
        }
    }

    ~Option()
    {
        clear();
    }

    template <typename V>
    Option<T>& operator=(V&& other)
    {
        emplace(std::forward<V>(other));

        return *this;
    }

    template <class... Args>
    void emplace(Args&&... args)
    {
        clear();
        new (&m_value) T(std::forward<Args>(args)...);
        m_some = true;
    }

    void clear()
    {
        if (m_some) {
            (**this).~T();
            m_some = false;
        }
    }

    bool some() const
    {
        return m_some;
    }

    T& operator*()
    {
        assert(m_some);
        return reinterpret_cast<T&>(m_value);
    }

    const T& operator*() const
    {
        assert(m_some);
        return reinterpret_cast<const T&>(m_value);
    }

    T&& take()
    {
        assert(m_some);
        m_some = false;
        return std::move(reinterpret_cast<T&>(m_value));
    }

private:
    bool m_some = false;
    alignas(T) unsigned char m_value[sizeof(T)];
};

}

#endif /* !OPTION_HPP_ */
