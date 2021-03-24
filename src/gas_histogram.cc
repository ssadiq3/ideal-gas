#include "gas_histogram.h"

using glm::vec2;
using std::vector;

namespace idealgas {


GasHistogram::GasHistogram(float maxSpeed, vec2 top_left, vec2 bottom_right, ci::Color color) {
  //Set interval cutoffs to place number of particles in graph
  first_interval_ = maxSpeed/5;
  second_interval_ = 2*maxSpeed/5;
  third_interval_ = 3*maxSpeed/5;
  fourth_interval_ = 4*maxSpeed/5;
  fifth_interval_ = maxSpeed;
  //Set boundaries of graph
  left_boundary_x_ = top_left.x;
  left_boundary_y_ = top_left.y;
  right_boundary_x_ = bottom_right.x;
  right_boundary_y_ = bottom_right.y;
  color_ = color;
}

void GasHistogram::UpdateHistogram(std::vector<GasParticle> particles) {
  num_particles_=(float)particles.size();
  for (GasParticle particle : particles) {
    //Use count magnifier so bar height can be raised on simulation
    //Add to interval's height if particle's velocity is in the interval
    if (length(particle.GetVelocity()) < first_interval_) {
      first_interval_count += COUNT_MAGNIFIER_;
    } else if (length(particle.GetVelocity()) < second_interval_) {
      second_interval_count += COUNT_MAGNIFIER_;
    } else if (length(particle.GetVelocity()) < third_interval_) {
      third_interval_count += COUNT_MAGNIFIER_;
    } else if (length(particle.GetVelocity()) < fourth_interval_) {
      fourth_interval_count+= COUNT_MAGNIFIER_;
    } else {
      fifth_interval_count += COUNT_MAGNIFIER_;
    }
  }
}

void GasHistogram::DrawHistogram() {
  float interval_width = (right_boundary_x_ - left_boundary_x_)/5;
  //Draw outline of graph
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(left_boundary_x_, left_boundary_y_),
                                    vec2(right_boundary_x_, right_boundary_y_)));

  //Use helpers to draw x and y axes
  DrawHistogramBars();
  DrawHistogramXAxis();
  DrawHistogramYAxis();
  Reset();
}

void GasHistogram::DrawHistogramBars() {
  float interval_width = (right_boundary_x_ - left_boundary_x_)/5;
  ci::gl::color(color_);

  //Draw solid rectangles for bars according to interval counts, using boundaries as reference
  ci::gl::drawSolidRect(ci::Rectf(vec2(left_boundary_x_, right_boundary_y_-first_interval_count),
                                  vec2(left_boundary_x_+interval_width, right_boundary_y_)));
  ci::gl::drawSolidRect(ci::Rectf(
      vec2(left_boundary_x_+interval_width,right_boundary_y_-second_interval_count),
      vec2(left_boundary_x_+2*interval_width, right_boundary_y_)));
  ci::gl::drawSolidRect(ci::Rectf(
      vec2(left_boundary_x_+2*interval_width, right_boundary_y_-third_interval_count),
      vec2(left_boundary_x_+3*interval_width, right_boundary_y_)));
  ci::gl::drawSolidRect(ci::Rectf(
      vec2(left_boundary_x_+3*interval_width, right_boundary_y_-fourth_interval_count),
      vec2(left_boundary_x_+4*interval_width, right_boundary_y_)));
  ci::gl::drawSolidRect(ci::Rectf(
      vec2(left_boundary_x_+4*interval_width, right_boundary_y_-fifth_interval_count),
      vec2(left_boundary_x_+5*interval_width, right_boundary_y_)));
}

void GasHistogram::DrawHistogramXAxis() {
  float interval_width = (right_boundary_x_ - left_boundary_x_)/5;
  //Draw axis title slightly below x axis
  ci::gl::drawString("Particle Speeds",
                     vec2(left_boundary_x_+ 3*interval_width/2, right_boundary_y_+20),
                     ci::Color("white"), ci::Font("Calibri", 25));
  //Draw speed intervals on x-axis using interval variables and boundaries as reference
  ci::gl::drawString("0", vec2(left_boundary_x_, right_boundary_y_),
                     ci::Color("white"), ci::Font("Calibri", 15));
  ci::gl::drawString(std::to_string((int)first_interval_),
                     vec2(left_boundary_x_+interval_width, right_boundary_y_),
                     ci::Color("white"), ci::Font("Calibri", 15));
  ci::gl::drawString(std::to_string((int)second_interval_),
                     vec2(left_boundary_x_+2*interval_width, right_boundary_y_),
                     ci::Color("white"), ci::Font("Calibri", 15));
  ci::gl::drawString(std::to_string((int)third_interval_),
                     vec2(left_boundary_x_+3*interval_width, right_boundary_y_),
                     ci::Color("white"), ci::Font("Calibri", 15));
  ci::gl::drawString(std::to_string((int)fourth_interval_),
                     vec2(left_boundary_x_+4*interval_width, right_boundary_y_),
                     ci::Color("white"), ci::Font("Calibri", 15));
  ci::gl::drawString(std::to_string((int)fifth_interval_),
                     vec2(right_boundary_x_, right_boundary_y_),
                     ci::Color("white"), ci::Font("Calibri", 15));
}

void GasHistogram::DrawHistogramYAxis() {
  int int_particles = (int) num_particles_;
  float interval_width = (right_boundary_y_-left_boundary_y_)/5;
  //Draw number of particles using variable and boundaries as reference
  ci::gl::drawString(std::to_string(int_particles/5),
                     vec2(left_boundary_x_-20,right_boundary_y_-interval_width),
                     ci::Color("white"), ci::Font("Calibri", 15));
  ci::gl::drawString(std::to_string(2*int_particles/5),
                     vec2(left_boundary_x_-20,right_boundary_y_-2*interval_width),
                     ci::Color("white"), ci::Font("Calibri", 15));
  ci::gl::drawString(std::to_string(3*int_particles/5),
                     vec2(left_boundary_x_-20,right_boundary_y_-3*interval_width),
                     ci::Color("white"), ci::Font("Calibri", 15));
  ci::gl::drawString(std::to_string(4*int_particles/5),
                     vec2(left_boundary_x_-20,right_boundary_y_-4*interval_width),
                     ci::Color("white"), ci::Font("Calibri", 15));
  ci::gl::drawString(std::to_string(int_particles),
                     vec2(left_boundary_x_-20,left_boundary_y_),
                     ci::Color("white"), ci::Font("Calibri", 15));
}

void GasHistogram::Reset() {
  //reset all variables to 0 for next call to update
  first_interval_count = 0;
  second_interval_count = 0;
  third_interval_count = 0;
  fourth_interval_count = 0;
  fifth_interval_count = 0;
}


}
