cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 20)
project(Battaglia)

# include necessary files and directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# compile every source and header file in project directory
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# create executable and link it to Geant4 libraries
add_executable(battaglia main.cpp ${sources} ${headers})