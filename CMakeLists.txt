cmake_minimum_required(VERSION 3.23)
project(UntitledEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE OFF)

include_directories(/usr/local/include)
include_directories(external/glm)
include_directories(external/imgui)
include_directories(/usr/local/rttr/include)

aux_source_directory("external/imgui" SRCS)
aux_source_directory("src" SRCS)
aux_source_directory("src/Components" SRCS)
aux_source_directory("src/Editors" SRCS)
aux_source_directory("external" SRCS)
aux_source_directory("external/glad" SRCS)
aux_source_directory("external/KHR" SRCS)

link_directories(/usr/local/rttr/lib)

add_library(jsoncpp SHARED IMPORTED)
set_target_properties(jsoncpp PROPERTIES
        IMPORTED_LOCATION "/usr/local/lib/libjsoncpp.dylib"
        INTERFACE_INCLUDE_DIRECTORIES "/usr/local/include/json"
        )

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wformat")
find_package(assimp REQUIRED)
link_directories(/usr/local/Cellar/glfw/3.3.2/lib)
add_executable(UntitledEngine ${SRCS} ${HDRS} PublicItem.h)

target_link_libraries(UntitledEngine GLFW assimp::assimp jsoncpp librttr_core_d.dylib)
