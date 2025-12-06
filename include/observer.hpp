#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Observer {
    public:
        virtual ~Observer() = default;
        virtual void update(const std::string& message) = 0;
};

class File_observer: public Observer {
    private:
        std::string filename;

    public: File_observer(const std::string& filename);
    void update(const std::string& message) override;
};

class Console_observer: public Observer {
    public:
        void update(const std::string& message) override;
};