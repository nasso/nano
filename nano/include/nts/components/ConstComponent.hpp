/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ConstComponent
*/

#ifndef CONSTCOMPONENT_HPP_
#define CONSTCOMPONENT_HPP_

#include "../IComponent.hpp"

namespace nts {

class ConstComponent : public IComponent {
public:
    ConstComponent(nts::Tristate value);

    virtual void tick() override;
    virtual bool stable() const override;
    virtual const Pinout& pinout() const override;
    virtual Tristate read(PinId pin) const override;
    virtual void write(PinId pin, Tristate value) override;
    virtual void display(std::ostream& os) const override;

private:
    const nts::Tristate m_value;
};

}

#endif /* !CONSTCOMPONENT_HPP_ */
