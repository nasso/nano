/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Tristate
*/

#ifndef TRISTATE_HPP_
#define TRISTATE_HPP_

#include <cstdint>
#include <iostream>

namespace nts {

class Tristate {
public:
    static const Tristate TRUE;
    static const Tristate FALSE;
    static const Tristate UNDEFINED;

    constexpr Tristate()
        : m_value(Value::UNDEFINED)
    {
    }

    constexpr Tristate(const Tristate& other)
        : m_value(other.m_value)
    {
    }

    Tristate operator&&(const Tristate&) const;
    Tristate operator||(const Tristate&) const;
    Tristate operator!() const;

    Tristate& operator|=(const Tristate&);
    Tristate& operator&=(const Tristate&);

    bool operator==(const Tristate&) const;
    bool operator!=(const Tristate&) const;

private:
    enum class Value {
        UNDEFINED = std::uint8_t(-1),
        FALSE = 0,
        TRUE = 1,
    };

    constexpr Tristate(Value val)
        : m_value(val)
    {
    }

    Value m_value;
};

std::ostream& operator<<(std::ostream&, const nts::Tristate&);

}

#endif /* !TRISTATE_HPP_ */
