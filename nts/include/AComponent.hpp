/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include <functional>
#include <set>
#include <unordered_map>
#include <vector>

namespace nts {

class AComponent : public IComponent {
public:
    virtual ~AComponent() = default;

    nts::Tristate compute(std::size_t pin) const override;
    void simulate(std::size_t tick) override;
    void setLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin) override;
    void unsetLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin) override;

    virtual void dump() const override;

protected:
    using PinSetter = std::function<void(std::size_t pin, nts::Tristate value)>;

    void input(std::size_t pin);
    void output(std::size_t pin);

    virtual void _compute(PinSetter set) = 0;

private:
    struct Pin {
        IComponent* comp;
        std::size_t pin;

        bool operator<(const Pin& other) const
        {
            return comp < other.comp && pin < other.pin;
        }
    };

    struct Output {
        nts::Tristate value;
        std::set<Pin> children;
    };

    std::size_t m_currentTick;
    bool m_simulating = false;
    std::unordered_map<std::size_t, Output> m_outputs;
    std::unordered_map<std::size_t, Pin> m_inputs;
};

}

#endif /* !ACOMPONENT_HPP_ */
