#pragma once

#include "voxelclass.h"
#include <string>

using std::string;

/**
 * @brief The Sculptor class
 */
class Sculptor {
protected:
    /**
   * @brief v
   */
  Voxel ***v;    // 3D matrix
  /**
   * @brief nx
   * @brief ny
   * @brief nz
   */
  int nx,ny,nz;  // Dimensions
  /**
   * @brief r
   * @brief g
   * @brief b
   * @brief a
   */
  float r,g,b,a; // Current drawing color
public:
  /**
   * @brief Sculptor
   * @param _nx
   * @param _ny
   * @param _nz
   */
  Sculptor(int _nx, int _ny, int _nz);
  /**
  * @brief ~Sculptor
  */
  ~Sculptor();
  /**
   * @brief setColor
   * @param r
   * @param g
   * @param b
   * @param alpha
   */
  void setColor(float r, float g, float b, float alpha);
  /**
   * @brief putVoxel
   * @param x
   * @param y
   * @param z
   */
  void putVoxel(int x, int y, int z);
  /**
   * @brief cutVoxel
   * @param x
   * @param y
   * @param z
   */
  void cutVoxel(int x, int y, int z);
  /**
   * @brief putBox
   * @param x0
   * @param x1
   * @param y0
   * @param y1
   * @param z0
   * @param z1
   */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
  * @brief cutBox
  * @param x0
  * @param x1
  * @param y0
  * @param y1
  * @param z0
  * @param z1
  */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
   * @brief putSphere
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param radius
   */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
   * @brief cutSphere
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param radius
   */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
   * @brief putEllipsoid
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param rx
   * @param ry
   * @param rz
   */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
   * @brief cutEllipsoid
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param rx
   * @param ry
   * @param rz
   */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
   * @brief writeOFF
   * @param filename
   */
  void writeOFF(string filename);
  /**
   * @brief writeVECT
   * @param filename
   */
  void writeVECT(string filename);
};
