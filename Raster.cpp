//
// Created by Carl Gombert on 2/12/25.
//
#include <iostream>
#include "Model.h"
#include "Raster.h"
#include "tgaimage.h"
#include "geometry.h"

Raster::Raster(){}

void Raster::triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
    if (t0.y==t1.y && t0.y==t2.y) return;
    if (t0.y>t1.y) std::swap(t0, t1);
    if (t0.y>t2.y) std::swap(t0, t2);
    if (t1.y>t2.y) std::swap(t1, t2);
    int total_height = t2.y-t0.y;
    for (int i=0; i<total_height; i++) {
        bool second_half = i>t1.y-t0.y || t1.y==t0.y;
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here
        Vec2i A =               t0 + (t2-t0)*alpha;
        Vec2i B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta;
        if (A.x>B.x) std::swap(A, B);
        for (int j=A.x; j<=B.x; j++) {
            image.set(j, t0.y+i, color); // attention, due to int casts t0.y+i != A.y
        }
    }
}

void Raster::draw_image(int width, int height, int xShift, int yShift, float angle, float scale, Model &model, TGAImage &image, Vec3f &light_dir, const std::string &outf) {
    for (int i=0; i<model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f v = model.vert(face[j]);

            v.x = v.x*cos(angle) + v.z*sin(angle);
            v.z= -v.x*sin(angle) + v.z*cos(angle);

            screen_coords[j] = Vec2i((v.x+1.)*width/scale + xShift, (v.y+1.)*height/scale + yShift);
            world_coords[j]  = v;
        }
        Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
        n.normalize();
        float intensity = n*light_dir;
        if (intensity>0) {
            triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
        }
    }

    image.flip_vertically();
    image.write_tga_file(outf.c_str());
}

void Raster::draw_gif(int width, int height, int xShift, int yShift, int frames, float scale, Model &model, TGAImage &image, Vec3f &light_dir) {
    float angle = 0.0;

    for (int n = 0; n < frames; n++) {
        draw_image(width, height, xShift, yShift, angle, scale, model, image, light_dir, "../res/output/" + std::to_string(n) + ".tga");

        image.clear();

        angle = angle + 2.0*3.1415926535897932/frames;
    }
}

