cmake_minimum_required(VERSION 3.26)
project(chess_new)
include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
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
        #sources/openmenu.cpp
)
