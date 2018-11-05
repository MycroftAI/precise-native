cmake_minimum_required(VERSION 3.5.1)
project(precise)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INSTALL_PREFIX /usr/local)

include_directories(include)
include_directories(include/precise)

add_library(precise SHARED
        kissfft/kissfft.hh
        kissfft/kissfft
        kissfft/kiss_fft.c
        mfcc/Mfcc.cpp
        mfcc/Mfcc.h
        AudioManager.cpp
        AudioManager.hpp
        local_tensorflow.h
        fake_tensorflow.h
        FftCalc.cc
        FftCalc.hh
        ModelRunner.cc
        ModelRunner.hpp
        RealtimeProcessor.cpp
        RealtimeProcessor.hpp)

find_package(SDL2 REQUIRED)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(precise ${SDL2_LIBRARIES})
target_link_libraries(precise -larriz -lportaudio -lportaudiocpp)

add_executable(precise_demo precise.cc)
add_dependencies(precise_demo precise)
target_link_libraries(precise_demo precise)
