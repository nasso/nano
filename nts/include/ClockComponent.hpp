/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ClockComponent
*/

#ifndef CLOCKCOMPONENT_HPP_
#define CLOCKCOMPONENT_HPP_

#include "IComponent.hpp"
#include "IInputComponent.hpp"

namespace nts {

class ClockComponent : public IComponent {
public:
    ClockComponent(Tristate init = Tristate::UNDEFINED);

    ClockComponent& operator=(Tristate value);

    Pinout pinout() const override;
    void simulate(IPinoutBuffer&) override;
    void display(std::ostream&) const override;

private:
    Tristate m_value = Tristate::UNDEFINED;
};

}

#endif /* !CLOCKCOMPONENT_HPP_ */
