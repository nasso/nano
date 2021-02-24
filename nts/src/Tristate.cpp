/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Tristate
*/

#include "Tristate.hpp"
#include <iostream>

namespace nts {

constexpr Tristate::Tristate(Value val)
    : m_value(val)
{
}

Tristate::operator Value() const
{
    return m_value;
}

Tristate Tristate::operator&&(const Tristate& other) const
{
    if (*this == Tristate::FALSE || other == Tristate::FALSE) {
        return Tristate::FALSE;
    } else if (*this == Tristate::UNDEFINED || other == Tristate::UNDEFINED) {
        return Tristate::UNDEFINED;
    } else {
        return Tristate::TRUE;
    }
}

Tristate Tristate::operator||(const Tristate& other) const
{
    if (*this == Tristate::TRUE || other == Tristate::TRUE) {
        return Tristate::TRUE;
    } else if (*this == Tristate::UNDEFINED || other == Tristate::UNDEFINED) {
        return Tristate::UNDEFINED;
    } else {
        return Tristate::FALSE;
    }
}

Tristate Tristate::operator!() const
{
    switch (*this) {
    case FALSE:
        return TRUE;
    case TRUE:
        return FALSE;
    default:
        return UNDEFINED;
    }
}

Tristate& Tristate::operator|=(const Tristate& other)
{
    return *this = *this || other;
}

Tristate& Tristate::operator&=(const Tristate& other)
{
    return *this = *this && other;
}

std::ostream& operator<<(std::ostream& os, const nts::Tristate& state)
{
    switch (state) {
    case Tristate::UNDEFINED:
        return os << 'U';
    case Tristate::TRUE:
        return os << '1';
    case Tristate::FALSE:
        return os << '0';
    }
    return os;
}

}
