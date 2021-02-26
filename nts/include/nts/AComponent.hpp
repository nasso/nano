/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"

namespace nts {

class AComponent : public IComponent {
public:
    AComponent();
    AComponent(Pinout pinout);

    void pinMode(PinId pin, PinMode flags);

    const Pinout& pinout() const override final;
    Tristate read(PinId pin) const override final;
    void write(PinId pin, Tristate value) override final;

    virtual void display(std::ostream& os) const override;

private:
    Pinout m_pinout;
    std::unordered_map<PinId, Tristate> m_pins;
};

}

#endif /* !ACOMPONENT_HPP_ */
