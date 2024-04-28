cmake_minimum_required(VERSION 3.10)

# Add your source files
file(GLOB_RECURSE APP_SOURCE "*.cpp")

add_library(applicaiton ${APP_SOURCE})
