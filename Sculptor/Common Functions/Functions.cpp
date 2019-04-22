#pragma once

#include "../Classes/VoxelClass.h"
#include "../Classes/SculptorClass.h"
#include <functional>

#ifndef _FSTR
#define _FSTR
#include <fstream>
#endif

bool validPoint(int x, int y, int z, int minx, int maxx, int miny, int maxy, int minz, int maxz){
    if(x < minx || x >= maxx ||y < miny ||y >= maxy ||z < minz ||z >= maxz) {return false;}

    return true;
}

void Box(int x0, int x1, int y0, int y1, int z0, int z1, bool put, Sculptor *sclptr){
    for(int i = x0; i < x1+1; i++){
        for(int j = y0; j < y1+1; j++){
            for(int k = z0; k < z1+1; k++){
                if(put) { sclptr->putVoxel(i, j, k); }
                else { sclptr->cutVoxel(i, j, k); }
            }
        }
    }
};

void Ellipse(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz, bool put, Sculptor *sclptr){
    int x0 = xcenter - rx;
    int x1 = xcenter + rx;
    int y0 = ycenter - ry;
    int y1 = ycenter + ry;
    int z0 = zcenter - rz;
    int z1 = zcenter + rz;

    int dist_sqrd_x, dist_sqrd_y, dist_sqrd_z;
    double radius_sqrd_x = rx*rx, radius_sqrd_y = ry*ry, radius_sqrd_z = rz*rz;
    double s1, s2, s3;

    for(int i = x0; i < x1+1; i++){
        for(int j = y0; j < y1+1; j++){
            for(int k = z0; k < z1+1; k++){
                dist_sqrd_x = (i - xcenter) * (i - xcenter);
                dist_sqrd_y = (j - ycenter) * (j - ycenter);
                dist_sqrd_z = (k - zcenter) * (k - zcenter);

                s1 = dist_sqrd_x/radius_sqrd_x;
                s2 = dist_sqrd_y/radius_sqrd_y;
                s3 = dist_sqrd_z/radius_sqrd_z;

                if( s1 + s2 + s3 <= 1 ){
                    if(put) { sclptr->putVoxel(i, j, k); }
                    else { sclptr->cutVoxel(i, j, k); }
                }
            }
        }
    }
};

bool notSurrounded(int x, int y, int z, Voxel ***voxels, int nx, int ny, int nz){
    for(int i = -1; i < 2; i += 2){
        if(validPoint(x + i, y + i, z + i, 0, nx, 0, ny, 0, nz)){
            //std::cout << "validated " << x + i << ", " << y + j << ", " << z + k << std::endl;
            if(!(voxels[x+i][y][z].isOn) || !(voxels[x][y+i][z].isOn)|| !(voxels[x][y][z+i].isOn)){ 
                return true; 
            }
        }
    }
    return false;
}

int CountVoxels(int nx, int ny, int nz, Voxel*** voxels){
    int count = 0;

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if(voxels[i][j][k].isOn && notSurrounded(i, j, k, voxels, nx, ny, nz)) { count++;}
            }
        }
    }

    return count;
};

void GoThrough(int nx, int ny, int nz, Sculptor *sclptr, std::function<void (int, int, int)> use){
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                use(i, j, k);
            }
        }
    }
};

void OutVertices(int x, int y, int z, std::ofstream* outfile){
    *outfile << x - 0.5 << " " << y + 0.5 << " " << z - 0.5 << std::endl;
    *outfile << x - 0.5 << " " << y - 0.5 << " " << z - 0.5 << std::endl;
    *outfile << x + 0.5 << " " << y - 0.5 << " " << z - 0.5 << std::endl;
    *outfile << x + 0.5 << " " << y + 0.5 << " " << z - 0.5 << std::endl;
    *outfile << x - 0.5 << " " << y + 0.5 << " " << z + 0.5 << std::endl;
    *outfile << x - 0.5 << " " << y - 0.5 << " " << z + 0.5 << std::endl;
    *outfile << x + 0.5 << " " << y - 0.5 << " " << z + 0.5 << std::endl;
    *outfile << x + 0.5 << " " << y + 0.5 << " " << z + 0.5 << std::endl;
};

void OutFaces(Voxel voxel, int i, std::ofstream* outfile){
    *outfile << 4 << " " << 0 + 8*i << " " << 3 + 8*i << " " << 2 + 8*i << " " << 1 + 8*i << " " << voxel.r << " " << voxel.g << " " << voxel.b << " " << voxel.a << " " << std::endl;
    *outfile << 4 << " " << 4 + 8*i << " " << 5 + 8*i << " " << 6 + 8*i << " " << 7 + 8*i << " " << voxel.r << " " << voxel.g << " " << voxel.b << " " << voxel.a << " " << std::endl;
    *outfile << 4 << " " << 0 + 8*i << " " << 1 + 8*i << " " << 5 + 8*i << " " << 4 + 8*i << " " << voxel.r << " " << voxel.g << " " << voxel.b << " " << voxel.a << " " << std::endl;
    *outfile << 4 << " " << 0 + 8*i << " " << 4 + 8*i << " " << 7 + 8*i << " " << 3 + 8*i << " " << voxel.r << " " << voxel.g << " " << voxel.b << " " << voxel.a << " " << std::endl;
    *outfile << 4 << " " << 3 + 8*i << " " << 7 + 8*i << " " << 6 + 8*i << " " << 2 + 8*i << " " << voxel.r << " " << voxel.g << " " << voxel.b << " " << voxel.a << " " << std::endl;
    *outfile << 4 << " " << 1 + 8*i << " " << 2 + 8*i << " " << 6 + 8*i << " " << 5 + 8*i << " " << voxel.r << " " << voxel.g << " " << voxel.b << " " << voxel.a << " " << std::endl;
};