cmake_minimum_required (VERSION 3.2)
project (AMR)
include_directories(${CMAKE_SOURCE_DIR}/source/hpp)

add_executable(AMR
source/cpp/main.cpp
source/cpp/MortonHasher.cpp
)

install(TARGETS AMR DESTINATION ${CMAKE_SOURCE_DIR}/exe)
