#include "../include/orc.hpp"
#include "../include/visitor.hpp"

Orc::Orc(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Orc::get_type() const {
    return "Orc";
}

void Orc::accept(Visitor& visitor) {
    visitor.Visit(*this);
}