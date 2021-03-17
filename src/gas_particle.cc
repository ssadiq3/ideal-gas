#include "gas_particle.h"

namespace idealgas {

GasParticle::GasParticle(vec2 position, vec2 velocity, float radius) {
  position_ = position;
  velocity_ = velocity;
  radius_ = radius;
}

void GasParticle::MoveParticle() {
  position_ += velocity_;
}

void GasParticle::SetPosition(vec2 set_position) {
  position_ = set_position;
}

void GasParticle::SetVelocity(vec2 set_velocity) {
  velocity_ = set_velocity;
}

float GasParticle::GetRadius() const {
  return radius_;
}

void GasParticle::SetRadius(float radius) {
  radius_ = radius;
}

}
