/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** AndGate
*/

#ifndef ANDGATE_HPP_
#define ANDGATE_HPP_

#include "AComponent.hpp"

namespace nts {

class AndGate : public AComponent {
public:
    AndGate();

protected:
    void _compute(PinSetter set) override;
};

}

#endif /* !ANDGATE_HPP_ */
