file(GLOB LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(util ${LIB_SOURCES})
target_include_directories(util PUBLIC ../include)
