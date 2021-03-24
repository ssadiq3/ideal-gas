#include "gas_particle.h"

namespace idealgas {

GasParticle::GasParticle(vec2 position, vec2 velocity, float radius, float mass, ci::Color color) {
  position_ = position;
  velocity_ = velocity;
  radius_ = radius;
  color_ = color;
  mass_ = mass;
}

void GasParticle::MoveParticle() {
  position_ += velocity_;
}

void GasParticle::DrawParticle() {
  ci::gl::color(ci::Color(color_));
  ci::gl::drawSolidCircle(position_, radius_);
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

const cinder::Color& GasParticle::GetColor() const {
  return color_;
}

void GasParticle::SetRadius(float radius) {
  radius_ = radius;
}

float GasParticle::GetMass() const {
  return mass_;
}

void GasParticle::SetMass(float mass) {
  mass_ = mass;
}

void GasParticle::SetColor(const cinder::Color& color) {
  color_ = color;
}

}
