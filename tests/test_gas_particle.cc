#include <catch2/catch.hpp>

#include <gas_particle.h>

using idealgas::GasParticle;

TEST_CASE("Particle Tests") {
  GasParticle particle = GasParticle(vec2(200, 200), vec2(1, 1), 5);

  SECTION("Move particle updates position") {
    particle.MoveParticle();
    REQUIRE(vec2(201, 201) == particle.GetPosition());
  }

  SECTION("Position can be changed") {
    particle.SetPosition(vec2(150, 200));
    REQUIRE(vec2(150, 200) == particle.GetPosition());
  }

  SECTION("Velocity can be changed") {
    particle.SetVelocity(vec2(2, -2));
    REQUIRE(vec2(2, -2) == particle.GetVelocity());
  }

  SECTION("Radius can be changed") {
    particle.SetRadius(10);
    REQUIRE(10 == particle.GetRadius());
  }
}