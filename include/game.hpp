#pragma once
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "npc.hpp"
#include "factory.hpp"
#include "observer.hpp"
#include "visitor.hpp"

class Game {
    private:
        std::vector<std::unique_ptr<NPC>> npcs;
        std::unique_ptr<NPC_factory> factory;
        std::vector<std::shared_ptr<Observer>> observers;
        std::string log_file;

        void notify_observers(const std::string& message);
        void wipe_logfile();
    
    public:
        Game(const std::string& log_filename);
        virtual ~Game() = default;

        void add_NPC(const std::string& type, const std::string& name, int x, int y);
        void save_to_file(const std::string& filename) const;
        void load_from_file(const std::string& filename);
        void print_NPC() const;
        void run_battle(int range);

        void add_observer(std::shared_ptr<Observer> observer);
        size_t count_of_NPC() const noexcept;
};