cmake_minimum_required(VERSION 3.16)
project(music_playlist_service_lab02 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab04
    src/audio_file.cpp
    src/track.cpp
    src/playlist.cpp
    src/base_user.cpp
    src/listener.cpp
    src/author.cpp
    src/main.cpp
)

target_include_directories(lab04 PRIVATE include)

if(MSVC)
    target_compile_options(lab04 PRIVATE /W4)
else()
    target_compile_options(lab04 PRIVATE -Wall -Wextra -Wpedantic)
endif()