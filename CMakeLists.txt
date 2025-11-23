cmake_minimum_required(VERSION 3.15)

project(RestaurantApp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- DataStructures Library (NEW) ---

add_library(DataStructures INTERFACE)

target_include_directories(DataStructures
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# --- RestaurantLogic Library ---

file(GLOB_RECURSE LOGIC_SOURCES
    CONFIGURE_DEPENDS
    "src/RestaurantLogic/*.cpp"
)

add_library(RestaurantLogic ${LOGIC_SOURCES} "src/RestaurantApp/Resturant.cpp" "include/RestaurantApp/Resturant.h")

target_include_directories(RestaurantLogic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(RestaurantLogic
    PRIVATE
        DataStructures
)

# --- RestaurantApp Executable ---

file(GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    "src/RestaurantApp/*.cpp"
)

add_executable(RestaurantApp
    ${APP_SOURCES}
 "src/RestaurantApp/Resturant.cpp" "include/RestaurantApp/Resturant.h")

target_link_libraries(RestaurantApp
    PRIVATE
        RestaurantLogic
)

# --- Set Binary Output Directories ---

set_target_properties(RestaurantApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties(RestaurantLogic PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)