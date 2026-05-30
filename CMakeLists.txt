cmake_minimum_required(VERSION 4.3)

project(SpaceInvaders)

add_subdirectory(vendor/SDL/)

add_executable(SpaceInvaders)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

target_sources(SpaceInvaders
    PRIVATE
        ${SRC_FILES}
)
target_include_directories(SpaceInvaders PRIVATE src/)
target_link_libraries(SpaceInvaders PRIVATE SDL3::SDL3)
