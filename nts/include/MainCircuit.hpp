/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui
** File description:
** MainCircuit
*/

#ifndef MAINCIRCUIT_HPP_
#define MAINCIRCUIT_HPP_

#include "NTSCircuit.hpp"

namespace nts {
class MainCircuit : public NTSCircuit {
public:
    MainCircuit(const std::string& filename,
        std::vector<std::unique_ptr<IComponentFactory>>& factories);
    ~MainCircuit();

    MainCircuit& operator=(const MainCircuit&);

    void setInputPin(const std::string& name, Tristate state);
    void display() const;
    void simulate();

protected:
private:
    size_t m_tick;
};
}

#endif /* !MAINCIRCUIT_HPP_ */
