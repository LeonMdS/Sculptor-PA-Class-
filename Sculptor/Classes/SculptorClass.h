#pragma once

#include "VoxelClass.h"
#include <string>

using std::string;

class Sculptor {
protected:
  //! Pointer to the voxel array.
  Voxel ***v;    // 3D matrix
  //! Array size in the X axis.
  int nx;
  //! Array size in the Y axis.
  int ny;
  //! Array size in the Z axis.
  int nz;
  //! Red component of the Sculptor's color.
  float r;
  //! Green component of the Sculptor's color.
  float g;
  //! Blue component of the Sculptor's color.
  float b;
  //! Transparency component of the Sculptor's color.
  float a;
public:
  //! Class Constructor that dynamically allocates a voxel matrix with specified sizes.
  Sculptor(int _nx, int _ny, int _nz);
  //! Class Destructor.
  ~Sculptor();
  //! Sets new color to the sculptor.
  void setColor(float r, float g, float b, float alpha);
  //! Inputs a voxel on speficied position, with parameters based on the Sculptor's.
  void putVoxel(int x, int y, int z);
  //! Removes a voxel from specified position.
  void cutVoxel(int x, int y, int z);
  //! Creates a box on given position, with given sizes.
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  //! Removes voxels in a box shape on given position with given sizes.
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  //! Creates a sphere on given position with given radius.
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  //! Removes voxels in a spherical shape on given position with given radius.
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  //! Creates an ellipse on given position with given radiuses.
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  //! Removes voxels in elliptic shape, on given position with given radiuses.
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  //! Writes the array created in the .off format.
  void writeOFF(string filename);
  //! Writes the array created in the .vect format.
  void writeVECT(string filename);
};
