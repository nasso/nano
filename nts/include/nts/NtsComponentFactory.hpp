/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** IComponentFactory
*/

#ifndef NTSCOMPONENTFACTORY_HPP_
#define NTSCOMPONENTFACTORY_HPP_

#include "IComponentFactory.hpp"
#include <memory>
#include <string>
#include <vector>

namespace nts {

class NtsComponentFactory : public IComponentFactory {
public:
    NtsComponentFactory(std::string dirpath);
    ~NtsComponentFactory() = default;

    std::unique_ptr<nts::IComponent> createComponent(const std::string& name)
        override;

private:
    std::string m_dirpath;
};

}

#endif /* !NTSCOMPONENTFACTORY_HPP_ */
