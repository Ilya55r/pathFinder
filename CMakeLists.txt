cmake_minimum_required(VERSION 3.8)

project(pathFinder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

set(GRID
    grid/gridscene.cpp grid/gridscene.h
    grid/wallitem.cpp grid/wallitem.h
    grid/gridview.h grid/gridview.cpp
    grid/pathitem.h grid/pathitem.cpp
    grid/helper.h
    grid/global.h)

SET(PATH_FINDER
    pathFinder/pathfinder.h
    pathFinder/pathfinder.cpp
    pathFinder/global.h)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    helper.h
)

add_executable(main main.cpp ${PROJECT_SOURCES})
add_library(grid SHARED ${GRID})
add_library(finder SHARED ${PATH_FINDER})
target_link_libraries(finder Qt5::Core)
target_compile_definitions(finder PUBLIC FINDERSHAREDLIB_LIBRARY)
target_link_libraries(grid Qt5::Widgets Qt5::Gui Qt5::Core finder)
target_compile_definitions(grid PUBLIC GRIDSHAREDLIB_LIBRARY)
target_link_libraries(main grid Qt5::Widgets Qt5::Gui Qt5::Core)
