cmake_minimum_required(VERSION 3.26)
project(chess_new)
include_directories(include/Easyx/include)
include_directories(include/nlohmann)
link_directories(include/Easyx/lib64)
link_libraries(libeasyx.a)
set(CMAKE_CXX_STANDARD 11)
include_directories(./headers)
#add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_executable(chess_new main.cpp
        #sources/openmenu.cpp
        sources/widget.cpp
        headers/widget.h
        sources/button.cpp
        headers/button.h
        sources/window.cpp
        headers/window.h
        headers/chess.h
        sources/chess.cpp
        sources/cheessai.cpp
        headers/chessai.h
        headers/data.h
        sources/data.cpp
        headers/table.h
        sources/table.cpp
        #sources/openmenu.cpp
)
