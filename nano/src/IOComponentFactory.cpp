/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** IOComponentFactory
*/

#include "IOComponentFactory.hpp"
#include "LoggerComponent.hpp"
#include "RomComponent.hpp"
#include <sstream>

namespace nts {
IOComponentFactory::IOComponentFactory(std::string loggerFilePath, std::string romFilePath)
    : m_loggerFile(loggerFilePath)
    , m_romFile(romFilePath)
{
}

IOComponentFactory::~IOComponentFactory()
{
    if (m_loggerFile.is_open())
        m_loggerFile.close();
    if (m_romFile.is_open())
        m_romFile.close();
}

std::unique_ptr<nts::IComponent> IOComponentFactory::createComponent(const std::string& name)
{
    std::cout << m_romFile.is_open() << std::endl;
    if (name == "logger" && m_loggerFile.is_open()) {
        return std::unique_ptr<IComponent>(new LoggerComponent(m_loggerFile));
    } else if (name == "2716" && m_romFile.is_open()) {
        if (m_romBuffer.empty()) {
            std::ostringstream ss;
            ss << m_romFile.rdbuf();
            m_romBuffer = std::vector<char>(ss.str().begin(), ss.str().end());
        }
        return std::unique_ptr<nts::IComponent>(new RomComponent(m_romBuffer));
    }
    throw std::runtime_error("Error can't create component " + name);
}
}