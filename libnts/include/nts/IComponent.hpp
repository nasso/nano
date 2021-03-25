/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include "Pinout.hpp"
#include "Tristate.hpp"
#include <cstdint>
#include <iostream>
#include <unordered_map>

namespace nts {

class IComponent {
public:
    virtual ~IComponent() = default;

    /**
     * @brief Simulate 1 step of internal logic.
     */
    virtual void tick() = 0;

    /**
     * @brief Checks whether or not the component is "stable".
     *
     * A component is said to be "stable" when ticking it again without changing
     * its INPUT pins wouldn't cause any change in its OUTPUT pins.
     *
     * @return true If the component is stable.
     * @return false If the component isn't stable.
     */
    virtual bool stable() const = 0;

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
