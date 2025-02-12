//
// Created by Carl Gombert on 2/12/25.
//

#include "Wireframe.h"
#include "Model.h"
#include "tgaimage.h"
#include "geometry.h"

TGAColor Wireframe::white = TGAColor(255, 255, 255, 255);

Wireframe::Wireframe() {}

void Wireframe::line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor &color) {
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
        }
    }
}

void Wireframe::draw_image(int width, int height, int xShift, int yShift, float angle, float scale, Model &model, TGAImage &image, const std::string &outf) {
    for (int i=0; i<model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        for (int j=0; j<3; j++) {
            Vec3 v0 = model.vert(face[j]);
            Vec3 v1 = model.vert(face[(j+1)%3]);

            v0.x = v0.x*cos(angle) + v0.z*sin(angle);
            v0.z= -v0.x*sin(angle) + v0.z*cos(angle);

            v1.x = v1.x*cos(angle) + v1.z*sin(angle);
            v1.z = -v1.x*sin(angle) + v1.z*cos(angle);

            int x0 = (v0.raw[0]+1.)*width/scale + xShift;
            int y0 = (v0.raw[1]+1.)*height/scale + yShift;
            int x1 = (v1.raw[0]+1.)*width/scale + xShift;
            int y1 = (v1.raw[1]+1.)*height/scale + yShift;
            line(x0, y0, x1, y1, image, white);
        }
    }

    image.flip_vertically();

    image.write_tga_file(outf.c_str()); //"../res/output/output.tga"
}

void Wireframe::draw_gif(int width, int height, int xShift, int yShift, int frames, float scale, Model &model, TGAImage &image) {
    float angle = 0.0;

    for (int n = 0; n < frames; n++) {
        draw_image(width, height, xShift, yShift, angle, scale, model, image, "../res/output/" + std::to_string(n) + ".tga");

        image.clear();

        angle = angle + 2*3.1415926535897932/frames;
    }
}