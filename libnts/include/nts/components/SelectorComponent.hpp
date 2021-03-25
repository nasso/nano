/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** SelectorComponent
*/

#ifndef SELECTORCOMPONENT_HPP_
#define SELECTORCOMPONENT_HPP_

#include "../AComponent.hpp"
#include <memory>
#include <vector>

namespace nts {

class SelectorComponent : public AComponent {
public:
    SelectorComponent();

    void tick() override;
    virtual void display(std::ostream& os) const override;
};

}

#endif /* !SELECTORCOMPONENT_HPP_ */
