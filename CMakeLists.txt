cmake_minimum_required(VERSION 3.15)
project(Project_CharacterPictures)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        include/
)

add_executable(CharacterPictures
        main.cpp
        src/picture.cpp
        src/pic_base.cpp
        include/picture/picture.hpp
        include/picture/pic_base.hpp
        )