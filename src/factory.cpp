#include "../include/factory.hpp"
#include "../include/trader.hpp"
#include "../include/orc.hpp"
#include "../include/druid.hpp"

std::unique_ptr<NPC> concrete_NPC_factory::create_NPC(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Trader") {
        return std::make_unique<Trader>(name, x, y);
    } else if (type == "Orc") {
        return std::make_unique<Orc>(name, x, y);
    } else if (type == "Druid") {
        return std::make_unique<Druid>(name, x, y);
    } else {
        throw std::invalid_argument("Некорректный тип NPC");
    }
}

std::unique_ptr<NPC> concrete_NPC_factory::load_NPC(const std::string& data) {
    std::istringstream iss(data);
    std::string type, name;
    int x, y;

    iss >> type >> name >> x >> y;
    return create_NPC(type, name, x, y);
}