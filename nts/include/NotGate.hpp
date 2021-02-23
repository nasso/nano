/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NotGate
*/

#ifndef NOTGATE_HPP_
#define NOTGATE_HPP_

#include "IComponent.hpp"
#include <iostream>

namespace nts {

class NotGate : public IComponent {
public:
    Pinout pinout() const override;
    void simulate(IPinoutBuffer&) override;
    void display(std::ostream&) const override;
};

}

#endif /* !NOTGATE_HPP_ */
