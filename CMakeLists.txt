cmake_minimum_required(VERSION 4.3)

project(SpaceInvaders)

add_subdirectory(vendor/SDL/)

add_executable(SpaceInvaders)
target_sources(SpaceInvaders
    PRIVATE
        src/main.cpp
        src/engine/init.cpp
)
target_link_libraries(SpaceInvaders PRIVATE SDL3::SDL3)
