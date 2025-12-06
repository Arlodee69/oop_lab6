#include "include/game.hpp"
#include <iostream>
#include <stdexcept>

void menu() {
    std::cout << std::endl;
    std::cout << "1. Добавление NPCs" << std::endl;
    std::cout << "2. Загрузка из файла" << std::endl;
    std::cout << "3. Пуск битв" << std::endl;
    std::cout << "4. Сохранение игры" << std::endl;
    std::cout << "5. Вывод всех NPC" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
}

void choice_of_NPC() {
    std::cout << "Выберете, кого добавить." << std::endl;
    std::cout << "1. Торговец" << std::endl;
    std::cout << "2. Орк" << std::endl;
    std::cout << "3. Друид" << std::endl;
    std::cout << "Ваш выбор: ";
}

void add_NPC(Game& game) {
    int choice;
    size_t count_of_NPC = game.count_of_NPC();
    std::string name;
    int x, y;

    choice_of_NPC();
    std::cin >> choice;
    std::cout << "Введите координаты вида х y: ";
    std::cin >> x >> y;

    if(choice == 1){
        name = "Торговец_" + std::to_string(count_of_NPC);
        game.add_NPC("Trader", name, x, y);
    } else if(choice == 2){
        name = "Орк_" + std::to_string(count_of_NPC);
        game.add_NPC("Orc", name, x, y);
    } else if(choice == 3){
        name = "Друид_" + std::to_string(count_of_NPC);
        game.add_NPC("Druid", name, x, y);
    } else {
        std::cout << "Неверный выбор." << std::endl;
    }
}

void NPC_from_file(Game& game) {
    try {
        game.load_from_file("game_state.txt");
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void run_battle(Game& game) {
    int range;
    std::cout << "Введите диапазон: ";
    std::cin >> range;
    if(range < 0){ range = -range; }
    game.run_battle(range);
    game.print_NPC();
}

void save_game(Game& game) {
    try {
        game.save_to_file("game_state.txt");
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Инициализация игры";
    const std::string log_filename = "battle_log.txt";
    Game game(log_filename);
    game.add_observer(std::make_shared<Console_observer>());
    game.add_observer(std::make_shared<File_observer>(log_filename));

    int choice;
    do {
        menu();
        std::cin >> choice;
        
        switch (choice) {
        case 1:
            add_NPC(game);
            std::cout << "NPC добавлен." << std::endl;
            break;
        case 2:
            NPC_from_file(game);
            std::cout << "Игра загружена." << std::endl;
            break;
        case 3:
            run_battle(game);
            std::cout << "Конец батлов." << std::endl;
            break;
        case 4:
            save_game(game);
            std::cout << "Игра сохранена." << std::endl;
            break;
        case 5:
            game.print_NPC();
            break;
        case 0:
            std::cout << "Выход из игры." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    } while (choice != 0);

    return 0;
}