/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** IOutputComponent
*/

#ifndef IOUTPUTCOMPONENT_HPP_
#define IOUTPUTCOMPONENT_HPP_

#include "IComponent.hpp"

namespace nts {

class IOutputComponent : virtual public IComponent {
public:
    virtual operator nts::Tristate() const = 0;
};

}

#endif /* !IOUTPUTCOMPONENT_HPP_ */
