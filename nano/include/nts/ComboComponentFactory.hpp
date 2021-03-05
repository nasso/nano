/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** IComponentFactory
*/

#ifndef COMBOCOMPONENTFACTORY_HPP_
#define COMBOCOMPONENTFACTORY_HPP_

#include "IComponentFactory.hpp"
#include <memory>
#include <vector>

namespace nts {

class ComboComponentFactory : public IComponentFactory {
public:
    ComboComponentFactory() noexcept = default;
    ~ComboComponentFactory() = default;

    void add(std::unique_ptr<IComponentFactory>) noexcept;

    Output createComponent(const std::string& name) noexcept override;

private:
    std::vector<std::unique_ptr<IComponentFactory>> m_factories;
};

}

#endif /* !COMBOCOMPONENTFACTORY_HPP_ */
