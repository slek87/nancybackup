cmake_minimum_required(VERSION 3.12)
project(gridworld C)

set(CMAKE_C_STANDARD 99)

add_executable(gridworld main.c gridworld.h gridworld.c)