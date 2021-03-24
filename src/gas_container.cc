#include "gas_container.h"

#include <gas_particle.h>

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(float particle_count, float cent_radius, float cent_mass) {
  //Set bigger and smaller masses and radii based off central mass and radius
  float small_radius = 2*cent_radius/3;
  float big_radius = 3*cent_radius/2;
  cent_mass_ = cent_mass;
  small_mass_ = 2*cent_mass/3;
  big_mass_ = 3*cent_mass/2;
  for (int i = 0; i <= particle_count; i++) {
    //Adds even amount of each type of particle to particles vector
    if (i < particle_count/3) {
      particles_.push_back(GasParticle(vec2(
          GetRandomFloat(LEFT_BOUNDARY_X_ + small_radius, RIGHT_BOUNDARY_X_ - small_radius),
          GetRandomFloat(LEFT_BOUNDARY_Y_ + small_radius, RIGHT_BOUNDARY_Y_ - small_radius)),
      vec2(x_velocity_, y_velocity_),
             small_radius, small_mass_, "green"));
    } else if (i < particle_count/1.5) {
      particles_.push_back(GasParticle(vec2(
          GetRandomFloat(LEFT_BOUNDARY_X_ + cent_radius, RIGHT_BOUNDARY_X_ - cent_radius),
          GetRandomFloat(LEFT_BOUNDARY_Y_ + cent_radius, RIGHT_BOUNDARY_Y_ - cent_radius)),
      vec2(x_velocity_, y_velocity_),
             cent_radius, cent_mass_, "blue"));
    } else {
      particles_.push_back(GasParticle(vec2(
          GetRandomFloat(LEFT_BOUNDARY_X_ + big_radius, RIGHT_BOUNDARY_X_ - big_radius),
          GetRandomFloat(LEFT_BOUNDARY_Y_ + big_radius, RIGHT_BOUNDARY_Y_ - big_radius)),
      vec2(x_velocity_, y_velocity_),
             big_radius, big_mass_, "red"));
    }
  }
}

void GasContainer::Display() {
  //draw solid circle for every particle in particles vector
  for (GasParticle particle : particles_) {
    particle.DrawParticle();
  }
  //Draw 3 histograms
  histogram_1_.DrawHistogram();
  histogram_2_.DrawHistogram();
  histogram_3_.DrawHistogram();

  ci::gl::color(ci::Color("white"));
  //draw container with boundaries from header file
  ci::gl::drawStrokedRect(ci::Rectf(vec2(LEFT_BOUNDARY_X_, LEFT_BOUNDARY_Y_),
                                    vec2(RIGHT_BOUNDARY_X_, RIGHT_BOUNDARY_Y_)));
}

void GasContainer::AdvanceOneFrame() {
  std::vector<GasParticle> small_particles;
  std::vector<GasParticle> med_particles;
  std::vector<GasParticle> big_particles;
  //iterate through all particles, find whether they collide with other particles,
  // the wall, and then move particle regularly
  for (size_t i = 0; i < particles_.size(); i++) {
    CheckParticleCollision(i);
    CheckWallCollision(i);
    particles_[i].MoveParticle();
    //Set particle vectors for histograms with updated velocity vec2's
    if (particles_[i].GetMass() <= small_mass_) {
      small_particles.push_back(particles_[i]);
    } else if (particles_[i].GetMass() <= cent_mass_) {
      med_particles.push_back(particles_[i]);
    } else {
      big_particles.push_back(particles_[i]);
    }
  }
  //Update histograms using particle vectors just set
  histogram_1_.UpdateHistogram(small_particles);
  histogram_2_.UpdateHistogram(med_particles);
  histogram_3_.UpdateHistogram(big_particles);
}

void GasContainer::CheckWallCollision(size_t t) {
  //local variables to store current positions and velocities
  float current_x_pos = particles_[t].GetPosition().x;
  float current_y_pos = particles_[t].GetPosition().y;
  float current_x_vel = particles_[t].GetVelocity().x;
  float current_y_vel = particles_[t].GetVelocity().y;
  float radius = particles_[t].GetRadius();

  //If center + radius is touching an x wall, change x velocity
  if (current_x_pos - radius <= LEFT_BOUNDARY_X_ ||
      current_x_pos + radius >= RIGHT_BOUNDARY_X_) {
    particles_[t].SetVelocity(vec2(current_x_vel * -1, current_y_vel));
    //If center + radius is touching y wall, change y velocity
  } else if (current_y_pos - radius <= LEFT_BOUNDARY_Y_ ||
             current_y_pos + radius >= RIGHT_BOUNDARY_Y_) {
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
    float mass_1 = particles_[t].GetMass();
    float mass_2 = particles_[j].GetMass();
    //Using equation from doc, if expression is less than 0, need to change velocities
    if (distance(particles_[t].GetPosition(), particles_[j].GetPosition()) <=
            particles_[t].GetRadius() + particles_[j].GetRadius() &&
        dot(particles_[t].GetVelocity() - particles_[j].GetVelocity(),
            particles_[t].GetPosition() - particles_[j].GetPosition()) < 0) {
      //If above expression is true, change velocities through helper method
      DoParticleCollision(particles_[t], particles_[j]);
    }
  }
}

void GasContainer::DoParticleCollision(GasParticle& particle_1, GasParticle& particle_2) {
  vec2 position_1 = particle_1.GetPosition();
  vec2 velocity_1 = particle_1.GetVelocity();
  vec2 position_2 = particle_2.GetPosition();
  vec2 velocity_2 = particle_2.GetVelocity();
  float mass_1 = particle_1.GetMass();
  float mass_2 = particle_2.GetMass();

  //Using equation from doc, if expression is less than 0, need to change velocities
  particle_1.SetVelocity(
      velocity_1 -
      (mass_2 * 2/(mass_1 + mass_2)*dot(velocity_1 - velocity_2, position_1 - position_2) /
       (length(position_1 - position_2) * length(position_1 - position_2)) *
       (position_1 - position_2)));

  //Changing other particle's velocity
  particle_2.SetVelocity(
      velocity_2 -
      (mass_1 * 2/(mass_1 + mass_2)*dot(velocity_2 - velocity_1, position_2 - position_1) /
       (length(position_2 - position_1) * length(position_2 - position_1)) *
       (position_2 - position_1)));
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
