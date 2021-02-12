/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include <functional>
#include <set>
#include <unordered_map>
#include <vector>

namespace nts {

class AComponent : public IComponent {
public:
    virtual ~AComponent();

    nts::Tristate compute(std::size_t pin) const override;
    void simulate(std::size_t tick) override;
    void setLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin) override;
    void unsetLink(std::size_t pin, nts::IComponent& other,
        std::size_t otherPin) override;
    virtual void dump() const override;

protected:
    using PinSetter = std::function<void(std::size_t pin, nts::Tristate value)>;

    /**
     * @brief Declares a pin as an input.
     *
     * @param pin
     */
    void input(std::size_t pin);

    /**
     * @brief Declares a pin as an output.
     *
     * @param pin
     */
    void output(std::size_t pin);

    /**
     * @brief Removes a pin.
     *
     * @param pin
     */
    void remove(std::size_t pin);

    /**
     * @brief Computes the values for all outputs.
     *
     * This method is called automatically by the AComponent class and shouldn't
     * be manually called. The provided callback is only valid for the length of
     * the call and should NOT be stored/reused elsewhere.
     *
     * @param set The function to be used to set each output pin's value.
     */
    virtual void _compute(PinSetter set) = 0;

private:
    struct Link {
        IComponent* comp = nullptr;
        std::size_t pin = 0;

        bool operator<(const Link& other) const;
    };

    struct Output {
        nts::Tristate value = UNDEFINED;
        std::set<Link> links;
        std::set<Link> newlinks;
    };

    std::size_t m_currentTick = 0;
    bool m_simulating = false;
    std::unordered_map<std::size_t, Output> m_outputs;
    std::unordered_map<std::size_t, Link> m_inputs;
};

}

#endif /* !ACOMPONENT_HPP_ */
