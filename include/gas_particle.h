#pragma once
#pragma warning( disable: 4819 )

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

class GasParticle {
 public:

  /**
   * Constructs gas particle object.
   * @param position initial position of particle
   * @param velocity initial velocity of particle
   * @param radius radius of particle
   */
  GasParticle(vec2 position, vec2 velocity, float radius);

  /**
   * Moves particle by updating position with velocity.
   */
  void MoveParticle();

  vec2 GetPosition() const { return position_; }

  vec2 GetVelocity() const { return velocity_; }

  float GetRadius() const;

  void SetPosition(vec2 position);

  void SetVelocity(vec2 velocity);

  void SetRadius(float radius);

 private:
  vec2 position_;
  vec2 velocity_;
  float radius_;
};
}

#ifndef IDEAL_GAS_GAS_PARTICLE_H
#define IDEAL_GAS_GAS_PARTICLE_H

#endif  // IDEAL_GAS_GAS_PARTICLE_H
