cmake_minimum_required(VERSION 3.5)

project(tower-defense-mars VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_HEADERS
    src/include/mainwindow.h
    src/include/game.hpp
    src/include/cockroach.h
    src/include/child_cockroach.h
    src/include/adult_cockroach.h
    src/include/mother_cockroach.h
    src/include/tower.h
    src/include/bullet.h
    src/include/basic_tower.h
    src/include/machine_gun_tower.h
    src/include/shotgun_tower.h
    src/include/build_basic_tower_icon.hpp
    src/include/build_machine_gun_tower_icon.hpp
    src/include/build_shotgun_tower_icon.hpp
    src/include/wallet.hpp
    src/include/item_placeble_tile.h
    src/include/item_not_placeble_tile.h
)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/game.cpp
        src/cockroach.cpp
        src/child_cockroach.cpp
        src/adult_cockroach.cpp
        src/mother_cockroach.cpp
        src/mainwindow.ui
        src/tower.cpp
        src/bullet.cpp
        src/basic_tower.cpp
        src/machine_gun_tower.cpp
        src/shotgun_tower.cpp
        src/build_basic_tower_icon.cpp
        src/build_machine_gun_tower_icon.cpp
        src/build_shotgun_tower_icon.cpp
        src/wallet.cpp
        src/item_placeble_tile.cpp
        src/item_not_placeble_tile.cpp
)

qt6_add_resources(PROJECT_SOURCES resouce.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tower-defense-mars
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES} ${PROJECT_HEADERS}
)
endif()



target_include_directories(tower-defense-mars PRIVATE src src/include)
target_link_libraries(tower-defense-mars PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tower-defense-mars)
endif()

