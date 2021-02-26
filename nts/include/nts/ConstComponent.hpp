/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** ConstComponent
*/

#ifndef CONSTCOMPONENT_HPP_
#define CONSTCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {

class ConstComponent : public AComponent {
public:
    ConstComponent(nts::Tristate value);

    void simulate() override;

private:
    const nts::Tristate m_value;
};

}

#endif /* !CONSTCOMPONENT_HPP_ */
