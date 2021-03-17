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
   * Constructs the gas container with random initial positions inside the rectangle.
   * @param particle_count Number of particles in container
   * @param particle_radius Radius of particles in container
   */
  GasContainer(float particle_count, float particle_radius);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Checks if particle at given index in particles is touching wall,
   * and changes velocity appropriately.
   * @param t index of particle to check in particles
   */
  void CheckWallCollision(size_t t);

  /**
   * Checks if particle at given index is colliding with any other particle
   * and changes velocities accordingly.
   * @param t index of particle to check collisions for in particles
   */
  void CheckParticleCollision(size_t t);

  /**
   * Generates a random float for initial positions in the simulation
   * @param min lower bound for random float
   * @param max upper bound for random float
   * @return random float
   */
  float GetRandomFloat(float min, float max);

  /**
   * Setter for particle objects vector
   * @param particles vector for particle instances
   */
  void SetParticles(const std::vector<GasParticle>& particles);

  /**
   * Getter for particles vector
   * @return vector of current particle instances
   */
  const std::vector<GasParticle>& GetParticles() const;

 private:
  std::vector<GasParticle> particles_;
  const float left_boundary_x_ = 100;
  const float left_boundary_y_ = 100;
  const float right_boundary_x_ = 600;
  const float right_boundary_y_ = 400;
  float x_velocity_ = 1;
  float y_velocity_ = 1;
};

}  // namespace idealgas
