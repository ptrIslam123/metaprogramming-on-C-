cmake_minimum_required(VERSION 3.1)

project(metaPrograming)


set(MAIN "main.cpp")



include_directories(tools)

include_directories(
    template_list
    variant
    tools
    memory
)


add_definitions( -Wall -g )

add_executable(main ${MAIN})