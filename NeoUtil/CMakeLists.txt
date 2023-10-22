file(GLOB_RECURSE SRC "*.cpp" "*.h")
add_library(NeoUtil STATIC ${SRC})

target_include_directories(NeoUtil PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")