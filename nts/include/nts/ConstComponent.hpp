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

    void simulate() override;
    const Pinout& pinout() const override;
    Tristate read(PinId pin) const override;
    void write(PinId pin, Tristate value) override;
    void display(std::ostream& os) const override;

private:
    const nts::Tristate m_value;
};

}

#endif /* !CONSTCOMPONENT_HPP_ */
