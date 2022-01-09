cmake_minimum_required(VERSION 3.6)
project(MinesweeperBot)
find_package(XP-CMake REQUIRED) #we need advanced cmake modules

set(CMAKE_CXX_STANDARD 20)
XPC_AutoBuildType()
XPC_SetCompileDefinitions()
find_package(StdPlusPlus REQUIRED)

set(SRC_FILES_SHARED
    src/minesweeper_interfaces/MemoryMineSweeper.cpp
    src/minesweeper_interfaces/MemoryMineSweeper.hpp

    src/model/BoardState.cpp
    src/model/BoardState.hpp
        src/model/MoveComputer.cpp
        src/model/MoveComputer.hpp
)

add_executable(MinesweeperBot ${SRC_FILES_SHARED} src/main.cpp src/model/BoxState.hpp src/model/MineSweeperInterface.hpp src/model/GameMove.hpp src/view/MainWindow.hpp src/view/MainWindow.cpp src/model/MovesLogger.hpp src/view/MainWindowLogger.hpp src/view/MainWindowLogger.cpp src/model/MineSweeperBot.hpp src/model/MineSweeperBot.cpp src/model/PlayingState.hpp src/view/LogViewController.hpp src/view/LogViewController.cpp)
target_link_libraries(MinesweeperBot Std++ Std++Static)

add_executable(MineSweeperBotTests ${SRC_FILES_SHARED} src_tests/3x3tests.cpp src_tests/BoardBuilder.hpp)
target_link_libraries(MineSweeperBotTests Std++ Std++Static Std++Test)