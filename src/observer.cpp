#include "../include/observer.hpp"

File_observer::File_observer(const std::string& filename) : filename(filename) {}

void File_observer::update(const std::string& message) {
    std::ofstream file(filename, std::ios::app);

    if (file.is_open()) {
        file << message << std::endl;
        file.close();
    } else {
        std::cerr << "Невозможно открыть файл" << std::endl;
    }
}

void Console_observer::update(const std::string& message) {
    std::cout << message <<std::endl;
}
