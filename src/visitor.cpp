#include "../include/visitor.hpp"
#include "../include/trader.hpp"
#include "../include/orc.hpp"
#include "../include/druid.hpp"
#include <algorithm>

Concrete_visitor_battle::Concrete_visitor_battle(int range) : range(range) {}

void Concrete_visitor_battle::see_opponents(const std::vector<NPC*>& npcs) {
    opponents = npcs;
}

bool Concrete_visitor_battle::in_range(const NPC& npc_1, const NPC& npc_2) const {
    int dx = npc_1.get_x() - npc_2.get_x();
    int dy = npc_1.get_y() - npc_2.get_y();
    return (dx * dx + dy * dy) <= (range * range);
}

void Concrete_visitor_battle::Visit(Trader& trader) {
    for (auto opponent : opponents) {
        if (&trader == opponent) continue; // не атакует себя

        // Работорговец убивает Друидов
        if (Druid* druid = dynamic_cast<Druid*>(opponent)) {
            if (in_range(trader, *druid)) {
                killed.push_back(druid);
            }
        }
    }
}

void Concrete_visitor_battle::Visit(Orc& orc) {
    for (auto opponent : opponents) {
        if (&orc == opponent) continue; // не атакует себя

        // Орк убивает ВСЕХ (включая других орков)
        if (in_range(orc, *opponent)) {
            killed.push_back(opponent);
        }
    }
}

void Concrete_visitor_battle::Visit(Druid& druid) {
    // Друид никого не трогает
}

std::vector<NPC*> Concrete_visitor_battle::get_killed() const {
    return killed;
}