/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "AComponent.hpp"
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
    // Components
    void insert(const K& name, std::unique_ptr<IComponent> component)
    {
        m_chipsets.emplace(name, std::move(component));
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
    void connect(const K& name1, PinId pin1, const K& name2, PinId pin2)

    {
        auto& chip1 = *m_chipsets.at(name1);
        auto& chip2 = *m_chipsets.at(name2);

        m_adjencyList[{ chip1, pin1 }].insert({ chip2, pin2 });
        m_adjencyList[{ chip2, pin2 }].insert({ chip1, pin1 });
    }

    void connect(PinId pin, const K& compName, PinId compPin)
    {
        auto& chip = *m_chipsets.at(compName);
        auto mode = chip.pinout().at(compPin);

        const auto& circuitPinout = pinout();

        auto myMode = circuitPinout.find(pin);
        if (myMode != circuitPinout.end()) {
            mode = mode | myMode->second;
        }

        pinMode(pin, mode);

        m_pinLinks[pin].insert({ chip, compPin });
    }

    void disconnect(const K& name1, PinId pin1, const K& name2, PinId pin2)
    {
        auto& chip1 = m_chipsets.at(name1);
        auto& chip2 = m_chipsets.at(name2);

        m_adjencyList[{ chip1, pin1 }].erase({ chip2, pin2 });
        m_adjencyList[{ chip2, pin2 }].erase({ chip1, pin1 });
    }

    void disconnect(PinId pin, const K& compName, PinId compPin)
    {
        auto& chip = m_chipsets.at(compName);

        m_pinLinks[pin].erase({ chip, compPin });

        if (m_pinLinks[pin].empty()) {
            m_pinLinks.erase(pin);
            pinMode(pin, NONE);
        }
    }

    void simulate() override
    {
        bool stable = false;

        for (std::size_t i = 0; i < 10000 && !stable; i++) {
            stable = tick();
        }

        if (!stable) {
            throw std::runtime_error("reached max tick count before stability");
        }
    }

    virtual void display(std::ostream& os) const override
    {
    }

private:
    class Pin {
    public:
        Pin(IComponent& comp, PinId id)
            : m_component(comp)
            , m_id(id)
        {
        }

        Pin(const Pin& other)
            : m_component(other.m_component)
            , m_id(other.m_id)
        {
        }

        bool operator==(const Pin& other) const
        {
            return &m_component == &other.m_component && m_id == other.m_id;
        }

        Tristate read() const
        {
            return m_component.read(m_id);
        }

        void write(Tristate value) const
        {
            return m_component.write(m_id, value);
        }

        PinMode mode() const
        {
            return m_component.pinout().at(m_id);
        }

        IComponent& component()
        {
            return m_component;
        }

        const IComponent& component() const
        {
            return m_component;
        }

        PinId id() const
        {
            return m_id;
        }

    private:
        IComponent& m_component;
        PinId m_id;
    };

    struct PinHash {
        std::size_t operator()(const Pin& pin) const
        {
            std::size_t hash = 17;
            hash = hash * 31 + std::hash<const IComponent*>()(&pin.component());
            hash = hash * 31 + std::hash<PinId>()(pin.id());
            return hash;
        }
    };

    using PinSet = std::unordered_set<Pin, PinHash>;

    std::unordered_map<K, std::unique_ptr<IComponent>> m_chipsets;
    std::unordered_map<Pin, PinSet, PinHash> m_adjencyList;
    std::unordered_map<PinId, PinSet> m_pinLinks;

    PinSet findConnectedPins(Pin pin)
    {
        PinSet connected;
        PinSet pool = { pin };

        while (!pool.empty()) {
            Pin pin = *pool.begin();

            try {
                PinSet& links = m_adjencyList.at(pin);

                auto mbConnectedPin = std::find_if(links.begin(), links.end(),
                    [&](auto pin) {
                        return connected.find(pin) == connected.end()
                            && pool.find(pin) == pool.end();
                    });

                if (mbConnectedPin != links.end()) {
                    pool.insert(*mbConnectedPin);
                } else {
                    pool.erase(pin);
                    connected.insert(pin);
                }
            } catch (std::out_of_range&) {
                pool.erase(pin);
                connected.insert(pin);
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

    void propagateFromCircuitPins(std::unordered_set<IComponent*>& updateList)
    {
        for (auto& link : m_pinLinks) {
            auto value = read(link.first);

            for (auto dest : link.second) {
                auto oldValue = dest.read();

                if (oldValue != value) {
                    updateList.insert(&dest.component());
                }

                // we actually want to overwrite the old value here rather than
                // propagating them.
                // it will keep its value anyway, unless the user changed it.
                dest.write(value);
            }
        }
    }

    void propagateToCircuitPins()
    {
        for (auto& link : m_pinLinks) {
            Tristate value;

            for (const auto& source : link.second) {
                auto newValue = source.read();

                value = propagate(value, newValue);

                if (value == Tristate::TRUE) {
                    break;
                }
            }

            write(link.first, value);
        }
    }

    void propagateLinks(std::unordered_set<IComponent*>& updateList)
    {
        PinSet visitedPins;

        for (auto& adjency : m_adjencyList) {
            Pin pin = adjency.first;
            PinSet& links = adjency.second;

            if (visitedPins.find(pin) == visitedPins.end()) {
                PinSet linkedPins = findConnectedPins(pin);
                Tristate linkValue;

                // compute the common link value
                for (const auto& pin : linkedPins) {
                    // only take OUTPUT pins into account
                    if (~pin.mode() & OUTPUT) {
                        continue;
                    }

                    linkValue = propagate(linkValue, pin.read());

                    // early-break if we find a high signal
                    if (linkValue == Tristate::TRUE) {
                        break;
                    }
                }

                // propagate the value to all connected pins
                for (auto pin : linkedPins) {
                    // if its value changes, add it to the updateList
                    if (pin.read() != linkValue) {
                        updateList.insert(&pin.component());
                    }

                    pin.write(linkValue);
                }

                visitedPins.insert(linkedPins.begin(), linkedPins.end());
            }
        }
    }

    /**
     * @brief Simulates one micro-step of the entire circuitry.
     *
     * @return true At least one sub-component was simulated
     * @return false No sub-component was simulated.
     */
    bool tick()
    {
        std::unordered_set<IComponent*> updateList;

        // step 1: propagate our pins to our components' pins
        propagateFromCircuitPins(updateList);

        // step 2: propagate values through inner links
        propagateLinks(updateList);

        // step 3: simulate chips for which at least one pin changed
        for (auto& component : updateList) {
            component->simulate();
        }

        // step 4: propagate components' pins back to our own pins
        propagateToCircuitPins();

        return updateList.empty();
    }
};

}

#endif /* !CIRCUIT_HPP_ */
