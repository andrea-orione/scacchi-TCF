cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 20)
project(Scacchi)

# include necessary files and directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/pieces)

# compile every source and header file in project directory
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB pieces_sources ${PROJECT_SOURCE_DIR}/src/pieces/*.cpp)
file(GLOB pieces_headers ${PROJECT_SOURCE_DIR}/include/pieces/*.hh)

# create executable and link it to Geant4 libraries
add_executable(scacchi main.cpp ${pieces_sources} ${pieces_headers} ${sources} ${headers})
