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
    NtsComponentFactory(std::string dirpath) noexcept;
    ~NtsComponentFactory() = default;

    Output createComponent(const std::string& name) noexcept override;

private:
    NtsComponentFactory(const NtsComponentFactory& base,
        const std::string& except) noexcept;

    std::string m_dirpath;
    std::unordered_set<std::string> m_exceptions;
};

}

#endif /* !NTSCOMPONENTFACTORY_HPP_ */
