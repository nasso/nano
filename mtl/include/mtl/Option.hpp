/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Option
*/

#ifndef MTL_OPTION_HPP_
#define MTL_OPTION_HPP_

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>

namespace mtl {

namespace {

    template <typename T>
    class Base;

    template <typename T>
    class Base<T&>;

    template <typename T>
    class Base<const T&>;

    template <typename T>
    class Base {
    public:
        constexpr Base() noexcept = default;

        ~Base()
        {
            clear();
        }

        // contains a value?
        bool is_some() const
        {
            return m_some;
        }

        // get a pointer to the contained value
        T* get()
        {
            if (m_some) {
                return reinterpret_cast<T*>(&m_value);
            } else {
                return nullptr;
            }
        }

        const T* get() const
        {
            if (m_some) {
                return reinterpret_cast<const T*>(&m_value);
            } else {
                return nullptr;
            }
        }

        // set to none
        void clear()
        {
            if (m_some) {
                get()->~T();
                m_some = false;
            }
        }

        // set to some
        template <typename... Args>
        void emplace(Args&&... args)
        {
            static_assert(std::is_constructible<T, Args...>::value,
                "Couldn't find a suitable constructor for T");

            new (&m_value) T(std::forward<Args>(args)...);
            m_some = true;
        }

    private:
        bool m_some = false;
        alignas(T) unsigned char m_value[sizeof(T)];
    };

    template <typename T>
    class Base<T&> {
        static_assert(sizeof(T) == 0, "optional mutable references disallowed");
    };

    template <typename T>
    class Base<const T&> {
    public:
        constexpr Base() noexcept = default;

        ~Base()
        {
            clear();
        }

        // contains a value?
        bool is_some() const
        {
            return m_value != nullptr;
        }

        // get a pointer to the contained value
        const T* get() const
        {
            return m_value;
        }

        // set to none
        void clear()
        {
            m_value = nullptr;
        }

        // set to some
        void emplace(const T& ref)
        {
            m_value = std::addressof(ref);
        }

    private:
        const T* m_value = nullptr;
    };

}

template <typename T>
class Option : Base<T> {
public:
    constexpr Option() noexcept = default;

    Option(const Option<T>& other)
    {
        *this = other;
    }

    Option(Option<T>&& other)
    {
        if (other) {
            emplace(std::move(other.unwrap()));
        }
    }

    Option<T>& operator=(const Option<T>& other)
    {
        if (other) {
            emplace(other.as_ref().unwrap());
        } else {
            take();
        }

        return *this;
    }

    bool operator==(const Option<T>& other) const
    {
        if (is_none() || other.is_none()) {
            return is_none() && other.is_none();
        }

        return as_ref().unwrap() == other.as_ref().unwrap();
    }

    operator bool() const
    {
        return is_some();
    }

    bool is_some() const
    {
        return Base<T>::is_some();
    }

    bool is_none() const
    {
        return !is_some();
    }

    T unwrap()
    {
        if (is_none()) {
            throw std::runtime_error("unwrap() called on a `none` value");
        }

        T val(std::forward<T>(*get()));

        clear();
        return std::forward<T>(val);
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
    T unwrap_or_else(F&& f)
    {
        if (*this) {
            return std::forward<T>(unwrap());
        } else {
            return std::forward<T>(f());
        }
    }

    Option<T> take()
    {
        if (*this) {
            Option<T> oldVal;
            oldVal.emplace(std::forward<T>(unwrap()));
            return oldVal;
        } else {
            return {};
        }
    }

    template <typename... Args>
    Option<T> replace(Args&&... args)
    {
        Option<T> oldVal = take();

        emplace(std::forward<Args>(args)...);

        return oldVal;
    }

    template <typename F>
    auto map(F&& f) -> Option<decltype(f(unwrap()))>
    {
        if (*this) {
            return mtl::some<decltype(f(unwrap()))>(f(unwrap()));
        } else {
            return {};
        }
    }

    Option<const T&> as_ref() const
    {
        if (*this) {
            return mtl::some<const T&>(*get());
        } else {
            return {};
        }
    }
};

template <typename T, typename... Args>
constexpr Option<T> some(Args&&... args)
{
    Option<T> opt;

    opt.replace(std::forward<Args>(args)...);
    return opt;
}

template <typename T>
constexpr Option<T> none() noexcept
{
    return {};
}

}

#endif /* !MTL_OPTION_HPP_ */
