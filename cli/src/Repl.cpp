/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** Repl
*/

#include "Repl.hpp"
#include "nts/NtsCircuit.hpp"
#include <csignal>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

thread_local bool gSigintReceived = false;

Repl::Repl(const std::string& path,
    const std::vector<std::string>& includePaths)
    : m_circuit(path, includePaths)
{
    readPins(m_inputs, nts::INPUT);
    readPins(m_outputs, nts::OUTPUT);
}

void Repl::run(std::istream& in, std::ostream& out)
{
    m_shouldQuit = false;

    std::string input;
    while (!m_shouldQuit) {
        out << "> ";

        if (!std::getline(in, input)) {
            break;
        }

        eval(input, out);
    }
}

void Repl::eval(const std::string& cmd, std::ostream& out)
{
    const std::regex assignment_r("^\\s*(\\w+)\\s*=\\s*(U|1|0)\\s*$");
    std::smatch m;

    if (cmd == "exit") {
        m_shouldQuit = true;
    } else if (cmd == "display") {
        display(out);
    } else if (cmd == "simulate") {
        simulate(out);
    } else if (cmd == "loop") {
        gSigintReceived = false;
        std::signal(SIGINT, [](int) {
            gSigintReceived = true;
        });

        while (!gSigintReceived) {
            simulate(out);
            display(out);
        }

        signal(SIGINT, nullptr);
    } else if (cmd == "dump") {
        out << m_circuit << std::endl;
    } else if (std::regex_match(cmd, m, assignment_r)) {
        try {
            nts::PinId pin(m_circuit.input(m[1]));
            nts::Tristate value;

            if (m[2] == "U") {
                value = nts::Tristate::UNDEFINED;
            } else if (m[2] == "0") {
                value = nts::Tristate::FALSE;
            } else if (m[2] == "1") {
                value = nts::Tristate::TRUE;
            }

            m_circuit.write(pin, value);
        } catch (...) {
            out << "Can't find a pin named \"" << m[1] << "\"" << std::endl;
        }
    } else {
        out << "Unknown command: " + cmd << std::endl;
    }
}

void Repl::simulate(std::ostream& out)
{
    m_inputs.clear();
    m_outputs.clear();

    readPins(m_inputs, nts::INPUT);

    try {
        m_circuit.simulate();
    } catch (const std::exception& e) {
        out << e.what() << std::endl;
    }

    readPins(m_outputs, nts::OUTPUT);
    m_tick++;
}

void Repl::readPins(Repl::TristateMap& dest, nts::PinMode filter)
{
    nts::Pinout pinout(m_circuit.pinout());
    const auto& pinNames = m_circuit.pins();

    for (const auto& pair : pinNames) {
        const std::string& name = pair.first;
        nts::PinId pin = pair.second;
        nts::PinMode mode = pinout.at(pin);

        if (mode & filter) {
            dest[name] = m_circuit.read(pin);
        }
    }
}

void Repl::display(std::ostream& out)
{
    out << "tick: " << m_tick << std::endl;

    out << "input(s):" << std::endl;
    for (const auto& pair : m_inputs) {
        const std::string& name = pair.first;
        nts::Tristate value = pair.second;

        out << "\t" << name << ": " << value << "\n";
    }

    out << "output(s):" << std::endl;
    for (const auto& pair : m_outputs) {
        const std::string& name = pair.first;
        nts::Tristate value = pair.second;

        out << "\t" << name << ": " << value << "\n";
    }

    out << std::flush;
}
