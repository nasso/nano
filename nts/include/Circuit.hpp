/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "AComponent.hpp"
#include "IInputComponent.hpp"
#include "IOutputComponent.hpp"
#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include <memory>

namespace nts {

class Circuit : public AComponent {
protected:
    template <typename Comp = InputComponent>
    Comp& input(std::size_t pin)
    {
        AComponent::input(pin);

        m_outputs.erase(pin);
        m_inputs.erase(pin);

        auto comp = new Comp;
        m_inputs.emplace(pin, comp);

        return *comp;
    }

    template <typename Comp = OutputComponent>
    Comp& output(std::size_t pin)
    {
        AComponent::output(pin);

        m_inputs.erase(pin);
        m_outputs.erase(pin);

        auto comp = new Comp;
        m_outputs.emplace(pin, comp);

        return *comp;
    }

    void _compute(PinSetter set) override;

private:
    std::size_t m_internTick = 0;
    std::unordered_map<std::size_t, std::unique_ptr<IInputComponent>> m_inputs;
    std::unordered_map<std::size_t, std::unique_ptr<IOutputComponent>>
        m_outputs;
};

}

#endif /* !CIRCUIT_HPP_ */
