/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Pinout
*/

#include "nts/Pinout.hpp"

nts::PinMode operator&(nts::PinMode a, nts::PinMode b)
{
    return static_cast<nts::PinMode>(static_cast<int>(a) & static_cast<int>(b));
}

nts::PinMode operator|(nts::PinMode a, nts::PinMode b)
{
    return static_cast<nts::PinMode>(static_cast<int>(a) | static_cast<int>(b));
}

nts::PinMode operator^(nts::PinMode a, nts::PinMode b)
{
    return static_cast<nts::PinMode>(static_cast<int>(a) ^ static_cast<int>(b));
}

nts::PinMode operator~(nts::PinMode a)
{
    return static_cast<nts::PinMode>(~static_cast<int>(a));
}

bool operator!(nts::PinMode a)
{
    return !static_cast<int>(a);
}

bool operator!=(nts::PinMode a, nts::PinMode b)
{
    return !(a & b);
}

bool operator==(nts::PinMode a, nts::PinMode b)
{
    return !(a != b);
}
