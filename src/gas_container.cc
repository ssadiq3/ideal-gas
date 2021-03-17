#include "gas_container.h"

#include <gas_particle.h>

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(float particle_count, float radius) {
  for (size_t i = 0; i <= particle_count; i++) {
    //add passed amount of particle objects with random float positions to fill particles vector
    particles_.push_back(GasParticle(vec2(
  GetRandomFloat(left_boundary_x_ + radius, right_boundary_x_ - radius),
  GetRandomFloat(left_boundary_y_ + radius, right_boundary_y_ - radius)),
vec2(x_velocity_, y_velocity_), radius));
  }
}

void GasContainer::Display() const {
  //draw solid circle for every particle in particles vector
  for (size_t i = 0; i < particles_.size(); i++) {
    ci::gl::color(ci::Color("orange"));
    ci::gl::drawSolidCircle(particles_[i].GetPosition(), particles_[i].GetRadius());
  }
  ci::gl::color(ci::Color("white"));
  //draw container with boundaries from header file
  ci::gl::drawStrokedRect(ci::Rectf(vec2(left_boundary_x_, left_boundary_y_),
                                    vec2(right_boundary_x_, right_boundary_y_)));
}

void GasContainer::AdvanceOneFrame() {
  //iterate through all particles, find whether they collide with other particles,
  // the wall, and then move particle regularly
  for (size_t i = 0; i < particles_.size(); i++) {
    CheckParticleCollision(i);
    CheckWallCollision(i);
    particles_[i].MoveParticle();
  }
}

void GasContainer::CheckWallCollision(size_t t) {
  //local variables to store current positions and velocities
  float current_x_pos = particles_[t].GetPosition().x;
  float current_y_pos = particles_[t].GetPosition().y;
  float current_x_vel = particles_[t].GetVelocity().x;
  float current_y_vel = particles_[t].GetVelocity().y;
  float radius = particles_[t].GetRadius();

  //If center + radius is touching an x wall, change x velocity
  if (current_x_pos - radius <= left_boundary_x_ ||
      current_x_pos + radius >= right_boundary_x_) {
    particles_[t].SetVelocity(vec2(current_x_vel * -1, current_y_vel));
    //If center + radius is touching y wall, change y velocity
  } else if (current_y_pos - radius <= left_boundary_y_ ||
             current_y_pos + radius >= right_boundary_y_) {
    particles_[t].SetVelocity(vec2(current_x_vel, current_y_vel * -1));
  }
}

void GasContainer::CheckParticleCollision(size_t t) {
  //iterate through all other particles not yet used
  for (size_t j = t + 1; j < particles_.size(); j++) {
    vec2 position_1 = particles_[t].GetPosition();
    vec2 velocity_1 = particles_[t].GetVelocity();
    vec2 position_2 = particles_[j].GetPosition();
    vec2 velocity_2 = particles_[j].GetVelocity();
    float radius_1 = particles_[t].GetRadius();
    float radius_2 = particles_[j].GetRadius();

    //Using equation from doc, if expression is less than 0, need to change velocity
    if (distance(position_1, position_2) <= radius_1 + radius_2 &&
        dot(velocity_1 - velocity_2, position_1 - position_2) < 0) {
      particles_[t].SetVelocity(
          velocity_1 -
          (dot(velocity_1 - velocity_2, position_1 - position_2) /
           (length(position_1 - position_2) * length(position_1 - position_2)) *
           (position_1 - position_2)));

      //Changing other particle's velocity
      particles_[j].SetVelocity(
          velocity_2 -
          (dot(velocity_2 - velocity_1, position_2 - position_1) /
           (length(position_2 - position_1) * length(position_2 - position_1)) *
           (position_2 - position_1)));
    }
  }
}

float GasContainer::GetRandomFloat(float min, float max) {
  //From online
  float random = ((float) rand()) / (float) RAND_MAX;
  float range = max - min;
  return (random*range) + min;
}

void GasContainer::SetParticles(const std::vector<GasParticle>& particles) {
  //set particles vector to given vector
  particles_ = particles;
}

const std::vector<GasParticle>& GasContainer::GetParticles() const {
  //return current particles vector
  return particles_;
}



}  // namespace idealgas
