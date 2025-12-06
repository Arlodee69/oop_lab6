#pragma once
#include "npc.hpp"

class Orc : public NPC {
public:
    Orc(const std::string& name, int x, int y);
    std::string get_type() const override;
    void accept(Visitor& visitor) override;
};