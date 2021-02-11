/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Chip
*/

#include "Chip.hpp"
#include <memory>

namespace nts {

Chip::Chip()
{
}

void Chip::add(std::unique_ptr<IComponent> component)
{
    m_children.insert(std::move(component));
}

void Chip::_compute(std::size_t)
{
}

}
