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
  /*!
   \param _nx sets the size of X dimension.
   \param _ny sets the size of Y dimension.
   \param _nz sets the size of Z dimension.
  */
  Sculptor(int _nx, int _ny, int _nz);

  //! Class Destructor.
  ~Sculptor();

  //! Sets new color to the sculptor.
  /*!
    \param r sets the red component of Sculptor.
    \param g sets the green component of Sculptor.
    \param b sets the blue component of Sculptor.
    \param alpha sets the transparency "a" of Sculptor.
  */
  void setColor(float r, float g, float b, float alpha);

  //! Inputs a voxel on speficied position, with parameters based on the Sculptor's.
  /*!
    \param x is the x coordinate of Sculptor.
    \param y is the y coordinate of Sculptor.
    \param z is the z coordinate of Sculptor.
  */
  void putVoxel(int x, int y, int z);

  //! Removes a voxel from specified position.
  /*!
    \param x is the x coordinate of Sculptor.
    \param y is the y coordinate of Sculptor.
    \param z is the z coordinate of Sculptor.
  */
  void cutVoxel(int x, int y, int z);

  //! Creates a box on given position, with given sizes.
  /*!
    \param x0 is where the box begins in the X axis.
    \param x1 is where the box ends in the X axis.
    \param y0 is where the box begins in the Y axis.
    \param y1 is where the box ends in the Y axis.
    \param z0 is where the box begins in the Z axis.
    \param z1 is where the box ends in the Z axis.
  */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

  //! Removes voxels in a box shape on given position with given sizes.
  /*!
    \param x0 is where the box begins in the X axis.
    \param x1 is where the box ends in the X axis.
    \param y0 is where the box begins in the Y axis.
    \param y1 is where the box ends in the Y axis.
    \param z0 is where the box begins in the Z axis.
    \param z1 is where the box ends in the Z axis.
  */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

  //! Creates a sphere on given position with given radius.
  /*!
    \param xcenter is the x position of the sphere's center.
    \param ycenter is the y position of the sphere's center.
    \param zcenter is the z position of the sphere's center.
    \param radius sets the radius of the sphere.
  */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);

  //! Removes voxels in a spherical shape on given position with given radius.
  /*!
    \param xcenter is the x position of the sphere's center.
    \param ycenter is the y position of the sphere's center.
    \param zcenter is the z position of the sphere's center.
    \param radius sets the radius of the sphere.
  */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

  //! Creates an ellipsoid on given position with given radiuses.
 /*!
    \param xcenter is the x position of the ellipsoid's center.
    \param ycenter is the y position of the ellipsoid's center.
    \param zcenter is the z position of the ellipsoid's center.
    \param rx sets the x-radius of the ellipsoid.
    \param ry sets the y-radius of the ellipsoid.
    \param rz sets the z-radius of the ellipsoid.
  */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

  //! Removes voxels in elliptic shape, on given position with given radiuses.
   /*!
    \param xcenter is the x position of the ellipsoid's center.
    \param ycenter is the y position of the ellipsoid's center.
    \param zcenter is the z position of the ellipsoid's center.
    \param rx sets the x-radius of the ellipsoid.
    \param ry sets the y-radius of the ellipsoid.
    \param rz sets the z-radius of the ellipsoid.
  */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  //! Writes the array created in the .off format.
  //! \param file is the path where the off file is set on the device. If the file doesn't exist, the function creates one.

  void writeOFF(string filename);
  //! Writes the array created in the .vect format.
  //! \param file is the path where the vect file is set on the device. If the file doesn't exist, the function creates one.
  void writeVECT(string filename);
};
