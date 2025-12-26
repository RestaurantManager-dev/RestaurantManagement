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


# --- CMUgraphicsLib Library ---
file(GLOB CMU_SOURCES 
    "include/CMUgraphicsLib/*.cpp" 
    "include/CMUgraphicsLib/*.c"
    "include/CMUgraphicsLib/jpeg/*.c"
)
add_library(CMUgraphicsLib STATIC ${CMU_SOURCES})
target_include_directories(CMUgraphicsLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/CMUgraphicsLib
        ${CMAKE_CURRENT_SOURCE_DIR}/include/CMUgraphicsLib/jpeg
)
# CMUgraphicsLib uses Windows API (GDI, User32, WinMM)
target_link_libraries(CMUgraphicsLib
    PUBLIC
        gdi32
        user32
        winmm
)


# --- GUI Library ---
file(GLOB GUI_SOURCES "src/GUI/*.cpp")
add_library(GUI STATIC ${GUI_SOURCES})
target_include_directories(GUI
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(GUI
    PUBLIC
        CMUgraphicsLib
)



# --- RestaurantLogic Library ---

file(GLOB_RECURSE LOGIC_SOURCES
    CONFIGURE_DEPENDS
    "src/RestaurantLogic/*.cpp"
)

add_library(RestaurantLogic ${LOGIC_SOURCES})

target_include_directories(RestaurantLogic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(RestaurantLogic
    PRIVATE
        DataStructures
        GUI
)

# --- RestaurantApp Executable ---

file(GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    "src/RestaurantApp/*.cpp"
)

add_executable(RestaurantApp
    ${APP_SOURCES}
)

target_link_libraries(RestaurantApp
    PRIVATE
        RestaurantLogic
)


target_compile_definitions(RestaurantApp
    PRIVATE
        INPUT_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/RestaurantApp/input.txt"
)

# --- Set Binary Output Directories ---

set_target_properties(RestaurantApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties(RestaurantLogic PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)