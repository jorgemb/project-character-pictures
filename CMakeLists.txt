cmake_minimum_required(VERSION 3.15)
project(Project_CharacterPictures)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        include/
)

add_executable(CharacterPictures
        main.cpp
        src/Picture.cpp
        src/PictureBase.cpp
        include/picture/Picture.hpp
        include/picture/PictureBase.hpp
        )