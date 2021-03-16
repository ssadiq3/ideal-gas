#include "gas_container.h"

#include <gas_particle.h>

namespace idealgas {

using glm::vec2;
using std::cout;

GasContainer::GasContainer() {
  left_boundary_x = 100;
  left_boundary_y = 100;
  right_boundary_x = 600;
  right_boundary_y = 400;
  for (size_t i = 0; i <= 50; i++) {
    particles_.push_back(GasParticle(vec2(GetRandomFloat(left_boundary_x+10, right_boundary_x-10),
                        GetRandomFloat(left_boundary_y+10, right_boundary_y-10)), vec2(1, 1)));
  }
}

void GasContainer::Display() const {
  for (size_t i = 0; i < particles_.size(); i++) {
    ci::gl::color(ci::Color("orange"));
    ci::gl::drawSolidCircle(particles_[i].GetPosition(), 10);
  }
  /*ci::gl::drawSolidCircle(vec2(rand_1, rand_2), 10);
  ci::gl::drawSolidCircle(vec2(rand_2, rand_1), 10);
  // This function has a lot of magic numbers; be sure to design your code in a
  way that avoids this. ci::gl::color(ci::Color("orange"));
  ci::gl::drawSolidCircle(vec2(dummy_variable_, 200), 10);*/
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(left_boundary_x, left_boundary_y),
                                    vec2(right_boundary_x, right_boundary_y)));
}

void GasContainer::AdvanceOneFrame() {
  for (size_t i = 0; i < particles_.size(); i++) {
    CheckParticleCollision(i);
    CheckWallCollision(i);
    particles_[i].MoveParticle();
  }
}

void GasContainer::CheckWallCollision(size_t t) {
  float current_x_pos = particles_[t].GetPosition().x;
  float current_y_pos = particles_[t].GetPosition().y;
  float current_x_vel = particles_[t].GetVelocity().x;
  float current_y_vel = particles_[t].GetVelocity().y;
  float radius = particles_[t].kRadius;

  if (current_x_pos - radius <= left_boundary_x ||
      current_x_pos + radius >= right_boundary_x) {
    particles_[t].SetVelocity(vec2(current_x_vel * -1, current_y_vel));
  } else if (current_y_pos - radius <= left_boundary_y ||
             current_y_pos + radius >= right_boundary_y) {
    particles_[t].SetVelocity(vec2(current_x_vel, current_y_vel * -1));
  }
}

void GasContainer::CheckParticleCollision(size_t t) {
  for (size_t j = t + 1; j < particles_.size(); j++) {
    vec2 position_1 = particles_[t].GetPosition();
    vec2 velocity_1 = particles_[t].GetVelocity();
    vec2 position_2 = particles_[j].GetPosition();
    vec2 velocity_2 = particles_[j].GetVelocity();
    float radius_1 = particles_[t].kRadius;
    float radius_2 = particles_[j].kRadius;

    if (distance(position_1, position_2) <= radius_1 + radius_2 &&
        dot(velocity_1 - velocity_2, position_1 - position_2) < 0) {
      particles_[t].SetVelocity(
          velocity_1 -
          (dot(velocity_1 - velocity_2, position_1 - position_2) /
           (length(position_1 - position_2) * length(position_1 - position_2)) *
           (position_1 - position_2)));

      particles_[j].SetVelocity(
          velocity_2 -
          (dot(velocity_2 - velocity_1, position_2 - position_1) /
           (length(position_2 - position_1) * length(position_2 - position_1)) *
           (position_2 - position_1)));
    }
  }
}

float GasContainer::GetRandomFloat(float min, float max) {
  float random = ((float) rand()) / (float) RAND_MAX;
  float range = max - min;
  return (random*range) + min;
}
const std::vector<GasParticle>& GasContainer::getParticles() const {
  return particles_;
}

}  // namespace idealgas
