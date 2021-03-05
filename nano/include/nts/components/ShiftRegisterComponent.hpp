/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** ShiftRegisterComponent
*/

#ifndef SHIFTREGISTERCOMPONENT_HPP_
#define SHIFTREGISTERCOMPONENT_HPP_

#include "../AComponent.hpp"
#include <memory>
#include <vector>

namespace nts {

class ShiftRegisterComponent : public AComponent {
public:
    ShiftRegisterComponent();

    void tick() override;
    virtual void display(std::ostream& os) const override;
};

}

#endif /* !SHIFTREGISTERCOMPONENT_HPP_ */
