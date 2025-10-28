cmake_minimum_required(VERSION 3.10.0)
project(RestaurantManagement VERSION 0.1.0 LANGUAGES C CXX)

add_executable(RestaurantManagement
    src/main.cpp
    src/Order.cpp
    src/NormalOrder.cpp
    src/VeganOrder.cpp
    src/VIPOrder.cpp
)

set_target_properties(RestaurantManagement PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(RestaurantManagement PRIVATE include)

# include(FetchContent)

# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        release-1.14.0 # Always use a specific tag or commit hash!
# )

# FetchContent_MakeAvailable(googletest)