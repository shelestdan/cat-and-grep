cmake_minimum_required(VERSION 3.21)
project(cat_and_grep C)

set(CMAKE_C_STANDARD 11)

include_directories(src/cat)

add_executable(cat_and_grep
        src/cat/s21_cat.c
        src/cat/s21_cat.h)
