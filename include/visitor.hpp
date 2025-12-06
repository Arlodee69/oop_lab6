#pragma once
#include <vector>
#include <cmath>
#include "npc.hpp"

class Trader;
class Orc;
class Druid;

class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void Visit(Trader& trader) = 0;
    virtual void Visit(Orc& orc) = 0;
    virtual void Visit(Druid& druid) = 0;
};

class Concrete_visitor_battle: public Visitor {
private:
    int range;
    std::vector<NPC*> opponents;
    std::vector<NPC*> killed;

public:
    Concrete_visitor_battle(int range);

    void Visit(Trader& trader) override;
    void Visit(Orc& orc) override;
    void Visit(Druid& druid) override;

    void see_opponents(const std::vector<NPC*>& npcs);
    std::vector<NPC*> get_killed() const;

    bool in_range(const NPC& npc_1, const NPC& npc_2) const;
};