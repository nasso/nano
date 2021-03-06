/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** IComponentFactory
*/

#ifndef ICOMPONENTFACTORY_HPP_
#define ICOMPONENTFACTORY_HPP_

#include "IComponent.hpp"
#include "mtl/Option.hpp"
#include <memory>
#include <string>

namespace nts {

class IComponentFactory {
public:
    using Output = mtl::Option<std::unique_ptr<IComponent>>;

    virtual ~IComponentFactory() = default;

    /**
     * @brief Create an instance of the given component.
     *
     * @param name The name of the component to return an instance of
     * @return An new instance of the component with the given name
     */
    virtual Output createComponent(const std::string& name) noexcept = 0;
};

}

#endif /* !ICOMPONENTFACTORY_HPP_ */
