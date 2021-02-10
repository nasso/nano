/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include <cstddef>

namespace nts {

enum Tristate {
    UNDEFINED = (-true),
    TRUE = true,
    FALSE = false
};

class IComponent {
public:
    virtual ~IComponent() = default;

    /**
     * @brief Reset the state of the Component if tick is different than the
     * currentSimulateTick.
     *
     * @param tick simulation tick
     */
    virtual void simulate(std::size_t tick) = 0;

    /**
     * @brief Get the value for a specific output.
     *
     * @param pin The output pin for which to get the value.
     * @return nts::Tristate The current value of the pin.
     */
    virtual nts::Tristate compute(std::size_t pin) = 0;

    /**
     * @brief Link an output pin to the input of another component.
     *
     * @param pin The output pin
     * @param other The other component
     * @param otherPin The other component's input pin
     */
    virtual void setLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin)
        = 0;

    /**
     * @brief Dump stuff in some way.
     */
    virtual void dump() const = 0;
};

}

#endif /* !ICOMPONENT_HPP_ */
