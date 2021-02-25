/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NotGate
*/

#ifndef NOTGATE_HPP_
#define NOTGATE_HPP_

#include "AComponent.hpp"
#include <iostream>

namespace nts {

class NotGate : public AComponent {
public:
    NotGate();

    void simulate() override;
};

}

#endif /* !NOTGATE_HPP_ */
