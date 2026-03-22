cmake_minimum_required(VERSION 4.1)
project(Oasencrawler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Oasencrawler main.cpp
        GameBoard.cpp
        GameBoard.h
        Tile.h
        Coordinate.h
        GameState.h
        Item.h)
