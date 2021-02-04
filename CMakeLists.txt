cmake_minimum_required(VERSION 3.15)
project(PROJ6)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PROJ6
        building.cpp
        building.hpp
        controller.hpp
        curses_controller.cpp
        curses_controller.hpp
        curses_view.cpp
        curses_view.hpp
        game.cpp
        game.hpp
        interface_type.hpp
        item.cpp
        item.hpp
        map_segment.cpp
        map_segment.hpp
        print_controller.cpp
        print_controller.hpp
        print_view.cpp
        print_view.hpp
        view.cpp
        view.hpp)
