#include "../include/trader.hpp"
#include "../include/visitor.hpp"

Trader::Trader(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Trader::get_type() const {
    return "Trader";
}

void Trader::accept(Visitor& visitor) {
    visitor.Visit(*this);
}