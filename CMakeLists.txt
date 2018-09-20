cmake_minimum_required(VERSION 2.6)
PROJECT(SuperPixels)

set (CMAKE_CXX_STANDARD 14)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

#not now
#find_package(VTK REQUIRED)
#include(${VTK_USE_FILE})

include_directories("src/")

add_executable(SuperPixels "src/SuperPixels.cpp")

target_link_libraries(SuperPixels  ${ITK_LIBRARIES} )#  ${VTK_LIBRARIES})


