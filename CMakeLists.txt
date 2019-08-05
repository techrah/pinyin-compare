cmake_minimum_required(VERSION 3.12.2)
project (pinyin-compare)
set(CMAKE_BUILD_TYPE Release)
enable_testing()

link_directories($ENV{LD_LIBRARY_PATH})

add_subdirectory(src)
add_subdirectory(tests)
