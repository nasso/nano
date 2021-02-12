/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** IComponentFactory
*/

#ifndef ICOMPONENTFACTORY_HPP_
#define ICOMPONENTFACTORY_HPP_

#include "IComponent.hpp"
#include <memory>

namespace nts {

class IComponentFactory {
public:
    virtual ~IComponentFactory() = default;

    /**
     * @brief Create an instance of the given component.
     *
     * @param name The name of the component to return an instance of
     * @return An new instance of the component with the given name
     */
    virtual std::unique_ptr<nts::IComponent> createComponent(const std::string& name) = 0;
};

}

#endif /* !ICOMPONENTFACTORY_HPP_ */
