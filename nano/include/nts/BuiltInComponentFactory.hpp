/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** IComponentFactory
*/

#ifndef BUILTINCOMPONENTFACTORY_HPP_
#define BUILTINCOMPONENTFACTORY_HPP_

#include "IComponentFactory.hpp"
#include "StaticComponentFactory.hpp"

namespace nts {

class BuiltInComponentFactory : public IComponentFactory {
public:
    BuiltInComponentFactory();

    virtual Output createComponent(const Name& name) override;

private:
    StaticComponentFactory m_scf;
};

}

#endif /* !BUILTINCOMPONENTFACTORY_HPP_ */
