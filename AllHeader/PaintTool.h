//
// Created by Astolfo on 24-11-15.
//

#ifndef PRINTTOOL_H
#define PRINTTOOL_H

#include "AllDefine.h"
#include "../EasyX/include/graphics.h"


class PaintTool
{
private:
    COL color = BACKGROUND_COLOR;

    void _paint_block(PII blockCoordinate)
    {
        auto [pixelX, pixelY] = block_to_pixel_coordinate(blockCoordinate);

        solidrectangle(pixelX, pixelY, pixelX + BLOCK_OF_PIXEL_SIZE - 1, pixelY + BLOCK_OF_PIXEL_SIZE - 1);
    }
    void _paint_chunk_row(PII chunkCoordinate)
    {
        auto [blockX, blockY] = chunk_to_block_coordinate(chunkCoordinate);

        for (int i = 0; i < CHUNK_OF_BLOCK_SIZE; i++) _paint_block({blockX + i, blockY});
    }
    void _paint_chunk_col(PII chunkCoordinate)
    {
        auto [blockX, blockY] = chunk_to_block_coordinate(chunkCoordinate);

        for (int i = 0; i < CHUNK_OF_BLOCK_SIZE; i++) _paint_block({blockX, blockY + i});
    }
    void _paint_chunk_row_line(PII LR, int chunkY, int randMid = 0)
    {
        if (LR.fi > LR.se) return;
        if (randMid == 0) {
            for (int i = LR.fi; i <= LR.se; i++) _paint_chunk_row({i, chunkY});
        } else {
            _paint_chunk_row_line({LR.fi, randMid - 1}, chunkY);
            _paint_chunk_row_line({randMid + 1, LR.se}, chunkY);
        }
    }
    void _paint_chunk_col_line(PII TB, int chunkX, int randMid = 0)
    {
        if (TB.fi > TB.se) return;
        if (randMid == 0) {
            for (int i = TB.fi; i <= TB.se; i++) _paint_chunk_col({chunkX, i});
        } else {
            _paint_chunk_col_line({TB.fi, randMid - 1}, chunkX);
            _paint_chunk_col_line({randMid + 1, TB.se}, chunkX);
        }
    }
    void _reset_fillcolor(COL paintColor)
    {
        this->color = paintColor;
        setfillcolor(paintColor);
    }

public:
    void reset_fillcolor(COL paintColor) { _reset_fillcolor(paintColor); }

    static PII chunk_to_block_coordinate(PII chunkCoordinate) { return {(chunkCoordinate.x - 1) * CHUNK_OF_BLOCK_SIZE + 1, (chunkCoordinate.y - 1) * CHUNK_OF_BLOCK_SIZE + 1}; }

    static PII block_to_pixel_coordinate(PII blockCoordinate) { return {(blockCoordinate.x - 1) * BLOCK_OF_PIXEL_SIZE + 1, (blockCoordinate.y - 1) * BLOCK_OF_PIXEL_SIZE + 1}; }

    static PII chunk_to_pixel_coordinate(PII chunkCoordinate) { return block_to_pixel_coordinate(chunk_to_block_coordinate(chunkCoordinate)); }

    static COL get_pixel_color(PII pixelCoordinate) { return getpixel(pixelCoordinate.x, pixelCoordinate.y); }

    void paint_block(PII blockCoordinate) { _paint_block(blockCoordinate); }

    void paint_chunk_row(PII chunkCoordinate) { _paint_chunk_row(chunkCoordinate); }

    void paint_chunk_col(PII chunkCoordinate) { _paint_chunk_col(chunkCoordinate); }

    void paint_chunk_row_line(PII LR, int chunkY, int randMid = 0) { _paint_chunk_row_line(LR, chunkY, randMid); };

    void paint_chunk_col_line(PII TB, int chunkX, int randMid = 0) { _paint_chunk_col_line(TB, chunkX, randMid); };

    void paint_chunk_line(PII range, int standard, int randMid, int colOrRow)
    {
        if (colOrRow) {
            paint_chunk_row_line(range, standard, randMid);
        } else {
            paint_chunk_col_line(range, standard, randMid);
        }
    }

    ~PaintTool() = default;
};

#endif //PRINTTOOL_H
