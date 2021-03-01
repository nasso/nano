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
#include <unordered_set>

namespace nts {

class NtsComponentFactory : public IComponentFactory {
public:
    NtsComponentFactory(std::string dirpath);
    ~NtsComponentFactory() = default;

    std::unique_ptr<IComponent> createComponent(const std::string& name)
        override;

private:
    NtsComponentFactory(const NtsComponentFactory& base,
        const std::string& except);

    std::string m_dirpath;
    std::unordered_set<std::string> m_exceptions;
};

}

#endif /* !NTSCOMPONENTFACTORY_HPP_ */
