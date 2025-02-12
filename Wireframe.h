//
// Created by Carl Gombert on 2/12/25.
//

#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "Model.h"
#include "tgaimage.h"
#include "geometry.h"

class Wireframe {
public:
    Wireframe();
    static TGAColor white;
    void draw_gif(int width, int height, int xShift, int yShift, int frames, float scale, Model &model, TGAImage &image);
    void draw_image(int width, int height, int xShift, int yShift, float angle, float scale, Model &model, TGAImage &image, const std::string &outf);
private:
    void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor &color);

};

#endif //WIREFRAME_H
