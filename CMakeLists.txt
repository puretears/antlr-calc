cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS "-std=c++1z -Werror -Wall -DDEBUG")
set(ANTLR_BINARY_LIB /usr/local/lib)
set(ANTLR_INCLUDE_LIB /usr/local/include/antlr4-runtime)
set(ANTLR4 java -jar /usr/local/lib/antlr-4.7.1-complete.jar)

project(Calculation)

# Specify include and link path
link_directories(${ANTLR_BINARY_LIB})

# set(SOURCES ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/MyVisitor.cpp)
set(SOURCES ${PROJECT_SOURCE_DIR}/main.cpp)

include_directories(
  ${ANTLR_INCLUDE_LIB}
  ${ANTLR_INCLUDE_LIB}/misc
  ${ANTLR_INCLUDE_LIB}/atn
  ${ANTLR_INCLUDE_LIB}/dfa
  ${ANTLR_INCLUDE_LIB}/tree
  ${ANTLR_INCLUDE_LIB}/support
  ${PROJECT_SOURCE_DIR}/antlr4-runtime-cpp
)

# Mark these file as GENERATED to bypass the file existence checking.
set(CALCULATION_GENERATED_SRC
  ${PROJECT_SOURCE_DIR}/antlr4-runtime-cpp/CalculationLexer.cpp
  ${PROJECT_SOURCE_DIR}/antlr4-runtime-cpp/CalculationParser.cpp
)

foreach(src_file ${CALCULATION_GENERATED_SRC})
set_source_files_properties(${src_file}
  PROPERTIES
  GENERATED TRUE
)
endforeach()

# Download and build the Antlr4 cpp runtime library
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add(Antlr4-Cpp
  GIT_REPOSITORY https://github.com/antlr/antlr4.git
  SOURCE_DIR antlr4-Cpp
  SOURCE_SUBDIR runtime/Cpp
)

add_executable(calc ${SOURCES} ${CALCULATION_GENERATED_SRC})

if(APPLE)
target_link_libraries(calc ${ANTLR_BINARY_LIB}/libantlr4-runtime.dylib)
elseif(UNIX)
target_link_libraries(calc ${ANTLR_BINARY_LIB}/libantlr4-runtime.so)
endif()

# Generate antlr4 files
if (NOT EXISTS ${PROJECT_SOURCE_DIR}/antlr4-runtime-cpp)
message("-----------------------")
add_custom_target(antlr4-runtime-cpp ALL
  COMMAND ${ANTLR4} -Dlanguage=Cpp -o ${PROJECT_SOURCE_DIR}/antlr4-runtime-cpp ${PROJECT_SOURCE_DIR}/Calculation.g4
  VERBATIM
)
endif ()

install(TARGETS calc DESTINATION debug)

