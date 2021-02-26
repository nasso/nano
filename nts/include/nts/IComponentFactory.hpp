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
#include <string>

namespace nts {

class IComponentFactory {
public:
    using Output = std::unique_ptr<IComponent>;
    using Name = std::string;

    virtual ~IComponentFactory() = default;

    /**
     * @brief Create an instance of the given component.
     *
     * @param name The name of the component to return an instance of
     * @return An new instance of the component with the given name
     */
    virtual Output createComponent(const Name& name) = 0;
};

}

#endif /* !ICOMPONENTFACTORY_HPP_ */
