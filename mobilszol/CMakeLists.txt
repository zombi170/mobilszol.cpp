cmake_minimum_required(VERSION 3.22)
project(mobilszol)

set(CMAKE_CXX_STANDARD 11)

add_executable(mobilszol
        teszt_main.cpp
        memtrace.h
        memtrace.cpp
        string5.h
        string5.cpp
        dijcsomagok.h
        azonosithato.h
        ugyfel.h
        ugyfel.cpp
        forgalom.h
        forgalom.cpp
        lista.h
        lista.cpp
        gtest_lite.h)