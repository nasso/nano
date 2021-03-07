/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** CounterComponent
*/

#ifndef COUNTERCOMPONENT_HPP_
#define COUNTERCOMPONENT_HPP_

#include "../AComponent.hpp"
#include <memory>
#include <vector>

namespace nts {

class CounterComponent : public AComponent {
public:
    CounterComponent();

    void tick() override;
    virtual void display(std::ostream& os) const override;
private:
    size_t m_value;
};

}

#endif /* !COUNTERCOMPONENT_HPP_ */
