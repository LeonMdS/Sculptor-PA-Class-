#pragma once

#include "voxelclass.h"

//Simple function to create a voxel matrix on the heap
/**
 * @brief Matrix
 * @param X
 * @param Y
 * @param Z
 * @return
 */
Voxel*** Matrix(int X, int Y, int Z){
    Voxel ***A;
    A = new Voxel** [X];
    A[0] = new Voxel* [X*Y];
    A[0][0] = new Voxel [X*Y*Z];

    int check = 0;
    int i, j;
    for (i = 0; i < X; i++) {
        if (i < (X-1)) { A[i+1] = A[i] + Y; }

        for (j = 1; j < Y; j++) {
            if(check != i){
                A[i][0] = A[i-1][Y-1] + Z;
                check = i;
            }

            A[i][j] = A[i][j-1] + Z;
        }
        check = i;
    }
    return A;
}
