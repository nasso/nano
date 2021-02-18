/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IInputComponent
*/

#ifndef IINPUTCOMPONENT_HPP_
#define IINPUTCOMPONENT_HPP_

#include "IPinComponent.hpp"

namespace nts {

/**
 * @brief A component that can be manually set to a specific value.
 */
class IInputComponent : public IPinComponent {
public:
    virtual IInputComponent& operator=(nts::Tristate value) = 0;

    Kind kind() const final override
    {
        return Kind::INPUT;
    }
};

}

#endif /* !IINPUTCOMPONENT_HPP_ */
