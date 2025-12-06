#include "../include/game.hpp"
#include <set>

void Game::notify_observers(const std::string& message) {
    for(auto& obs : observers) {
        obs->update(message);
    }
}

void Game::wipe_logfile() {
    std::ofstream log_f(log_file, std::ofstream::out | std::ofstream::trunc);

    if (log_f.is_open()) {
        log_f.close();
    } else {
        std::cerr << "Невозможно открыть файл" << std::endl;
    }
}

Game::Game(const std::string& log_file): factory(std::make_unique<concrete_NPC_factory>()), log_file(log_file) {
    wipe_logfile();
}

void Game::add_NPC(const std::string& type, const std::string& name, int x, int y) {
    if(x < 0 || x > 500 || y < 0 || y > 500) {throw std::invalid_argument("Некорректные координаты");}
    npcs.push_back(factory->create_NPC(type, name, x, y));
}

void Game::save_to_file(const std::string& filename) const {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const auto& npc : npcs) {
            file << npc->get_type() << " " << npc->get_name() << " " << npc->get_x() << " " << npc->get_y() << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Невозможно сохранить в файл" << std::endl;
    }
}

void Game::load_from_file(const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        npcs.clear();
        std::string line;
        while (std::getline(file, line)) {
            npcs.push_back(factory->load_NPC(line));
        }
        file.close();
    } else {
        std::cerr << "Невозможно открыть файл" << std::endl;
    }
}

void Game::print_NPC() const {
    for (const auto& npc : npcs) {
        std::cout << npc->get_type() << " " << npc->get_name() << " at (" << npc->get_x() << ", " << npc->get_y() << ")" << std::endl;
    }
}

void Game::run_battle(int range) {
    Concrete_visitor_battle visitor(range); 
    std::vector<NPC*> npc_ptrs;

    for (auto& npc : npcs) { 
        npc_ptrs.push_back(npc.get());
    }

    visitor.see_opponents(npc_ptrs);

    for (auto& npc : npcs) {
        npc->accept(visitor);
    }

    auto killed = visitor.get_killed();
    std::set<NPC*> unique_killed(killed.begin(), killed.end());
    std::vector<NPC*> killed_NPC(unique_killed.begin(), unique_killed.end());

    for (auto killed_npc : killed_NPC) {
        std::string message = killed_npc->get_type() + " " + killed_npc->get_name() + " был убит";
        notify_observers(message);
    }

    for (auto it = npcs.begin(); it != npcs.end();) {
        if (std::find(killed_NPC.begin(), killed_NPC.end(), it->get()) != killed_NPC.end()) {
            it = npcs.erase(it);
        } else {
            ++it; 
        }
    }
}

void Game::add_observer(std::shared_ptr<Observer> observer) { 
    observers.push_back(observer);
}

size_t Game::count_of_NPC() const noexcept {
    return npcs.size();
}