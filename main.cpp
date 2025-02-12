#include <iostream>
#include "Model.h"
#include "tgaimage.h"
#include "geometry.h"
#include "Raster.h"

int main(int argc, char** argv) {
    int width = 500;
    int height = 500;
    float scale = 4.0;
    int yShift = 0;
    int xShift = 0;
    int rotation = 0;
    float angle = 0;

    int count = 60;


    TGAImage image(width, height, TGAImage::RGB);
    Model model = Model("../res/input/golang_gopher.obj");
    Vec3f light_dir(0,0,-1);

    Raster raster = Raster();
    raster.draw_image(width, height, xShift, yShift, angle, scale, model, image, light_dir, "../res/output/output.tga");
    //raster.draw_gif(width, height, xShift, yShift, count, scale, model, image, light_dir);
    return 0;
}
