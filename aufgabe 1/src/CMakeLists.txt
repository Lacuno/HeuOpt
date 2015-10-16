# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (HeuOpt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#target_include_directories (HeuOpt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../lib")
add_executable (heuopt_ex1 main.cpp kpmp_instance.cpp kpmp_solution_writer.cpp kpmp_solution.cpp)
#target_link_libraries (HeuOpt LINK_PUBLIC heuopt_ex1)UX_SOURCE_DIRECTORY
