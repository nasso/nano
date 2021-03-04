/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "AComponent.hpp"
#include "IComponent.hpp"
#include "mtl/Option.hpp"
#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace nts {
namespace {

    template <typename K>
    using ChipMap = std::unordered_map<K, std::unique_ptr<IComponent>>;

    template <typename K>
    struct ChipPin {
        mtl::Option<K> owner;
        PinId pin;

        ChipPin(K name, PinId pin)
            : owner(std::move(name))
            , pin(pin)
        {
        }

        ChipPin(PinId pin)
            : owner()
            , pin(pin)
        {
        }

        bool operator==(const ChipPin& other) const
        {
            return owner == other.owner && pin == other.pin;
        }

        Tristate read(const IComponent& circuit, const ChipMap<K>& chips) const
        {
            return owner.as_ref()
                .map([&](auto& name) -> const auto& { return *chips.at(name); })
                .unwrap_or(circuit)
                .read(pin);
        }

        void write(IComponent& circuit, ChipMap<K>& chips, Tristate value) const
        {
            return owner.as_ref()
                .map([&](auto& name) -> auto& { return *chips.at(name); })
                .unwrap_or(circuit)
                .write(pin, value);
        }

        PinMode mode(const IComponent& circuit, const ChipMap<K>& chips) const
        {
            return owner.as_ref()
                .map([&](auto& name) -> const auto& { return *chips.at(name); })
                .unwrap_or(circuit)
                .pinout()
                .at(pin);
        }
    };

    template <typename Set, typename Node, typename AdjencyList>
    Set findConnected(Node node, const AdjencyList& adjencyList)
    {
        Set connected;
        Set pool = { node };

        while (!pool.empty()) {
            const Node& node = *pool.begin();

            try {
                const Set& links = adjencyList.at(node);

                auto mbConnectedPin = std::find_if(links.begin(), links.end(),
                    [&](auto& node) {
                        return connected.find(node) == connected.end()
                            && pool.find(node) == pool.end();
                    });

                if (mbConnectedPin != links.end()) {
                    pool.insert(*mbConnectedPin);
                } else {
                    connected.insert(node);
                    pool.erase(node);
                }
            } catch (std::out_of_range&) {
                connected.insert(node);
                pool.erase(node);
            }
        }

        return connected;
    }

    Tristate propagate(Tristate a, Tristate b)
    {
        if ((a || b) == Tristate::TRUE) {
            return Tristate::TRUE;
        } else if ((a && b) == Tristate::FALSE) {
            return Tristate::FALSE;
        }

        return Tristate::UNDEFINED;
    }
}
}

namespace std {

template <typename K>
struct hash<nts::ChipPin<K>> {
    using argument_type = nts::ChipPin<K>;
    using result_type = std::size_t;

    result_type operator()(const argument_type& pin) const
    {
        result_type hash = 17;
        hash = hash * 31 + std::hash<mtl::Option<K>>()(pin.owner);
        hash = hash * 31 + std::hash<nts::PinId>()(pin.pin);
        return hash;
    }
};

}

namespace nts {

template <typename K>
class Circuit : public AComponent {
public:
    Circuit()
    {
    }

    Circuit(Circuit&& other)
        : AComponent(std::move(other))
        , m_chipsets(std::move(other.m_chipsets))
        , m_pinLinks(std::move(other.m_pinLinks))
    {
    }

    // Components
    void insert(const K& name, std::unique_ptr<IComponent> component)
    {
        m_chipsets.emplace(name, std::move(component));
    }

    std::unique_ptr<IComponent> remove(const K& name)
    {
        std::unique_ptr<IComponent> chip(std::move(m_chipsets.at(name)));

        m_chipsets.erase(name);

        return std::move(chip);
    }

    IComponent& operator[](const K& name)
    {
        return *m_chipsets.at(name);
    }

    const IComponent& operator[](const K& name) const
    {
        return *m_chipsets.at(name);
    }

    // Links
    void connect(const K& chip1, PinId pin1, const K& chip2, PinId pin2)
    {
        connectPins({ chip1, pin1 }, { chip2, pin2 });
    }

    void connect(PinId pin, const K& compName, PinId compPin)
    {
        connectPins({ pin }, { compName, compPin });
    }

    void connect(PinId pin1, PinId pin2)
    {
        connectPins({ pin1 }, { pin2 });
    }

