cmake_minimum_required(VERSION 3.3)

project(TicTacToe VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

if (WIN32)
    set(SFML_DIR "C:/SFML/2.5.1/lib/cmake/SFML")
    file(COPY "C:/SFML/2.5.1/bin/" DESTINATION ${CMAKE_BINARY_DIR})
ELSE()
    set(SFML_DIR "/usr/local/Cellar/sfml/2.5.1/lib/cmake/SFML")
ENDIF()

file(COPY "resources" DESTINATION ${CMAKE_BINARY_DIR})

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

file(GLOB source_files "src/*.cpp")

include_directories(include)

add_executable(${PROJECT_NAME} ${source_files} "resources/resources.rc")

target_link_libraries("${PROJECT_NAME}" sfml-graphics sfml-window)
