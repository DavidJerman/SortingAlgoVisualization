cmake_minimum_required(VERSION 3.24)
project(SortingAlgorithmsVisualization)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        olcPixelGameEngine.h
        Constants.h
        Sorter.h)

set(SOURCE_FILES
        main.cpp
        Sorter.cpp)

# Set linker libraries for Windows
set(LINKER_LIBRARIES_WINDOWS
        user32
        gdi32
        opengl32
        gdiplus
        Shlwapi
        dwmapi
        )

# Set linker libraries for Linux
set(LINKER_LIBRARIES_LINUX
        X11
        GL
        pthread
        png
        stdc++fs)

if(WIN32)
    add_executable(GameOfLife ${SOURCE_FILES} ${HEADER_FILES})
    target_link_libraries(GameOfLife ${LINKER_LIBRARIES_WINDOWS})
elseif(UNIX)
    add_executable(GameOfLife ${SOURCE_FILES} ${HEADER_FILES})
    target_link_libraries(GameOfLife ${LINKER_LIBRARIES_LINUX})
endif()
