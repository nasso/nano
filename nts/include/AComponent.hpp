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
#include <vector>

namespace nts {

struct ComponentInput {
    IComponent& component;
    std::size_t input;
};

class AComponent : public IComponent {
public:
    virtual ~AComponent() = default;

    virtual nts::Tristate compute(std::size_t pin) override;
    virtual void setLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin) override;

    void set(std::size_t pin, Tristate value);

private:
    std::unordered_map<std::size_t, Tristate> m_inputs;
    std::unordered_map<std::size_t, std::vector<ComponentInput>> m_outputs;
};

}

#endif /* !ACOMPONENT_HPP_ */
