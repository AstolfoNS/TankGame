cmake_minimum_required(VERSION 3.29)
project(TankGame)

set(CMAKE_CXX_STANDARD 20)

include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
link_libraries(libeasyx.a)

add_executable(
        TankGame
        main.cpp
        GlobalVariable.cpp
        EasyX/include/easyx.h
        EasyX/include/graphics.h
        AllHeader/AllDefine.h
        AllHeader/PaintTool.h
        AllHeader/Window.h
        AllHeader/Graph.h
        AllHeader/Player.h
        AllHeader/RandFunction.h
        AllHeader/Tank.h
)

