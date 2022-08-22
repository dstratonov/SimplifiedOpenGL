#include "tgaimage.h"
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const int width  = 800;
const int height = 800;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color){
    bool sweep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)){
        std::swap(x0, y0);
        std::swap(x1, y1);
        sweep = true;
    }
    if (x0 > x1){
        std::swap(x1, x0);
        std::swap(y1, y0);
    }
    float dError = (y1 - y0)/float(x1 - x0);
    int y = y0;
    for (int x = x0; x < x1; x += 1){
        y = y0 + (x - x0) * dError;
        if (sweep) {
            image.set(y, x, color);
        }
        else{
            image.set(x, y, color);
        }
    }
}

int main(int argc, char** argv) {
    Model model("D:\\SimplifiedOpenGL\\SimplifiedOpenGL\\SimplifiedOpenGL\\obj\\african_head.obj");
    TGAImage image(width, height, TGAImage::RGB);
    for (int i = 0; i < model.nfaces(); i++){
        auto face = model.face(i);
        for (int j = 0; j < 3; j++){
            Vec3f v0 = model.vert(face[j]);
            Vec3f v1 = model.vert(face[(j + 1) % 3]);
            int x0 = (v0.x * 0.5 + 0.5) * width;
            int y0 = (v0.y * 0.5 + 0.5) * height;
            int x1 = (v1.x * 0.5 + 0.5 ) * width;
            int y1 = (v1.y * 0.5 + 0.5 ) * height;
            line(x0, y0, x1, y1, image, white);
        }
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    system("output.tga");
    return 0;
}