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

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(nts_pinout)
{
    emscripten::register_vector<nts::PinId>("vector<nts::PinId>");
    emscripten::register_map<nts::PinId, nts::PinMode>("Pinout");

    emscripten::enum_<nts::PinMode>("PinMode")
        .value("NONE", nts::PinMode::NONE)
        .value("INPUT", nts::PinMode::INPUT)
        .value("OUTPUT", nts::PinMode::OUTPUT)
        .value("INPUT_OUTPUT", nts::PinMode::INPUT | nts::PinMode::OUTPUT);
}
#endif
