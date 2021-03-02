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
#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace nts {

template <typename K>
class Circuit : public AComponent {
public:
    Circuit()
    {
    }

    Circuit(Circuit&& other)
        : AComponent(std::move(other))
        , m_adjencyList(std::move(other.m_adjencyList))
        , m_chipsets(std::move(other.m_chipsets))
        , m_directPinLinks(std::move(other.m_directPinLinks))
        , m_pinLinks(std::move(other.m_pinLinks))
        , m_maxTickPerSimulation(other.m_maxTickPerSimulation)
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
        m_adjencyList[{ chip1, pin1 }].insert({ chip2, pin2 });
        m_adjencyList[{ chip2, pin2 }].insert({ chip1, pin1 });
    }

    void disconnect(const K& chip1, PinId pin1, const K& chip2, PinId pin2)
    {
        m_adjencyList[{ chip1, pin1 }].erase({ chip2, pin2 });
        m_adjencyList[{ chip2, pin2 }].erase({ chip1, pin1 });
    }

    void connect(PinId pin, const K& compName, PinId compPin)
    {
        m_pinLinks[pin].insert({ compName, compPin });
    }

    void disconnect(PinId pin, const K& compName, PinId compPin)
    {
        m_pinLinks[pin].erase({ compName, compPin });

        if (m_pinLinks[pin].empty()) {
            m_pinLinks.erase(pin);
        }
    }

    void connect(PinId pin1, PinId pin2)
    {
        if (pin1 != pin2) {
            m_directPinLinks[pin1].insert(pin2);
            m_directPinLinks[pin2].insert(pin1);
        }
    }

    void disconnect(PinId pin1, PinId pin2)
    {
        if (pin1 != pin2) {
            m_directPinLinks[pin1].erase(pin2);
            if (m_directPinLinks[pin1].empty()) {
                m_directPinLinks.erase(pin1);
            }

            m_directPinLinks[pin2].erase(pin1);
            if (m_directPinLinks[pin2].empty()) {
                m_directPinLinks.erase(pin2);
            }
        }
    }

    virtual void tick() override
    {
        // step 1: propagate directly connected pins (like in a buffer)
        propagateDirectLinks();

        // step 2: propagate our pins to our components' pins
        propagateFromCircuitPins();

        // step 3: tick unstable chips
        for (const auto& pair : m_chipsets) {
            IComponent& chip = *pair.second;

            if (!chip.stable()) {
                chip.tick();
            }
        }

        // step 4: propagate values through inner links
        propagateLinks();

        // step 5: propagate components' pins back to our own pins
        propagateToCircuitPins();
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
    using ChipMap = std::unordered_map<K, std::unique_ptr<IComponent>>;

    class Pin {
    public:
        Pin(K comp, PinId id)
            : m_compName(comp)
            , m_id(id)
        {
        }

        Pin(const Pin& other)
            : m_compName(other.m_compName)
            , m_id(other.m_id)
        {
        }

        bool operator==(const Pin& other) const
        {
            return m_compName == other.m_compName && m_id == other.m_id;
        }

        Tristate read(const ChipMap& chips) const
        {
            return chips.at(m_compName)->read(m_id);
        }

        void write(ChipMap& chips, Tristate value) const
        {
            return chips.at(m_compName)->write(m_id, value);
        }

        PinMode mode(const ChipMap& chips) const
        {
            return chips.at(m_compName)->pinout().at(m_id);
        }

        const K& compName() const
        {
            return m_compName;
        }

        PinId id() const
        {
            return m_id;
        }

    private:
        K m_compName;
        PinId m_id;
    };

    struct PinHash {
        std::size_t operator()(const Pin& pin) const
        {
            std::size_t hash = 17;
            hash = hash * 31 + std::hash<K>()(pin.compName());
            hash = hash * 31 + std::hash<PinId>()(pin.id());
            return hash;
        }
    };

    using PinSet = std::unordered_set<Pin, PinHash>;
    using PinAdjencyList = std::unordered_map<Pin, PinSet, PinHash>;
    using PinIdSet = std::unordered_set<PinId>;
    using PinIdAdjencyList = std::unordered_map<PinId, PinIdSet>;

    ChipMap m_chipsets;
    std::unordered_map<PinId, PinSet> m_pinLinks;
    PinAdjencyList m_adjencyList;
    PinIdAdjencyList m_directPinLinks;

    std::size_t m_maxTickPerSimulation;

    template <typename Node, typename Set, typename AdjencyList>
    Set findConnected(Node node, const AdjencyList& adjencyList)
    {
        Set connected;
        Set pool = { node };

        while (!pool.empty()) {
            const Node& node = *pool.begin();

            try {
                const Set& links = adjencyList.at(node);

                auto mbConnectedPin = std::find_if(links.begin(), links.end(),
                    [&](auto node) {
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

    void propagateFromCircuitPins()
    {
        for (const auto& link : m_pinLinks) {
            Tristate value = read(link.first);

            for (const Pin& dest : link.second) {
                Tristate oldValue = dest.read(m_chipsets);

                // we actually want to overwrite the old value here rather than
                // propagating them.
                // it will keep its value anyway, unless the user changed it.
                dest.write(m_chipsets, value);
            }
        }
    }

    void propagateToCircuitPins()
    {
        for (auto& link : m_pinLinks) {
            Tristate value = Tristate::UNDEFINED;

            for (const Pin& source : link.second) {
                Tristate newValue = source.read(m_chipsets);

                value = propagate(value, newValue);

                if (value == Tristate::TRUE) {
                    break;
                }
            }

            write(link.first, value);
        }
    }

    void propagateLinks()
    {
        PinSet visitedPins;

        for (const auto& adjency : m_adjencyList) {
            const Pin& pin = adjency.first;

            if (visitedPins.find(pin) == visitedPins.end()) {
                PinSet links = findConnected<Pin, PinSet>(pin, m_adjencyList);
                Tristate linkValue = Tristate::UNDEFINED;

                // compute the common link value
                for (const Pin& pin : links) {
                    // only take OUTPUT pins into account
                    if (pin.mode(m_chipsets) != PinMode::OUTPUT) {
                        continue;
                    }

                    linkValue = propagate(linkValue, pin.read(m_chipsets));

                    // break early if we find a high signal
                    if (linkValue == Tristate::TRUE) {
                        break;
                    }
                }

                // propagate the value to all connected pins
                for (const Pin& pin : links) {
                    // only set INPUT pins
                    if (pin.mode(m_chipsets) != PinMode::INPUT) {
                        continue;
                    }

                    pin.write(m_chipsets, linkValue);
                }

                visitedPins.insert(links.begin(), links.end());
            }
        }
    }

    void propagateDirectLinks()
    {
        PinIdSet visitedPins;
        const Pinout& myPinout = pinout();

        for (const auto& link : m_directPinLinks) {
            PinId pin = link.first;

            if (visitedPins.find(pin) == visitedPins.end()) {
                PinIdSet links = findConnected<PinId, PinIdSet>(pin,
                    m_directPinLinks);
                Tristate linkValue = Tristate::UNDEFINED;

                // compute the common link value
                for (const auto& pin : links) {
                    // only take INPUT pins into account: *INPUT* => OUTPUT
                    if (myPinout.at(pin) != PinMode::INPUT) {
                        continue;
                    }

                    linkValue = propagate(linkValue, read(pin));

                    // break early if we find a high signal
                    if (linkValue == Tristate::TRUE) {
                        break;
                    }
                }

                // propagate the value to all connected pins
                for (auto pin : links) {
                    // only set OUTPUT pins: INPUT => *OUTPUT*
                    if (myPinout.at(pin) != PinMode::OUTPUT) {
                        continue;
                    }

                    write(pin, linkValue);
                }

                visitedPins.insert(links.begin(), links.end());
            }
        }
    }
};

}

#endif /* !CIRCUIT_HPP_ */
