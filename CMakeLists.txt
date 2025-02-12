cmake_minimum_required(VERSION 3.29)
project(C__Engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(C__Engine main.cpp
        Model.cpp
        Model.h
        tgaimage.cpp
        tgaimage.h
        geometry.h
        Wireframe.cpp
        Wireframe.h
        Raster.cpp
        Raster.h
)
