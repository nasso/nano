/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** IComponentFactory
*/

#ifndef ICOMPONENTFACTORY_HPP_
#define ICOMPONENTFACTORY_HPP_

#include "IComponent.hpp"

namespace nts {

class IComponentFactory {
public:
    virtual ~IComponentFactory() = default;

    std::unique_ptr<nts::IComponent> createComponent(const std::string& name);
};

}

#endif /* !ICOMPONENTFACTORY_HPP_ */
