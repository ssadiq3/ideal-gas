#pragma once
//#pragma warning( disable: 4819 )

#include "cinder/gl/gl.h"

using glm::vec2;
using std::string;

namespace idealgas {

class GasParticle {
 public:

  /**
   * Constructs gas particle object.
   * @param position initial position of particle
   * @param velocity initial velocity of particle
   * @param radius radius of particle
   */
  GasParticle(vec2 position, vec2 velocity, float radius, float mass, ci::Color color);

  /**
   * Moves particle by updating position with velocity.
   */
  void MoveParticle();

  /**
   * Draws particle with appropriate color, position, and radius
   */
  void DrawParticle();

  vec2 GetPosition() const { return position_; }

  vec2 GetVelocity() const { return velocity_; }

  float GetRadius() const;

  float GetMass() const;

  const cinder::Color& GetColor() const;

  void SetPosition(vec2 position);

  void SetVelocity(vec2 velocity);

  void SetRadius(float radius);

  void SetMass(float mass);

  void SetColor(const cinder::Color& color);

 private:
  vec2 position_;
  vec2 velocity_;
  float radius_;
  float mass_;
  ci::Color color_;
};
}

#ifndef IDEAL_GAS_GAS_PARTICLE_H
#define IDEAL_GAS_GAS_PARTICLE_H

#endif  // IDEAL_GAS_GAS_PARTICLE_H
