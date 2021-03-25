/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** StaticComponentFactory
*/

#ifndef STATICCOMPONENTFACTORY_HPP_
#define STATICCOMPONENTFACTORY_HPP_

#include "IComponentFactory.hpp"
#include <functional>
#include <unordered_map>

namespace nts {

class StaticComponentFactory : public IComponentFactory {
public:
    using Generator = std::function<std::unique_ptr<nts::IComponent>()>;

    StaticComponentFactory();

    Output createComponent(const std::string& name) noexcept override;

    void add(const std::string& name, Generator gen);

private:
    std::unordered_map<std::string, Generator> m_generators;
};

}

#endif /* !STATICCOMPONENTFACTORY_HPP_ */
