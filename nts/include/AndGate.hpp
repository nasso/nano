/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** AndGate
*/

#ifndef ANDGATE_HPP_
#define ANDGATE_HPP_

#include "IComponent.hpp"
#include <iostream>

namespace nts {

class AndGate : public IComponent {
public:
    Pinout pinout() const override;
    void simulate(IPinoutBuffer&) override;
    void display(std::ostream&) const override;
};

}

#endif /* !ANDGATE_HPP_ */
