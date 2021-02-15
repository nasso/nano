/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** IComponentFactory
*/

#ifndef BUILTINCOMPONENTFACTORY_HPP_
#define BUILTINCOMPONENTFACTORY_HPP_

#include "IComponentFactory.hpp"
#include <memory>
#include <string>
#include <vector>

namespace nts {

class BuiltInComponentFactory : public IComponentFactory {
public:
    ~BuiltInComponentFactory() = default;

    std::unique_ptr<nts::IComponent> createComponent(const std::string& name)
        override;

private:
};

}

#endif /* !BUILTINCOMPONENTFACTORY_HPP_ */
