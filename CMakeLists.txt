cmake_minimum_required(VERSION 3.10)
project(project2 C)

set(CMAKE_C_STANDARD 99)

add_executable(project2 wordcount.c htab.h htab_structures.h htab_memory.c htab_iterators.c htab_getset.c htab_hash.c io.c io.h)