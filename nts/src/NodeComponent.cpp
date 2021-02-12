/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** NodeComponent
*/

#include "NodeComponent.hpp"
#include "AComponent.hpp"

namespace nts {

NodeComponent::NodeComponent()
{
    input(1);
    output(2);
}

void NodeComponent::_compute(PinSetter set)
{
    set(2, compute(1));
}

}
