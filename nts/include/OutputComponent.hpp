/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** OutputComponent
*/

#ifndef OUTPUTCOMPONENT_HPP_
#define OUTPUTCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {

class OutputComponent : public AComponent {
public:
    OutputComponent();

    operator nts::Tristate() const;

    nts::Tristate read() const;

protected:
    void _compute(PinSetter) override;

private:
    nts::Tristate m_value = UNDEFINED;
};

}

#endif /* !OUTPUTCOMPONENT_HPP_ */
