//
// Created by Astolfo on 24-11-15.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <functional>
#include "PaintTool.h"
#include "AllDefine.h"
#include "RandFunction.h"

extern PaintTool painter;

class Graph
{
private:
    int             width_;
    int             height;
    std::set<PII>   coordinateSet;

    void _create_border()
    {
        painter.paint_chunk_row_line({1, width_ - 1}, 1);
        painter.paint_chunk_row_line({1, width_ - 1}, height);
        painter.paint_chunk_col_line({1, height - 1}, 1);
        painter.paint_chunk_col_line({1, height - 1}, width_);

        painter.paint_block(PaintTool::chunk_to_block_coordinate({width_, height}));
    }
    void _create_maze(PII TLCoordinate, PII BRCoordinate)
    {
        if ((BRCoordinate.x - TLCoordinate.x + 1) * (BRCoordinate.y - TLCoordinate.y + 1) < 1) return;

        int chunkX = rand_range_int(TLCoordinate.x, BRCoordinate.x);
        int chunkY = rand_range_int(TLCoordinate.y, BRCoordinate.y);

        int TT = TLCoordinate.y - 1;
        int BT = chunkY - 1;

        int LL = TLCoordinate.x - 1;
        int RL = chunkX - 1;

        int RR = BRCoordinate.x;
        int LR = chunkX;

        int BB = BRCoordinate.y;
        int TB = chunkY;

        int massage[4][4] = {
            {TT, BT, chunkX, rand_range_int(TT, BT)},
            {LR, RR, chunkY, rand_range_int(LR, RR)},
            {TB, BB, chunkX, rand_range_int(TB, BB)},
            {LL, RL, chunkY, rand_range_int(LL, RL)},
        };

        for (int i = 0, randChoice = rand_range_int(0, 10); i <= 3; i++) {
            if (i == randChoice) {
                massage[i][3] = 0;
            } else {
                coordinateSet.insert(i & 1 ? std::make_pair(massage[i][3], massage[i][2]) : std::make_pair(massage[i][2], massage[i][3]));
            }
            painter.paint_chunk_line({massage[i][0], massage[i][1]}, massage[i][2], massage[i][3], i & 1);
        }

        _create_maze(TLCoordinate, {chunkX - 1, chunkY - 1});
        _create_maze({chunkX + 1, TLCoordinate.y}, {BRCoordinate.x, chunkY - 1});
        _create_maze({TLCoordinate.x, chunkY + 1}, {chunkX - 1, BRCoordinate.y});
        _create_maze({chunkX + 1, chunkY + 1}, BRCoordinate);
    }
    void _optimizing_maze()
    {
        for (PII chunkCoordinate : coordinateSet) {
            auto [blockX, blockY] = PaintTool::chunk_to_block_coordinate(chunkCoordinate);
            if (PaintTool::get_pixel_color(PaintTool::block_to_pixel_coordinate({blockX, blockY - 1})) == BARRIER_COLOR ||
                PaintTool::get_pixel_color(PaintTool::block_to_pixel_coordinate({blockX - 1, blockY})) == BARRIER_COLOR) painter.paint_block({blockX, blockY});
        }
    }

public:
    explicit Graph(int graphWidth_, int graphHeight) : width_(graphWidth_), height(graphHeight) {}

    void create_graph()
    {
        painter.reset_fillcolor(BARRIER_COLOR);

        _create_border();

        _create_maze({2, 2}, {width_ - 1, height - 1});

        _optimizing_maze();
    }

    ~Graph() = default;
};

#endif //GRAPH_H
