cmake_minimum_required(VERSION 3.28.3)
project(computing_at_scale CXX)

add_subdirectory(/home/kairvilodhiya/MANE6965/computing-at-scale-demo-2025/Demo_lecture4/mathlibrary)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC mathlibrary)