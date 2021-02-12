/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "AComponent.hpp"
#include "InputComponent.hpp"
#include "NodeComponent.hpp"
#include "OutputComponent.hpp"

namespace nts {

class Circuit : public AComponent {
protected:
    InputComponent& input(std::size_t pin);
    OutputComponent& output(std::size_t pin);

    void _compute(PinSetter set) override;

private:
    std::size_t m_internTick = 0;
    std::unordered_map<std::size_t, InputComponent> m_inputs;
    std::unordered_map<std::size_t, OutputComponent> m_outputs;
};

}

#endif /* !CIRCUIT_HPP_ */
