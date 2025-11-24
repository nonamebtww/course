cmake_minimum_required(VERSION 3.16)
project(Course C)

add_executable(app
        # Sources
        course/main.c
        course/functions.c

        # Headers
        course/functions.h
)

target_include_directories(app
        PRIVATE
        course
)