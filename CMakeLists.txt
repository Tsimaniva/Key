cmake_minimum_required(VERSION 3.29)
project(Bird)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bird main.cpp
        classes/Bird.cpp
        classes/Bird.h
        classes/Pipe.cpp
        classes/Pipe.h
        classes/Food.cpp
        classes/Food.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include/SFML)
link_directories(C:/SFML/lib)

target_link_libraries(Bird sfml-system sfml-window sfml-graphics sfml-audio)

