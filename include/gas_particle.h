#pragma once
#pragma warning( disable: 4819 )

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

class GasParticle {
 public:
  const float kRadius = 10;

  GasParticle(vec2 position, vec2 velocity);

  vec2 GetPosition() const { return position_; }

  vec2 GetVelocity() const { return velocity_; }

  void SetPosition(vec2 position);

  void SetVelocity(vec2 velocity);

  void MoveParticle();

 private:
  vec2 position_;
  vec2 velocity_;
};
}

#ifndef IDEAL_GAS_GAS_PARTICLE_H
#define IDEAL_GAS_GAS_PARTICLE_H

#endif  // IDEAL_GAS_GAS_PARTICLE_H
