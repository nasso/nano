/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** PullComponent
*/

#ifndef PULLCOMPONENT_HPP_
#define PULLCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {

/**
 * @brief The most important component.
 */
class PullComponent : public AComponent {
public:
    enum PullDirection {
        UP,
        DOWN,
    };

    PullComponent(PullDirection direction);

protected:
    void _compute(PinSetter set) override;

private:
    PullDirection m_dir;
};

}

#endif /* !PULLCOMPONENT_HPP_ */
