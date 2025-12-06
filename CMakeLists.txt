cmake_minimum_required(VERSION 3.14)
project(NPC_Battle_Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(GTest QUIET)

set(COMMON_SOURCES
    src/npc.cpp
    src/trader.cpp
    src/orc.cpp
    src/druid.cpp
    src/factory.cpp
    src/game.cpp
    src/observer.cpp
    src/visitor.cpp
)

include_directories(include)

# Основной исполняемый файл
add_executable(${PROJECT_NAME}
    ${COMMON_SOURCES}
    main.cpp
)

if(GTest_FOUND)
    enable_testing()

    add_executable(tests
        tests/test.cpp
        ${COMMON_SOURCES}
    )

    target_include_directories(tests PRIVATE include)

    target_link_libraries(tests
        GTest::gtest
        GTest::gtest_main
        ${CMAKE_THREAD_LIBS_INIT}
    )

    add_test(NAME GameTests COMMAND tests)
else()
    message(STATUS "Google Test not found — tests will not be built.")
endif()