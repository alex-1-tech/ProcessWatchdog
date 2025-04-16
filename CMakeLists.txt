cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ProcScope)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Concurrent)

find_package(Boost REQUIRED)

include_directories(
    src/
)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} 
    Qt5::Core 
    Qt5::Widgets 
    Qt5::Gui
    Qt5::Concurrent
)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
