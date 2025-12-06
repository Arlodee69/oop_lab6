#pragma once
#include "npc.hpp"

class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y);
    std::string get_type() const override;
    void accept(Visitor& visitor) override;
};