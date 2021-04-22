cmake_minimum_required(VERSION 2.1)

project(metaPrograming)


set(MAIN "main.cpp")


include_directories(
    template_list
    variant
    tools
    memory
)


add_definitions( -g )

add_executable(main ${MAIN})