/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Circuit
*/

#include "nts/Circuit.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

using Circuit = nts::Circuit<std::string>;
using namespace emscripten;

nts::IComponent* Circuit_get(Circuit& self, const std::string& name)
{
    return self
        .get(name)
        .map([](auto& comp) { return &comp; })
        .unwrap_or(nullptr);
}

EMSCRIPTEN_BINDINGS(nts_circuit_str)
{
    class_<Circuit, base<nts::AComponent>>("Circuit")
        .constructor<>()
        .property("stable", &Circuit::stable)
        .function("tick", &Circuit::tick)
        .function("insert", &Circuit::insert)
        .function("remove", &Circuit::remove)
        .function("get", &Circuit_get, allow_raw_pointers())
        .function("connect",
            select_overload<void(nts::PinId, nts::PinId)>(&Circuit::connect))
        .function("connect",
            select_overload<void(nts::PinId, const std::string&, nts::PinId)>(
                &Circuit::connect))
        .function("connect",
            select_overload<void(const std::string&, nts::PinId,
                const std::string&, nts::PinId)>(&Circuit::connect))
        .function("disconnect",
            select_overload<void(nts::PinId, nts::PinId)>(&Circuit::disconnect))
        .function("disconnect",
            select_overload<void(nts::PinId, const std::string&, nts::PinId)>(
                &Circuit::disconnect))
        .function("disconnect",
            select_overload<void(const std::string&, nts::PinId,
                const std::string&, nts::PinId)>(&Circuit::disconnect));
}
#endif
