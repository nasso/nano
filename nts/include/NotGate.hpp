/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NotGate
*/

#ifndef NOTGATE_HPP_
#define NOTGATE_HPP_

#include "AComponent.hpp"

namespace nts {

class NotGate : public AComponent {
public:
    NotGate();

protected:
    void _compute(PinSetter set) override;
};

}

#endif /* !NOTGATE_HPP_ */
