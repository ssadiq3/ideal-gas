#include "gas_particle.h"

namespace idealgas {

GasParticle::GasParticle(vec2 position, vec2 velocity) {
  position_ = position;
  velocity_ = velocity;
}

void GasParticle::SetPosition(vec2 set_position) {
  position_ = set_position;
}

void GasParticle::SetVelocity(vec2 set_velocity) {
  velocity_ = set_velocity;
}

void GasParticle::MoveParticle() {
  position_ += velocity_;
}

}
