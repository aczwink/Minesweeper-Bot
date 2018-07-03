cmake_minimum_required(VERSION 3.6)
project(MinesweeperBot)
find_package(XP-CMake REQUIRED) #we need advanced cmake modules

set(CMAKE_CXX_STANDARD 11)
XPC_AutoBuildType()
XPC_SetCompileDefinitions()
find_package(StdPlusPlus REQUIRED)

add_executable(MinesweeperBot src/Log.cpp src/Log.hpp src/LogViewController.cpp src/LogViewController.hpp src/main.cpp src/MainWindow.hpp src/MainWindow.cpp src/MinesweeperBot.cpp src/MinesweeperBot.hpp src/MineSweeperInterface.hpp src/MineSweeperXPInterface.cpp src/MineSweeperXPInterface.hpp)
target_link_libraries(MinesweeperBot Std++ Std++Static)