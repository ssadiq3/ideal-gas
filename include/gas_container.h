#pragma once
#pragma warning( disable: 4819 )

#include "cinder/gl/gl.h"
#include "gas_particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * TODO: Add more parameters to this constructor, and add documentation.
   */
  GasContainer();

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  void CheckWallCollision();

  void CheckParticleCollision();

 private:
  /**
   * This variable is just for the purposes of demonstrating how to make a shape move
   * across a screen. Please remove it once you start working on your code.
   */
  std::vector<GasParticle> particles_;
  float left_boundary_x;
  float left_boundary_y;
  float right_boundary_x;
  float right_boundary_y;
};

}  // namespace idealgas
