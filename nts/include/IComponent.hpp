/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include "Tristate.hpp"
#include <cstdint>
#include <iostream>
#include <unordered_map>

namespace nts {

enum PinMode : std::uint8_t {
    NONE = 0,
    INPUT = 1 << 1,
    OUTPUT = 1 << 2,
};

inline PinMode operator|(PinMode a, PinMode b)
{
    return static_cast<PinMode>(static_cast<int>(a) | static_cast<int>(b));
}

using PinId = std::size_t;
using Pinout = std::unordered_map<PinId, PinMode>;

class IComponent {
public:
    virtual ~IComponent() = default;

    /**
     * @brief Compute a step of simulation.
     */
    virtual void simulate() = 0;

    /**
     * @brief Get pinout information
     *
     * @return Pinout
     */
    virtual const Pinout& pinout() const = 0;

    /**
     * @brief Read the value of a pin.
     *
     * @param pin The pin to read
     * @return Tristate
     */
    virtual Tristate read(PinId pin) const = 0;

    /**
     * @brief Write a value to a pin.
     *
     * @param pin The pin to write to
     * @param value The value to write
     */
    virtual void write(PinId pin, Tristate value) = 0;

    /**
     * @brief Display a description of the component.
     *
     * @param os The output stream
     */
    virtual void display(std::ostream& os) const = 0;
};

}

std::ostream& operator<<(std::ostream& os, const nts::IComponent& comp);

#endif /* !ICOMPONENT_HPP_ */
