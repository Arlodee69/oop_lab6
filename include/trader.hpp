#pragma once
#include "npc.hpp"

class Trader : public NPC { // Работорговец
public:
    Trader(const std::string& name, int x, int y);
    std::string get_type() const override;
    void accept(Visitor& visitor) override;
};