#pragma once

#include "../Classes/SculptorClass.h"
#include <fstream>

//Checks if the point (x,y,z) is within the matrix, to not cause segmentation faults
bool validPoint(int x, int y, int z, int maxx, int maxy, int maxz){
    if(x < 0 || x >= maxx ||y < 0 ||y >= maxy ||z < 0 ||z >= maxz) {return false;}

    return true;
};

//Iterates through array on a given interval and executes given function
template<typename Func>
void GoThrough(int x0, int x1, int y0, int y1, int z0, int z1, Func use){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k < z1; k++){
                use(i, j, k);
            }
        }
    }
};

//Box function uses the GoThrough to iterate though the desired intervals and turn the voxels on or off, depending on the given bool put
void Box(int x0, int x1, int y0, int y1, int z0, int z1, bool put, Sculptor *sclptr){

    //Iterates through the given interval, and utilizes of a lambda function
    GoThrough(x0, x1 + 1, y0, y1 + 1, z0, z1 + 1, [&](int x, int y, int z){
        if(put) { sclptr->putVoxel(x, y, z); }
        else { sclptr->cutVoxel(x, y, z); }
    });
};

//Ellipse function uses the GoThrough to iterate though the desired intervals and turn the voxels on or off depending on the given bool put
void Ellipse(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz, bool put, Sculptor* sclptr){

    //Creates the cubic interval that includes the ellipse, which will be used in the GoThrough function
    int x0 = xcenter - rx;
    int x1 = xcenter + rx;
    int y0 = ycenter - ry;
    int y1 = ycenter + ry;
    int z0 = zcenter - rz;
    int z1 = zcenter + rz;

    //Determines the radius squared of x, y and z to be used inside the function
    double radius_sqrd_x = rx*rx, radius_sqrd_y = ry*ry, radius_sqrd_z = rz*rz;

    //Variables to be used inside the lambda function
    int dist_sqrd_x, dist_sqrd_y, dist_sqrd_z;
    double contribution_x, contribution_y, contribution_z, sum_of_contributions;

    //Iterates through the interval and uses the ellipse formula to decide if the point is in the ellipse or not
    GoThrough(x0, x1, y0, y1, z0, z1, [&](int x, int y, int z){
        
        //Calculates distance from the center squared for each axis
        dist_sqrd_x = (x - xcenter) * (x - xcenter);
        dist_sqrd_y = (y - ycenter) * (y - ycenter);
        dist_sqrd_z = (z - zcenter) * (z - zcenter);

        //Calculates the contribution of each axis to the sum
        contribution_x = dist_sqrd_x/radius_sqrd_x;
        contribution_y = dist_sqrd_y/radius_sqrd_y;
        contribution_z = dist_sqrd_z/radius_sqrd_z;

        //Calculates the sum of all contributions
        sum_of_contributions = contribution_x + contribution_y + contribution_z;

        //Acts if the point is included in the ellipse or not
        if( sum_of_contributions <= 1 ){
            if(put) { sclptr->putVoxel(x, y, z); }
            else { sclptr->cutVoxel(x, y, z); }
        }
    });
};

//Function to check if a given point is surrounded or not, also using the maximum values of the array to validate each point, to avoid segmentation faults
bool notSurrounded(int x, int y, int z, Voxel ***voxels, int nx, int ny, int nz){

    //For loop will have i being -1 and 1
    for(int i = -1; i < 2; i += 2){

        //Checks validity of the point, to avoid problems
        if(validPoint(x + i, y + i, z + i, nx, ny, nz)){

            //Returns true if any space around the voxel, not including diagonals, is not turned on
            if(!(voxels[x+i][y][z].isOn) || !(voxels[x][y+i][z].isOn)|| !(voxels[x][y][z+i].isOn)){ 
                return true; 
            }
        }
    }

    //Returns false if all the points around it, not including diagonals, were turned on
    return false;
}

//Function to count the number of voxels turned on inside an array, counting the surrounded ones only if include_surrounded is true
int CountVoxels(int nx, int ny, int nz, Voxel*** voxels, bool include_surrounded){
    //Counter to track the number of voxels
    int count = 0;

    GoThrough(0, nx, 0, ny, 0, nz, [&](int x, int y, int z){
        //Creates variables to hold the information of whether the voxel is on and if it is surrounded or not
        bool voxel_on = voxels[x][y][z].isOn;
        bool not_surrounded = notSurrounded(x, y, z, voxels, nx, ny, nz);

        //If statement only activates if the voxel is on and not surrounded, but if include_surrounded is true, then it only needs the voxel to be on
        if(voxel_on && (not_surrounded || include_surrounded)) { count++;}
    });

    return count;
};

//Two simple functions to write out to the output in template format
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