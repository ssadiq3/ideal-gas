#pragma once
#pragma warning( disable: 4819 )

#include "cinder/gl/gl.h"
#include "gas_particle.h"
#include "gas_histogram.h"

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
  GasContainer(float particle_count, float cent_radius, float cent_mass);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display();

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
   * Helper for check particle collision that sets the new velocities of particles
   * @param particle_1 one particle in collision
   * @param particle_2 other particle in collision
   */
  void DoParticleCollision(GasParticle& particle_1, GasParticle& particle_2);
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
  //Instantiate histogram objects to work with in source file
  GasHistogram histogram_1_ = GasHistogram(5, vec2(100,450),
                                           vec2(350,700), "green");
  GasHistogram histogram_2_ = GasHistogram(5, vec2(400, 450),
                                           vec2(650, 700), "blue");
  GasHistogram histogram_3_ = GasHistogram(5, vec2(700, 450),
                                           vec2(950, 700), "red");
  const float LEFT_BOUNDARY_X_ = 200;
  const float LEFT_BOUNDARY_Y_ = 100;
  const float RIGHT_BOUNDARY_X_ = 800;
  const float RIGHT_BOUNDARY_Y_ = 400;
  float cent_mass_;
  float small_mass_;
  float big_mass_;
  float x_velocity_ = 2;
  float y_velocity_ = 2;
};

}  // namespace idealgas
