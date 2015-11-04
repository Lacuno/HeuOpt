# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (HeuOpt)

# Boost
find_package(Boost COMPONENTS program_options REQUIRED)

file(COPY "instances/" DESTINATION "instances/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
file(GLOB SOURCE_FILES "src/aufgabe1/*.h" 
					   "src/aufgabe1/*.cpp" 
					   "${CMAKE_SOURCE_DIR}/framework/*.cpp" 
					   "${CMAKE_SOURCE_DIR}/framework/*.h")

include_directories(${CMAKE_SOURCE_DIR}/framework
					${Boost_INCLUDE_DIRS})
	
add_executable (heuopt_ex1 ${SOURCE_FILES})
target_link_libraries(heuopt_ex1 ${Boost_LIBRARIES})