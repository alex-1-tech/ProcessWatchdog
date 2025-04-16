cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ProcScope)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Concurrent Test)
find_package(Boost REQUIRED)

enable_testing()

include_directories(src/)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
)

file(GLOB_RECURSE TEST_SOURCES
    "tests/*.cpp"
    "tests/*.h"
)

add_library(proc_core ${SOURCES})
target_link_libraries(proc_core
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Concurrent
    ${Boost_LIBRARIES}
)
target_include_directories(proc_core PUBLIC src/)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} proc_core)

add_executable(unit_tests ${TEST_SOURCES})
target_include_directories(unit_tests PRIVATE tests/)
target_link_libraries(unit_tests
    proc_core
    Qt5::Test
)

add_test(NAME unit_tests COMMAND unit_tests)
