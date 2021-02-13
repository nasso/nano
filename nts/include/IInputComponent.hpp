/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IInputComponent
*/

#ifndef IINPUTCOMPONENT_HPP_
#define IINPUTCOMPONENT_HPP_

#include "IComponent.hpp"

namespace nts {

/**
 * @brief A component that can be manually set to a specific value.
 */
class IInputComponent : virtual public IComponent {
public:
    virtual IInputComponent& operator=(nts::Tristate value) = 0;
};

}

#endif /* !IINPUTCOMPONENT_HPP_ */
