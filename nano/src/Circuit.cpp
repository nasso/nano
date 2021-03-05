/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Circuit
*/

#include "nts/Circuit.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(nts_circuit_str)
{
    using Circuit = nts::Circuit<std::string>;

    emscripten::class_<Circuit, emscripten::base<nts::AComponent>>("Circuit")
        .constructor<>()
        .property("stable", &Circuit::stable)
        .function("tick", &Circuit::tick);
}
#endif
