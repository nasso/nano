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
    using Generator = std::function<Output()>;

    StaticComponentFactory();

    virtual Output createComponent(const Name& name) override;

    void add(const Name& name, Generator gen);

private:
    std::unordered_map<Name, Generator> m_generators;
};

}

#endif /* !STATICCOMPONENTFACTORY_HPP_ */
