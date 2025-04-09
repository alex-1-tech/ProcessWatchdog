cmake_minimum_required(VERSION 3.10)
project(ProcScope)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

find_package(Boost REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
