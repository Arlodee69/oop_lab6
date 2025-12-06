#pragma once
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include "npc.hpp"

class NPC_factory {
    public:
        virtual ~NPC_factory() = default;
        virtual std::unique_ptr<NPC> create_NPC(const std::string& type, const std::string& name, int x, int y) = 0;
        virtual std::unique_ptr<NPC> load_NPC(const std::string& data) = 0;
};

class concrete_NPC_factory: public NPC_factory {
    public:
        std::unique_ptr<NPC> create_NPC(const std::string& type, const std::string& name, int x, int y) override;
        std::unique_ptr<NPC> load_NPC(const std::string& data) override;
};
