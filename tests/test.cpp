#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <fstream>
#include <string>
#include "../include/game.hpp"
#include "../include/factory.hpp"
#include "../include/observer.hpp"
#include "../include/npc.hpp"
#include "../include/druid.hpp"
#include "../include/trader.hpp"
#include "../include/orc.hpp"

TEST(NPCTest, TypesAreCorrect) {
    Trader t("T", 0, 0);
    Orc o("O", 0, 0);
    Druid d("D", 0, 0);

    EXPECT_EQ(t.get_type(), "Trader");
    EXPECT_EQ(o.get_type(), "Orc");
    EXPECT_EQ(d.get_type(), "Druid");
}

// Работорговец убивает Друида
TEST(BattleTest, TraderKillsDruid) {
    Game game("test_log.txt");

    game.add_NPC("Trader", "T1", 0, 0);
    game.add_NPC("Druid", "D1", 0, 0);

    EXPECT_EQ(game.count_of_NPC(), 2);

    game.run_battle(1);

    EXPECT_EQ(game.count_of_NPC(), 1);  // Остался только Торговец
}

// Орк убивает всех, включая других Орков
TEST(BattleTest, OrcKillsEveryone) {
    Game game("test_log.txt");

    game.add_NPC("Orc", "O1", 0, 0);
    game.add_NPC("Orc", "O2", 0, 0);
    game.run_battle(1);
    EXPECT_EQ(game.count_of_NPC(), 0);  // Оба орка убивают друг друга
}

// Друид не убивает, но может быть убит
TEST(BattleTest, DruidCanBeKilled) {
    Game game("test_log.txt");

    game.add_NPC("Druid", "D1", 0, 0);
    game.add_NPC("Trader", "T1", 0, 0);

    game.run_battle(10);

    EXPECT_EQ(game.count_of_NPC(), 1);  // Остался только Trader
}

TEST(GameTest, SaveAndLoad) {
    Game game1("log1.txt");
    game1.add_NPC("Trader", "T1", 50, 60);
    game1.add_NPC("Orc", "O1", 70, 80);

    game1.save_to_file("test_save.txt");

    Game game2("log2.txt");
    game2.load_from_file("test_save.txt");

    EXPECT_EQ(game2.count_of_NPC(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}