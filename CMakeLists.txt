# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (HeuOpt)

# Boost
find_package(Boost COMPONENTS program_options system filesystem REQUIRED)

file(COPY "instances/" DESTINATION "instances/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
file(GLOB SOURCE_FILES "src/aufgabe1/*.h" 
					   "src/aufgabe1/*.cpp" 
					   "${CMAKE_SOURCE_DIR}/framework/*.cpp" 
					   "${CMAKE_SOURCE_DIR}/framework/*.h")
set(EX1_SOURCE ${SOURCE_FILES})
list(REMOVE_ITEM EX1_SOURCE "${CMAKE_SOURCE_DIR}/src/aufgabe1/main.cpp")

file(GLOB SOURCE_FILES2 "src/aufgabe2/*.h"
		   "src/aufgabe2/*.cpp")
set(EX2_SOURCE ${SOURCE_FILES2})
list(REMOVE_ITEM EX2_SOURCE "${CMAKE_SOURCE_DIR}/src/aufgabe2/main.cpp")



include_directories(${CMAKE_SOURCE_DIR}/src/aufgabe1
		    ${CMAKE_SOURCE_DIR}/framework 
	            ${Boost_INCLUDE_DIRS}
		   )
add_executable (heuopt_ex1 ${EX1_SOURCE} "${CMAKE_SOURCE_DIR}/src/aufgabe1/main.cpp")
add_executable (heuopt_ex2 ${EX1_SOURCE} ${EX2_SOURCE} "${CMAKE_SOURCE_DIR}/src/aufgabe2/main.cpp")
target_link_libraries(heuopt_ex1 ${Boost_LIBRARIES})
target_link_libraries(heuopt_ex2 ${Boost_LIBRARIES})
