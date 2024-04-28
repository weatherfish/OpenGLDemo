cmake_minimum_required(VERSION 3.10)

# Add your source files
file(GLOB WRAPER_SOURCE "*.cpp")

# Create a library named "wrapper"
add_library(wrapper ${WRAPER_SOURCE})
