//
// Created by Carl Gombert on 2/12/25.
//
#ifndef RASTER_H
#define RASTER_H

#include "Model.h"
#include "tgaimage.h"
#include "geometry.h"

class Raster {
public:
    Raster();
    void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color);
    void draw_image(int width, int height, int xShift, int yShift, float angle, float scale, Model &model, TGAImage &image, Vec3f &light_dir, const std::string &outf);
    void draw_gif(int width, int height, int xShift, int yShift, int frames, float scale, Model &model, TGAImage &image, Vec3f &light_dir);
};

#endif //RASTER_H
