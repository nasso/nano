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

    virtual void setLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin) override;

private:
    std::vector<Pin> m_pins;
    std::unordered_map<std::size_t, rtk::Subscription> m_links;
};

}

#endif /* !ACOMPONENT_HPP_ */
