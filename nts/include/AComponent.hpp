/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include <unordered_map>

namespace nts {

class AComponent : public IComponent {
public:
    virtual ~AComponent() = default;

    nts::Tristate compute(std::size_t pin) const override;
    void simulate(std::size_t tick) override;
    void setLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin) override;

    virtual void dump() const override;

protected:
    void input(std::size_t pin);
    void output(std::size_t pin);
    void set(std::size_t output, nts::Tristate value);

    virtual void _compute(std::size_t tick) = 0;

private:
    struct ComponentInput {
        IComponent& component;
        std::size_t output;
    };

    std::size_t m_currentTick;
    bool m_simulating = false;
    std::unordered_map<std::size_t, ComponentInput> m_inputs;
    std::unordered_map<std::size_t, nts::Tristate> m_outputs;
};

}

#endif /* !ACOMPONENT_HPP_ */
