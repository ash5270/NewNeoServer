cmake_minimum_required(VERSION 3.20)
project(NEOServer)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(NeoUtil)
add_subdirectory(NeoNetwork)
add_subdirectory(NeoGameBase)
add_subdirectory(NeoGameServer)

add_dependencies (NeoNetwork NeoUtil)
add_dependencies (NeoGameServer NeoNetwork NeoUtil)


target_link_libraries(NeoNetwork NeoUtil)
target_link_libraries(NeoGameServer NeoGameBase)
target_link_libraries(NeoGameServer NeoNetwork)
target_link_libraries(NeoGameServer NeoUtil)

target_link_libraries(NeoGameServer "${CMAKE_CURRENT_SOURCE_DIR}/Redis/lib/hiredis.lib")
target_link_libraries(NeoGameServer "${CMAKE_CURRENT_SOURCE_DIR}/Redis/lib/redis++.lib")

target_include_directories(NeoGameServer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Redis")

target_include_directories(NeoNetwork PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann")
target_include_directories(NeoGameServer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann")



