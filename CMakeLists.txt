cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 20)
project(Scacchi)

# include necessary directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/movers)
include_directories(${PROJECT_SOURCE_DIR}/include/pieces)
include_directories(${PROJECT_SOURCE_DIR}/include/renderers)

# get all files to be compiled
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB movers_sources ${PROJECT_SOURCE_DIR}/src/movers/*.cpp)
file(GLOB movers_headers ${PROJECT_SOURCE_DIR}/include/movers/*.hh)
file(GLOB pieces_sources ${PROJECT_SOURCE_DIR}/src/pieces/*.cpp)
file(GLOB pieces_headers ${PROJECT_SOURCE_DIR}/include/pieces/*.hh)
file(GLOB renderers_sources ${PROJECT_SOURCE_DIR}/src/renderers/*.cpp)
file(GLOB renderers_headers ${PROJECT_SOURCE_DIR}/include/renderers/*.hh)

# create executable
add_executable(scacchi main.cpp ${renderers_sources} ${pieces_sources} ${movers_sources} ${sources})
