#pragma once
#include <string>

class Visitor;

class NPC {
    protected:
        std::string name;
        int x, y;
    
    public:
        NPC(const std::string& name, int x, int y);
        virtual ~NPC() = default;

        const std::string& get_name() const;
        int get_x() const;
        int get_y() const;
        virtual std::string get_type() const = 0;

        virtual void accept(Visitor& visitor) = 0;
};