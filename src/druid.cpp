#include "../include/druid.hpp"
#include "../include/visitor.hpp"

Druid::Druid(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Druid::get_type() const {
    return "Druid";
}

void Druid::accept(Visitor& visitor) {
    visitor.Visit(*this);
}