    void disconnect(const K& chip1, PinId pin1, const K& chip2, PinId pin2)
    {
        disconnectPins({ chip1, pin1 }, { chip2, pin2 });
    }

    void disconnect(PinId pin, const K& compName, PinId compPin)
    {
        disconnectPins({ pin }, { compName, compPin });
    }

    void disconnect(PinId pin1, PinId pin2)
    {
        disconnectPins({ pin1 }, { pin2 });
    }

    // Circuit component
    virtual void tick() override
    {
        // tick unstable chips
        for (const auto& pair : m_chipsets) {
            IComponent& chip = *pair.second;

            if (!chip.stable()) {
                chip.tick();
            }
        }

        // propagate values through links
        propagateLinks();
        inputsClean();
    }

    virtual bool stable() const override
    {
        if (inputsDirty()) {
            return false;
        }

        for (const auto& pair : m_chipsets) {
            const IComponent& chip = *pair.second;

            if (!chip.stable()) {
                return false;
            }
        }

        return true;
    }

    virtual void display(std::ostream& os) const override
    {
        thread_local const std::size_t shiftWidth = 1;
        thread_local const std::string shift(shiftWidth, ' ');
        thread_local std::size_t level = 0;

        const std::string curShift(level * 2 * shiftWidth, ' ');

        // circuit
        os << "(circuit\n";

        // pins
        const auto& circuitPinout = pinout();
        bool breakPins = circuitPinout.size() >= 6;

        os << curShift << shift << "(pins";
        for (const auto& pin : circuitPinout) {
            if (breakPins) {
                os << "\n";
                os << curShift << shift << shift;
            } else {
                os << " ";
            }

            os << "(" << pin.first << " " << read(pin.first) << ")";
        }
        if (breakPins) {
            os << "\n";
            os << curShift << shift;
        }
        os << ")\n";

        // chipsets
        os << curShift << shift << "(chipsets\n";
        level++;
        for (const auto& c : m_chipsets) {
            os << curShift << shift << shift;

            os << "(" << c.first << " ";
            c.second->display(os);
            os << ")\n";
        }
        level--;
        os << curShift << shift << ")\n";

        // end circuit
        os << curShift << ")";
    }

private:
    using ChipPin = nts::ChipPin<K>;
    using PinSet = std::unordered_set<ChipPin>;
    using PinAdjencyList = std::unordered_map<ChipPin, PinSet>;

    std::unordered_map<K, std::unique_ptr<IComponent>> m_chipsets;
    PinAdjencyList m_pinLinks;

    void connectPins(ChipPin from, ChipPin to)
    {
        m_pinLinks[from].insert(to);
        m_pinLinks[to].insert(from);
    }

    void disconnectPins(ChipPin from, ChipPin to)
    {
        m_pinLinks[from].erase(to);
        m_pinLinks[to].erase(from);
    }

    void propagateLinks()
    {
        PinSet visitedPins;

        for (const auto& adjency : m_pinLinks) {
            const ChipPin& pin = adjency.first;

            if (visitedPins.find(pin) == visitedPins.end()) {
                PinSet links = findConnected<PinSet>(pin, m_pinLinks);
                Tristate linkValue = Tristate::UNDEFINED;

                // compute the common link value
                for (const ChipPin& pin : links) {
                    PinMode mode = pin.mode(*this, m_chipsets);

                    // only read from our INPUT pins and chips' OUTPUT pins
                    if (pin.owner
                            ? mode == PinMode::OUTPUT
                            : mode == PinMode::INPUT) {
                        linkValue = propagate(linkValue,
                            pin.read(*this, m_chipsets));
                    }

                    // break early if we find a high signal
                    if (linkValue == Tristate::TRUE) {
                        break;
                    }
                }

                // propagate the value to all connected pins
                for (const ChipPin& pin : links) {
                    PinMode mode = pin.mode(*this, m_chipsets);

                    // only write to our OUTPUT pins and chips' INPUT pins
                    if (pin.owner
                            ? mode == PinMode::INPUT
                            : mode == PinMode::OUTPUT) {
                        pin.write(*this, m_chipsets, linkValue);
                    }
                }

                visitedPins.insert(links.begin(), links.end());
            }
        }
    }
};

}

#endif /* !CIRCUIT_HPP_ */
