# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( graypes_ )

cmake_minimum_required(VERSION 2.8.10)

set(CMAKE_CXX_STANDARD 14)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

     create_single_source_cgal_program( "graypes.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 