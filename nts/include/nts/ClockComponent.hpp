/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ClockComponent
*/

#ifndef CLOCKCOMPONENT_HPP_
#define CLOCKCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {

class ClockComponent : public AComponent {
public:
    ClockComponent(Tristate init = Tristate::UNDEFINED);

    ClockComponent& operator=(Tristate value);

    void simulate() override;

private:
    Tristate m_value = Tristate::UNDEFINED;
};

}

#endif /* !CLOCKCOMPONENT_HPP_ */
