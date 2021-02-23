/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include "Tristate.hpp"
#include <iostream>
#include <unordered_map>

namespace nts {

enum class PinFlags {
    NONE = 0,
    INPUT = 1,
    OUTPUT = 2,
    IO = INPUT | OUTPUT,
};

using PinId = std::size_t;
using Pinout = std::unordered_map<PinId, PinFlags>;

class IPinoutBuffer {
public:
    virtual ~IPinoutBuffer() = default;

    virtual Tristate read(PinId) const = 0;
    virtual void write(PinId, Tristate) = 0;
};

class IComponent {
public:
    virtual ~IComponent() = default;

    /**
     * @brief Get pinout information
     *
     * @return PinFlags
     */
    virtual Pinout pinout() const = 0;

    /**
     * @brief Compute a step of simulation on the given pinout buffer.
     *
     * @param tick simulation tick
     */
    virtual void simulate(IPinoutBuffer&) = 0;

    /**
     * @brief Display a description of the component.
     */
    virtual void display(std::ostream&) const = 0;
};

}

std::ostream& operator<<(std::ostream& os, const nts::IComponent& comp);

#endif /* !ICOMPONENT_HPP_ */
