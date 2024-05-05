cmake_minimum_required(VERSION 3.10)

# Add your source files
file(GLOB_RECURSE FW_SOURCE "*.cpp")

add_library(glFramework ${FW_SOURCE})
