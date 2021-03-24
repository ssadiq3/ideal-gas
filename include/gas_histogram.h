#pragma once

#include "cinder/gl/gl.h"
#include "gas_particle.h"

namespace idealgas {

/**
 * The three histograms displayed to track particles and their velocities.
 */
class GasHistogram {
 public:
  /**
   * Constructs a histogram for a specific set of particles.
   * @param maxSpeed maximum speed of particles
   * @param top_left top left of graph
   * @param bottom_right bottom right of graph
   * @param color color of histogram bars
   */
  GasHistogram(float maxSpeed, vec2 top_left, vec2 bottom_right, ci::Color color);

  /**
   * Updates the histogram every frame when speeds of velocities change.
   * @param particles list of particles that histogram is updating for
   */
  void UpdateHistogram(std::vector<GasParticle> particles);

  /**
   * Draws the histogram to be displayed on the simulation.
   */
  void DrawHistogram();

  /**
   * Helper for DrawHistogram that draws the different bars according to the speeds
   */
  void DrawHistogramBars();

  /**
   * Helper for DrawHistogram that draws x-axis with speed numbers at intervals
   */
  void DrawHistogramXAxis();

  /**
   * Helper for DrawHistogram that draws y-axis with number of particles at intervals
   */
  void DrawHistogramYAxis();

 private:
  float left_boundary_x_;
  float left_boundary_y_;
  float right_boundary_x_;
  float right_boundary_y_;
  float first_interval_;
  float second_interval_;
  float third_interval_;
  float fourth_interval_;
  float fifth_interval_;
  float first_interval_count = 0;
  float second_interval_count = 0;
  float third_interval_count = 0;
  float fourth_interval_count = 0;
  float fifth_interval_count = 0;
  const float COUNT_MAGNIFIER_ = 10;
  float num_particles_ = 0;
  ci::Color color_;

  /**
   * Resets the interval count variables so update can count again.
   */
  void Reset();
};
}
