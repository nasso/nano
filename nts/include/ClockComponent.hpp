/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ClockComponent
*/

#ifndef CLOCKCOMPONENT_HPP_
#define CLOCKCOMPONENT_HPP_

#include "AComponent.hpp"
#include "IInputComponent.hpp"

namespace nts {

class ClockComponent : public AComponent, public IInputComponent {
public:
    ClockComponent(Tristate init = Tristate::UNDEFINED);

    virtual ClockComponent& operator=(Tristate value) override;

protected:
    void _compute(PinSetter) override;

private:
    Tristate m_value = Tristate::UNDEFINED;
};

}

#endif /* !CLOCKCOMPONENT_HPP_ */
