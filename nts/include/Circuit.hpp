/*
** EPITECH PROJECT, 2021
** B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "DynamicPinoutBuffer.hpp"
#include "IComponent.hpp"
#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace nts {

template <typename K>
class Circuit : public IComponent {
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
        auto& chip1 = m_chipsets.at(name1);
        auto& chip2 = m_chipsets.at(name2);

        m_adjencyList[{ &chip1, pin1 }].insert({ &chip2, pin2 });
        m_adjencyList[{ &chip2, pin2 }].insert({ &chip1, pin1 });
    }

    void connect(PinId pin, const K& compName, PinId compPin)
    {
        auto& chip = m_chipsets.at(compName);

        m_adjencyList[{ pin }].insert({ &chip, compPin });
        m_adjencyList[{ &chip, compPin }].insert({ pin });
    }

    void disconnect(const K& name1, PinId pin1, const K& name2, PinId pin2)

    {
        auto& chip1 = m_chipsets.at(name1);
        auto& chip2 = m_chipsets.at(name2);

        m_adjencyList[{ &chip1, pin1 }].erase({ &chip2, pin2 });
        m_adjencyList[{ &chip2, pin2 }].erase({ &chip1, pin1 });
    }

    void disconnect(PinId pin, const K& compName, PinId compPin)
    {
        auto& chip = m_chipsets.at(compName);

        m_adjencyList[{ pin }].erase({ &chip, compPin });
        m_adjencyList[{ &chip, compPin }].erase({ pin });
    }

    // Circuit as a Component
    Pinout pinout() const override
    {
        Pinout pinout;

        for (auto& adjency : m_adjencyList) {
            if (adjency.first.m_chip == nullptr) {
                // TODO: compute the flags satisfying to all connections
                pinout[adjency.first.m_id] = nts::PinUsage::IO;
            }
        }

        return pinout;
    }

    void simulate(IPinoutBuffer& pbuf) override
    {
        bool stable = false;

        while (!stable) {
            stable = tick(pbuf);
        }
    }

    virtual void display(std::ostream&) const override { }

private:
    class Chipset : public IPinoutBuffer {
    public:
        Chipset(std::unique_ptr<IComponent> comp)
            : m_component(std::move(comp))
        {
        }

        IComponent& operator*()
        {
            return *m_component;
        }

        const IComponent& operator*() const
        {
            return *m_component;
        }

        void simulate()
        {
            m_component->simulate(m_pbuf);
        }

        Tristate operator[](PinId pin) const
        {
            return m_pbuf.read(pin);
        }

        Tristate read(PinId pin) const
        {
            return m_pbuf.read(pin);
        }

        void write(PinId pin, Tristate value)
        {
            return m_pbuf.write(pin, value);
        }

    private:
        std::unique_ptr<IComponent> m_component;
        DynamicPinoutBuffer m_pbuf;
    };

    class Pin {
    public:
        Chipset* m_chip = nullptr;
        PinId m_id = 0;

        Pin(Chipset* chip, PinId id)
            : m_chip(chip)
            , m_id(id)
        {
        }

        Pin(PinId id)
            : m_id(id)
        {
        }

        Pin(const Pin& other)
        {
            *this = other;
        }

        Pin& operator=(const Pin& other)
        {
            m_chip = other.m_chip;
            m_id = other.m_id;
            return *this;
        }

        bool operator==(const Pin& other) const
        {
            return m_chip == other.m_chip && m_id == other.m_id;
        }

        Tristate read(IPinoutBuffer& default_buf) const
        {
            if (m_chip) {
                return m_chip->read(m_id);
            } else {
                return default_buf.read(m_id);
            }
        }

        void write(IPinoutBuffer& default_buf, Tristate value) const
        {
            if (m_chip) {
                m_chip->write(m_id, value);
            } else {
                default_buf.write(m_id, value);
            }
        }
    };

    struct PinHash {
        std::size_t operator()(const Pin& pin) const
        {
            std::size_t hash = 17;
            hash = hash * 31 + std::hash<const Chipset*>()(pin.m_chip);
            hash = hash * 31 + std::hash<PinId>()(pin.m_id);
            return hash;
        }
    };

    using PinSet = std::unordered_set<Pin, PinHash>;

    std::unordered_map<K, Chipset> m_chipsets;
    std::unordered_map<Pin, PinSet, PinHash> m_adjencyList;

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

    bool tick(IPinoutBuffer& pbuf)
    {
        PinSet visitedPins;
        std::unordered_set<Chipset*> updateList;

        // step 1: propagate values through links
        for (auto& adjency : m_adjencyList) {
            Pin pin = adjency.first;
            PinSet& links = adjency.second;

            if (visitedPins.find(pin) == visitedPins.end()) {
                PinSet linkedPins = findConnectedPins(pin);
                Tristate linkValue;

                // compute the link value
                for (const Pin& pin : linkedPins) {
                    Tristate pinval = pin.read(pbuf);

                    if (pinval != Tristate::UNDEFINED) {
                        linkValue = pinval;
                    }

                    // early-break if we find a high signal
                    if (linkValue == Tristate::TRUE) {
                        break;
                    }
                }

                // spread the link value to all pins
                for (const Pin& pin : linkedPins) {
                    auto oldVal = pin.read(pbuf);

                    if (oldVal != linkValue) {
                        if (pin.m_chip) {
                            updateList.insert(pin.m_chip);
                        }

                        pin.write(pbuf, linkValue);
                    }
                }

                visitedPins.insert(linkedPins.begin(), linkedPins.end());
            }
        }

        // step 2: simulate chips for which at least one pin changed
        for (auto chip : updateList) {
            chip->simulate();
        }

        return updateList.empty();
    }
};

}

#endif /* !CIRCUIT_HPP_ */
