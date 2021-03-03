/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Option
*/

#ifndef OPTION_HPP_
#define OPTION_HPP_

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>

namespace mtl {

template <typename T>
class Option {
public:
    static const Option<T> NONE();

    Option()
        : m_some(false)
    {
    }

    Option(T&& value)
        : m_some(false)
    {
        emplace(std::forward<T>(value));
    }

    Option(const Option<T>& other)
        : m_some(false)
    {
        *this = other;
    }

    Option(Option<T>&& other)
        : m_some(false)
    {
        *this = std::forward<Option<T>>(other);
    }

    template <std::enable_if_t<std::is_reference<T>, bool> = true>
    ~Option()
    {
        if (is_some()) {
            (**this).~T();
        }
    }

    operator bool() const
    {
        return is_some();
    }

    Option<T>& operator=(const Option<T>& other)
    {
        if (other) {
            emplace(*other);
        } else {
            take();
        }

        return *this;
    }

    Option<T>& operator=(Option<T>&& other)
    {
        if (other) {
            emplace(std::move(other.unwrap()));
        } else {
            take();
        }

        return *this;
    }

    template <class... Args>
    Option<T> emplace(Args&&... args)
    {
        static_assert(std::is_constructible<T, Args...>::value,
            "Cannot construct T");

        Option<T> old_val = take();
        new (&m_value) T(std::forward<Args>(args)...);
        m_some = true;
        return std::move(old_val);
    }

    Option<T> take()
    {
        if (m_some) {
            Option<T> val(std::forward<T>(unwrap()));

            m_some = false;
            return std::move(val);
        } else {
            return {};
        }
    }

    bool is_some() const
    {
        return m_some;
    }

    bool is_none() const
    {
        return !m_some;
    }

    T unwrap()
    {
        assert(m_some);
        m_some = false;
        return std::move(reinterpret_cast<T&>(m_value));
    }

    T unwrap_or(T val)
    {
        if (*this) {
            return std::forward<T>(unwrap());
        } else {
            return std::forward<T>(val);
        }
    }

    T unwrap_or_default()
    {
        static_assert(std::is_default_constructible<T>::value,
            "No default constructor for T");

        if (*this) {
            return std::forward<T>(unwrap());
        } else {
            return {};
        }
    }

    template <typename F>
    auto unwrap_or_else(F&& f) -> T
    {
        if (*this) {
            return std::forward<T>(unwrap());
        } else {
            return std::forward<T>(f());
        }
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

    bool operator==(const Option<T>& other) const
    {
        if (is_none() && other.is_none()) {
            return true;
        }

        return **this == *other;
    }

    template <typename F>
    auto map(F&& f) -> Option<decltype(f(unwrap()))>
    {
        if (is_some()) {
            return { f(unwrap()) };
        } else {
            return {};
        }
    }

    Option<T&> as_ref()
    {
        if (is_some()) {
            return { **this };
        } else {
            return {};
        }
    }

private:
    bool m_some = false;
    alignas(T) unsigned char m_value[sizeof(T)];
};

}

#endif /* !OPTION_HPP_ */
