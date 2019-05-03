#pragma once

struct Voxel {
  //! Red component of the voxel.
  float r;
  //! Green component of the voxel.
  float g;
  //! Blue component of the voxel.
  float b;
  //! Transparency component of the voxel.
  float a;
  //! Boolean that determines if the voxel is activated or not.
  bool isOn;
};
