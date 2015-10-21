# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (HeuOpt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
file(GLOB SOURCE_FILES "src/aufgabe1/*.h" "src/aufgabe1/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/framework)
	
add_executable (heuopt_ex1 ${SOURCE_FILES})