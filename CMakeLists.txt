cmake_minimum_required(VERSION 3.16)

project(Pacman
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(pacman
    ${SOURCES}
)

find_package(SFML 3.0.2 COMPONENTS Graphics Window System Audio REQUIRED)

target_link_libraries(pacman
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
)

target_include_directories(pacman
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_custom_command(
    TARGET pacman
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:pacman>/assets
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)