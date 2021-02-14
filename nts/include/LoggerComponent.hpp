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
    LoggerComponent(std::ostream& output_s);
    ~LoggerComponent() = default;

protected:
    void _compute(PinSetter set) override;

private:
    std::ostream& m_output;
};
}

#endif /* !LOGGERCOMPONENT_HPP_ */
