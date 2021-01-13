list(APPEND EXTRA_INCLUDES ../include)
list(APPEND EXTRA_LIBS util stdc++fs)


file(GLOB APP_SOURCES bellman-ford.cpp floyd_warshall.cpp dijkstra.cpp kruskal.cpp prim.cpp)
foreach(sourcefile ${APP_SOURCES})
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    string(REPLACE ".cpp" "" exe ${filename})
    add_executable(${exe} ${filename})
    target_include_directories(${exe} PUBLIC ${EXTRA_INCLUDES})
    target_link_libraries(${exe} PUBLIC ${EXTRA_LIBS})
endforeach(sourcefile ${APP_SOURCES})