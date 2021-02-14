/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IComponent
*/

#include "IComponent.hpp"

std::ostream& operator<<(std::ostream& os, const nts::IComponent& comp)
{
    comp.dump(os);
    return os;
}
