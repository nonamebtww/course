cmake_minimum_required(VERSION 3.16)
project(Course C)

add_executable(app
        #
        course/main.c

        #
        course/headers/functions.h
        course/src/functions.c

        course/headers/logging.h
        course/src/logging.c

        #
        course/headers/models.h
        course/headers/menu.h
        course/src/menu.c
)

target_include_directories(app
        PRIVATE
        course/headers
)