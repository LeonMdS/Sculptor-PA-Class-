#pragma once

#include "sculptorclass.h"
#include "functions.cpp"
#include "matrix.cpp"

//Constructor creates matrix of desired size, and saves that size into the nx, ny and nz parameters of the sculptor class
/**
 * @brief Sculptor::Sculptor
 * @param _nx
 * @param _ny
 * @param _nz
 */
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    this->v = Matrix(_nx, _ny, _nz);
    this->nx = _nx;
    this->ny = _ny;
    this->nz = _nz;
};

//Destructor frees the entire memory allocated to the voxels
/**
 * @brief Sculptor::~Sculptor
 */
Sculptor::~Sculptor(){
    delete[] v[0][0];
    delete[] v[0];
    delete[] v;
}

//Sets new color and transparency of the sculptor
/**
 * @brief Sculptor::setColor
 * @param r
 * @param g
 * @param b
 * @param alpha
 */
void Sculptor::setColor(float r, float g, float b, float alpha){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = alpha;
};

//Turns voxel on and sets its color and transparency to be the same as the current sculptor setup
/**
 * @brief Sculptor::putVoxel
 * @param x
 * @param y
 * @param z
 */
void Sculptor::putVoxel(int x, int y, int z){
    (this->v)[x][y][z].isOn = true;
    (this->v)[x][y][z].r = this->r;
    (this->v)[x][y][z].g = this->g;
    (this->v)[x][y][z].b = this->b;
    (this->v)[x][y][z].a = this->a;
};

//Turns voxel off
/**
 * @brief Sculptor::cutVoxel
 * @param x
 * @param y
 * @param z
 */
void Sculptor::cutVoxel(int x, int y, int z){
    (this->v)[x][y][z].isOn = false;
};

//The box funcion takes in the x, y and z limits, and activates voxels of a sculptor pointer if true, and deactivates them if false
/**
 * @brief Sculptor::putBox
 * @param x0
 * @param x1
 * @param y0
 * @param y1
 * @param z0
 * @param z1
 */
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    Box(x0, x1, y0, y1, z0, z1, true, this);
};
/**
 * @brief Sculptor::cutBox
 * @param x0
 * @param x1
 * @param y0
 * @param y1
 * @param z0
 * @param z1
 */
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    Box(x0, x1, y0, y1, z0, z1, false, this);
};


//The Ellipse funcion takes in the x, y and z centers, and, in the case of it being inside of the ellipse, it activates the
//voxels of a sculptor pointer if true, and deactivates them if false
/**
 * @brief Sculptor::putSphere
 * @param xcenter
 * @param ycenter
 * @param zcenter
 * @param radius
 */
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    Ellipse(xcenter, ycenter, zcenter, radius, radius, radius, true, this);
};
/**
 * @brief Sculptor::cutSphere
 * @param xcenter
 * @param ycenter
 * @param zcenter
 * @param radius
 */
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    Ellipse(xcenter, ycenter, zcenter, radius, radius, radius, false, this);
};
/**
 * @brief Sculptor::putEllipsoid
 * @param xcenter
 * @param ycenter
 * @param zcenter
 * @param rx
 * @param ry
 * @param rz
 */
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    Ellipse(xcenter, ycenter, zcenter, rx, ry, rz, true, this);
};
/**
 * @brief Sculptor::cutEllipsoid
 * @param xcenter
 * @param ycenter
 * @param zcenter
 * @param rx
 * @param ry
 * @param rz
 */
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    Ellipse(xcenter, ycenter, zcenter, rx, ry, rz, false, this);
};


//Function to write a file corresponding to the current voxel array, in the format of .off
/**
 * @brief Sculptor::writeOFF
 * @param filename
 */
void Sculptor::writeOFF(string filename){
    //Creates output file
    std::ofstream outfile (filename);

    //Determines how it should be interpreted
    outfile << "OFF" << std::endl;

    //Counts surface voxels and writes out the first line of information
    int voxels = CountVoxels(this->nx, this->ny, this->nz, this->v, false);
    outfile << 8*voxels << " " << 6*voxels << " " << 0 << std::endl;

    //Iterates through array and uses the lambda on each voxel
    //Reminder: the this keyword represents a pointer to the current sculptor this is activated on
    GoThrough(0, this->nx, 0, this->ny, 0, this->nz, [&outfile, this](int x, int y, int z){
        //Determines current voxel and if it is surrounded
        Voxel voxel = (this->v)[x][y][z];
        bool not_surrounded = notSurrounded(x, y, z, this->v, this->nx, this->ny, this->nz);

        //Outputs the information about the vertices of the voxel if it is both turned on
        //and not surrounded by other voxels
        if(voxel.isOn && not_surrounded){
            OutVertices(x, y, z, &outfile);
        }
    });

    //Counter to be used in the lambda function
    int i = 0;

    //Iterates through array and uses the lambda on each voxel, as it was done previously
    //Reminder: the this keyword represents a pointer to the current sculptor this is activated on
    GoThrough(0, this->nx, 0, this->ny, 0, this->nz, [&outfile, &i, this](int x, int y, int z){
        //Determines current voxel and if it is surrounded
        Voxel voxel = (this->v)[x][y][z];
        bool not_surrounded = notSurrounded(x, y, z, this->v, this->nx, this->ny, this->nz);

        //Output information about a face if the voxel is both on and not surrounded
        if(voxel.isOn && not_surrounded) {
            OutFaces(voxel, i, &outfile);
            i++;
        };
    });

    //Closes output file
    outfile.close();
};


//Function to write a file corresponding to the current voxel array, in the format of .vect
/**
 * @brief Sculptor::writeVECT
 * @param filename
 */
void Sculptor::writeVECT(string filename){
    //Creates output file
    std::ofstream outfile (filename);

    //Determines how it should be interpreted
    outfile << "VECT" << std::endl;

    //Counts voxels, including the ones surrounded by other voxels, and writes down the first lines of information
    int voxels = CountVoxels(this->nx, this->ny, this->nz, this->v, true);
    outfile << voxels << " " << voxels << " " << voxels << std::endl;
    for(int i = 0; i < 2*voxels; i++){
        outfile << 1;
        if(i != (voxels - 1) && i != (2*voxels - 1)){ outfile << " "; }
        else { outfile << std::endl; }
    }

    //Iterates through array and uses the lambda on each voxel
    //Reminder: the this keyword represents a pointer to the current sculptor this is activated on
    GoThrough(0, this->nx, 0, this->ny, 0, this->nz, [&outfile, this](int x, int y, int z) {
        //Determines current voxel
        Voxel voxel = (this->v)[x][y][z];

        //Outputs the voxel's position, if turned on
        if(voxel.isOn) { outfile << x << " " << y << " " << z << std::endl; }
    });

    //Iterates through array and uses the lambda on each voxel, as it was done previously
    //Reminder: the this keyword represents a pointer to the current sculptor this is activated on
    GoThrough(0, this->nx, 0, this->ny, 0, this->nz, [&outfile, this](int x, int y, int z) {
        //Determines current voxel
        Voxel voxel = (this->v)[x][y][z];

        //Outputs voxel's color and transparency, if turned on
        if(voxel.isOn) { outfile << voxel.r << " " << voxel.g << " " << voxel.b << " " << voxel.a << std::endl; }
    });

    //Closes output file
    outfile.close();
};
