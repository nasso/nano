/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {

/**
 * @brief A component with a single configurable output.
 */
class InputComponent : public AComponent {
public:
    InputComponent(nts::Tristate value = UNDEFINED);

    InputComponent& operator=(nts::Tristate value);

protected:
    void _compute(PinSetter tick) override;

private:
    nts::Tristate m_value = UNDEFINED;
};

}

#endif /* !INPUTCOMPONENT_HPP_ */
