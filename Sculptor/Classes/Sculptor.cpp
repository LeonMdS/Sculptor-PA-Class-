#pragma once

#include "SculptorClass.h"
#include "../Common Functions/Functions.cpp"
#include "../Common Functions/Matrix.cpp"

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    this->v = Matrix(_nx, _ny, _nz);
    this->nx = _nx;
    this->ny = _ny;
    this->nz = _nz;
};

Sculptor::~Sculptor(){
    delete[] v[0][0];
    delete[] v[0];
    delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float alpha){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = alpha;
};

void Sculptor::putVoxel(int x, int y, int z){
    (this->v)[x][y][z].isOn = true;
    (this->v)[x][y][z].r = this->r;
    (this->v)[x][y][z].g = this->g;
    (this->v)[x][y][z].b = this->b;
    (this->v)[x][y][z].a = this->a;
};

void Sculptor::cutVoxel(int x, int y, int z){
    (this->v)[x][y][z].isOn = false;
};

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    Box(x0, x1, y0, y1, z0, z1, true, this);
};

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    Box(x0, x1, y0, y1, z0, z1, false, this);
};

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    Ellipse(xcenter, ycenter, zcenter, radius, radius, radius, true, this);
};

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    Ellipse(xcenter, ycenter, zcenter, radius, radius, radius, false, this);
};

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    Ellipse(xcenter, ycenter, zcenter, rx, ry, rz, true, this);
};

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    Ellipse(xcenter, ycenter, zcenter, rx, ry, rz, false, this);
};

void Sculptor::writeOFF(string filename){
    std::ofstream outfile (filename);
    outfile << "OFF" << std::endl;
    int voxels = CountVoxels(this->nx, this->ny, this->nz, this->v);
    std::cout << "voxels counted with surround: " << voxels << std::endl;
    outfile << 8*voxels << " " << 6*voxels << " " << 0 << std::endl;

    GoThrough(this->nx, this->ny, this->nz, this, [&outfile, this](int x, int y, int z){
        Voxel voxel = (this->v)[x][y][z];
        if(voxel.isOn && notSurrounded(x, y, z, this->v, this->nx, this->ny, this->nz)){
            OutVertices(x, y, z, &outfile);
        }
    });

    size_t i = 0;
    GoThrough(this->nx, this->ny, this->nz, this, [&outfile, &i, this](int x, int y, int z){
        Voxel voxel = (this->v)[x][y][z];
        if(voxel.isOn && notSurrounded(x, y, z, this->v, this->nx, this->ny, this->nz)) {
            OutFaces(voxel, i, &outfile);
            i++;
        };
    });

    outfile.close();
};

void Sculptor::writeVECT(string filename){
    std::ofstream outfile (filename);
    outfile << "VECT" << std::endl;
    int voxels = CountVoxels(this->nx, this->ny, this->nz, this->v);
    outfile << voxels << " " << voxels << " " << voxels << std::endl;

    for(size_t i = 0; i < 2*voxels; i++){
        outfile << 1;
        if(i != (voxels - 1) && i != (2*voxels - 1)){ outfile << " "; }
        else { outfile << std::endl; }
    }

    GoThrough(this->nx, this->ny, this->nz, this, [&outfile, this](int x, int y, int z) { 
        Voxel voxel = (this->v)[x][y][z];
        if(voxel.isOn) { outfile << x << " " << y << " " << z << std::endl; }
    });

    GoThrough(this->nx, this->ny, this->nz, this, [&outfile, this](int x, int y, int z) { 
        Voxel voxel = (this->v)[x][y][z];
        if(voxel.isOn) { outfile << voxel.r << " " << voxel.g << " " << voxel.b << " " << voxel.a << std::endl; }
    });

    outfile.close();
};