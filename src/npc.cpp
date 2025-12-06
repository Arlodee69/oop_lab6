#include "../include/npc.hpp"

NPC::NPC(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
const std::string& NPC::get_name() const {return name;};

int NPC::get_x() const {return x;}

int NPC::get_y() const {return y;}