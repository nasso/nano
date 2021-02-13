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

class Pin;

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
     * @brief Get the value of a pin.
     *
     * @param pin The output pin for which to get the value.
     * @return nts::Tristate The current value of the pin.
     */
    virtual nts::Tristate compute(std::size_t pin) = 0;

    /**
     * @brief Link a pin of this component to the pin of another component.
     *
     * The internal graph is bi-directional. This method can be called in either
     * direction, but it will automatically call itself on the other component
     * if the link didn't already exist.
     *
     * @param pin The pin of this component to be linked
     * @param other The other component
     * @param otherPin The other component's pin to link to
     */
    virtual void setLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin)
        = 0;

    /**
     * @brief Remove a link between a pin of this component and another.
     *
     * @param pin The pin of this component to disconnect
     * @param other The other component
     * @param otherPin The other component's pin to disconnect from
     */
    virtual void unsetLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin)
        = 0;

    /**
     * @brief Dump stuff in some way.
     */
    virtual void dump() const = 0;
};

}

#endif /* !ICOMPONENT_HPP_ */
