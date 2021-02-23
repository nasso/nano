/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ConstComponent
*/

#ifndef CONSTCOMPONENT_HPP_
#define CONSTCOMPONENT_HPP_

#include "IComponent.hpp"

namespace nts {

class ConstComponent : public IComponent {
public:
    ConstComponent(nts::Tristate value);

    Pinout pinout() const override;
    void simulate(IPinoutBuffer&) override;
    void display(std::ostream&) const override;

private:
    const nts::Tristate m_value;
};

}

#endif /* !CONSTCOMPONENT_HPP_ */
