cmake_minimum_required(VERSION 3.15)

project(RestaurantManagement VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(RestaurantLogic
    src/Order.cpp
    src/NormalOrder.cpp
    src/VeganOrder.cpp
    src/VIPOrder.cpp
)

target_include_directories(RestaurantLogic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(RestaurantManagement
    src/main.cpp
)

target_link_libraries(RestaurantManagement
    PRIVATE
        RestaurantLogic
)

set_target_properties(RestaurantManagement PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
