/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Tristate
*/

#include "nts/Tristate.hpp"
#include <iostream>

namespace nts {

const Tristate Tristate::UNDEFINED = Tristate(Tristate::Value::UNDEFINED);
const Tristate Tristate::FALSE = Tristate(Tristate::Value::FALSE);
const Tristate Tristate::TRUE = Tristate(Tristate::Value::TRUE);

bool Tristate::operator==(const Tristate& other) const
{
    return m_value == other.m_value;
}

bool Tristate::operator!=(const Tristate& other) const
{
    return m_value != other.m_value;
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
    switch (m_value) {
    case Value::FALSE:
        return TRUE;
    case Value::TRUE:
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
    if (state == Tristate::FALSE) {
        return os << '0';
    } else if (state == Tristate::TRUE) {
        return os << '1';
    } else {
        return os << 'U';
    }
}

}
