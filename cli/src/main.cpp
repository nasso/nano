/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** main
*/

#include "Repl.hpp"
#include "nts/BuiltInComponentFactory.hpp"
#include "nts/LoggerComponent.hpp"
#include "nts/MultiComponentFactory.hpp"
#include "nts/NtsCircuit.hpp"
#include "nts/NtsComponentFactory.hpp"
#include "nts/RomComponent.hpp"
#include "nts/StaticComponentFactory.hpp"
#include <fstream>
#include <iostream>
#include <memory>

static void usage(const std::string& name)
{
    std::cout << "usage: " << name << " <nts_file>" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2 || argv[1] == std::string("-h")) {
        usage(argv[0]);
        return (argc == 2 && argv[1] == std::string("-h") ? 0 : 84);
    }

    try {
        std::ofstream logfile;
        std::ifstream file(argv[1]);

        auto builtins = std::make_unique<nts::BuiltInComponentFactory>();
        auto chips = std::make_unique<nts::NtsComponentFactory>("components");
        auto extras = std::make_unique<nts::StaticComponentFactory>();

        extras->add("logger", [&]() {
            if (!logfile.is_open()) {
                logfile.open("log.bin");

                if (!logfile.is_open()) {
                    throw std::runtime_error("Can't open log file");
                }
            }

            return std::make_unique<nts::LoggerComponent>(logfile);
        });

        extras->add("2716", []() {
            std::ifstream romfile("rom.bin", std::ios::binary | std::ios::in);

            if (!romfile.is_open()) {
                throw std::runtime_error("Couldn't read \"rom.bin\"");
            }

            std::vector<std::uint8_t> rom(2048);
            romfile.read(reinterpret_cast<char*>(rom.data()), rom.size());

            return std::make_unique<nts::RomComponent>(rom);
        });

        nts::MultiComponentFactory mainFactory;
        mainFactory.addFactory(std::move(builtins));
        mainFactory.addFactory(std::move(extras));
        mainFactory.addFactory(std::move(chips));

        nts::NtsCircuit circuit(file, mainFactory);

        Repl repl(std::move(circuit));

        repl.run(std::cin, std::cout);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return (84);
    }

    return (0);
}
