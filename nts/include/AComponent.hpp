/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include "Pin.hpp"
#include "Subscription.hpp"
#include <unordered_map>
#include <vector>

namespace nts {

struct ComponentInput {
    IComponent& component;
    std::size_t input;
};

class AComponent : public IComponent {
public:
    virtual ~AComponent() = default;

    void simulate(size_t tick);

    nts::Tristate compute(size_t pin);

    void setLink(size_t pin, nts::IComponent& other,
        size_t otherPin) override;

    void dump() const override;

protected:
    virtual void _simulate() = 0;
    void _init();
    Pin& getPin(size_t pin);

    std::vector<Pin> m_pins;
    std::vector<size_t> m_inputPins;
    std::unordered_map<size_t, std::shared_ptr<rtk::Subscription>> m_links;

private:
    size_t m_currentTick;
};

}

#endif /* !ACOMPONENT_HPP_ */
