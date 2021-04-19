cmake_minimum_required(VERSION 2.1)

project(metaPrograming)

set(MAIN "main.cpp")

include_directories(
    template_list
)

add_executable(main ${MAIN})