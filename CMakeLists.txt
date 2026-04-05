cmake_minimum_required(VERSION 4.1)
project(PFE_PROJECT_WILLT C)

set(CMAKE_C_STANDARD 99)

add_executable(powerQualityAnalyser main.c
        waveform.h
        waveform.c
        io.c
        io.h)

add_executable(testing_run
        testing.c
        io.c)
