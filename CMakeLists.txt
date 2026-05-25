cmake_minimum_required(VERSION 4.3)

project(SpaceInvaders)

add_subdirectory(vendor/SDL/)

add_executable(SpaceInvaders)
target_sources(SpaceInvaders
    PRIVATE
        src/main.cpp
        src/engine/init.cpp
        src/engine/renderer
)
target_include_directories(SpaceInvaders PRIVATE src/engine)
target_link_libraries(SpaceInvaders PRIVATE SDL3::SDL3)
