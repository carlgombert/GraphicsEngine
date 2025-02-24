#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v.raw[i];

            verts_.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            std::vector<int> ft;
            int itrash, idx, tidx;
            iss >> trash;
            while (iss >> idx) { // Read only vertex index
                idx--;
                f.push_back(idx);
                if (iss.peek() == '/') { // Check if texture/normal indices exist
                    iss.ignore();
                    if (iss.peek() != ' ') { // texture index if present
                        if (iss.peek() != '/') {
                            iss >> tidx;
                            tidx--;
                            ft.push_back(tidx);
                        } else {
                            iss >> itrash;
                        }
                    }
                    if (iss.peek() == '/') { // Skip normal index if present
                        iss.ignore();
                        iss >> itrash;
                    }
                }
            }
            faces_.push_back(f);
            face_textures_.push_back(ft);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash;
            Vec3f t = Vec3f();
            for (int i=0;i<3;i++) iss >> t.raw[i];

            textures_.push_back(t);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

int Model::ntextures() {
    return (int)textures_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

std::vector<int> Model::face_texture(int idx) {
    return face_textures_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

Vec3f Model::texture(int i) {
    return textures_[i];
}
