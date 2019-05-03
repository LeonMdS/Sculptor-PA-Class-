#pragma once

/**
 * @brief The Voxel struct
 */
struct Voxel {
    /**
   * @brief r
   * @brief g
   * @brief b
   */
  float r,g,b; // Colors
  /**
   * @brief a
   */
  float a;     // Transparency
  /**
   * @brief isOn
   */
  bool isOn;   // Included or not
};
