/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** IComponentFactory
*/

#ifndef MULTICOMPONENTFACTORY_HPP_
#define MULTICOMPONENTFACTORY_HPP_

#include "IComponentFactory.hpp"
#include <memory>
#include <vector>

namespace nts {

class MultiComponentFactory : public IComponentFactory {
public:
    MultiComponentFactory(std::vector<std::unique_ptr<IComponentFactory>>);
    ~MultiComponentFactory() = default;

    std::unique_ptr<nts::IComponent> createComponent(const std::string& name)
        override;

private:
    std::vector<std::unique_ptr<IComponentFactory>> m_factories;
};

}

#endif /* !MULTICOMPONENTFACTORY_HPP_ */
