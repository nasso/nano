/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** IOComponentFactory
*/

#ifndef IOCOMPONENTFACTORY_HPP_
#define IOCOMPONENTFACTORY_HPP_

#include "IComponentFactory.hpp"
#include <vector>

#include <fstream>
#include <string>

namespace nts {
class IOComponentFactory : public IComponentFactory {
public:
    IOComponentFactory(std::string loggerFilePath = "./log.bin", std::string romFilePath = "./rom.bin");
    ~IOComponentFactory();

    std::unique_ptr<nts::IComponent> createComponent(const std::string& name);

protected:
private:
    std::ofstream m_loggerFile;
    std::ifstream m_romFile;
    std::vector<char> m_romBuffer;
};
}

#endif /* !IOCOMPONENTFACTORY_HPP_ */
