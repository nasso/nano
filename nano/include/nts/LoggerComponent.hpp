/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** LoggerComponent
*/

#ifndef LOGGERCOMPONENT_HPP_
#define LOGGERCOMPONENT_HPP_

#include "AComponent.hpp"
#include <memory>
#include <vector>

namespace nts {

class LoggerComponent : public AComponent {
public:
    LoggerComponent(std::ostream& out);

    virtual void simulate() override;
    virtual void display(std::ostream& os) const override;

private:
    bool m_rising = false;
    std::ostream& m_output;
};

}

#endif /* !LOGGERCOMPONENT_HPP_ */
