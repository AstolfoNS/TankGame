//
// Created by Astolfo on 24-11-15.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "Graph.h"
#include "AllDefine.h"
#include "../EasyX/include/graphics.h"

class Window
{
private:
    int     width_;
    int     height;
    Graph   maze;

public:
    explicit Window(int windowWidth_, int windowHeight) : width_(windowWidth_), height(windowHeight), maze(Graph(windowWidth_, windowHeight)) {
        initgraph(width_ * CHUNK_OF_PIXEL_SIZE + 1, height * CHUNK_OF_PIXEL_SIZE + 1);
        setbkcolor(BACKGROUND_COLOR);
        cleardevice();

        maze.create_graph();
    };


    ~Window() {
        closegraph();
    }
};

#endif //WINDOW_H
