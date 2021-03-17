#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;
using idealgas::GasParticle;

TEST_CASE("Wall Collisions") {
  GasContainer container = GasContainer(1, 5);
  std::vector<GasParticle> particles = container.GetParticles();

  SECTION("Left wall collision") {
    particles[0].SetPosition(vec2(105, 200));
    particles[0].SetVelocity(vec2(-1, 0));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(1, 0) == container.GetParticles()[0].GetVelocity());
  }

  SECTION("Right wall collision") {
    particles[0].SetPosition(vec2(595, 200));
    particles[0].SetVelocity(vec2(1, 0));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(-1, 0) == container.GetParticles()[0].GetVelocity());
  }

  SECTION("Top wall collision") {
    particles[0].SetPosition(vec2(250, 105));
    particles[0].SetVelocity(vec2(0, 1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(0, -1) == container.GetParticles()[0].GetVelocity());
  }

  SECTION("Bottom wall collision") {
    particles[0].SetPosition(vec2(250, 395));
    particles[0].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(0, 1) == container.GetParticles()[0].GetVelocity());
  }
}

TEST_CASE("2 Particle Collisions") {
  GasContainer container = GasContainer(1, 5);
  std::vector<GasParticle> particles = container.GetParticles();
  SECTION("Two Particles in x direction- Particle 1 test") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(-1, 0));
    particles[1].SetVelocity(vec2(1, 0));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(1, 0) == container.GetParticles()[0].GetVelocity());
  }

  SECTION("Two Particles in x direction- Particle 2 test") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(-1, 0));
    particles[1].SetVelocity(vec2(1, 0));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(-1, 0) == container.GetParticles()[1].GetVelocity());
  }

  SECTION("Two Particles in y direction- Particle 1 test") {
    particles[0].SetPosition(vec2(300, 205));
    particles[1].SetPosition(vec2(300, 200));
    particles[0].SetVelocity(vec2(0, -1));
    particles[1].SetVelocity(vec2(0, 1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(0, 1) == container.GetParticles()[0].GetVelocity());
  }

  SECTION("Two Particles in y direction- Particle 2 test") {
    particles[0].SetPosition(vec2(300, 205));
    particles[1].SetPosition(vec2(300, 200));
    particles[0].SetVelocity(vec2(0, -1));
    particles[1].SetVelocity(vec2(0, 1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(0, -1) == container.GetParticles()[1].GetVelocity());
  }

  SECTION("Two Particles moving away in x directions, no collision, Particle 1") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(1, 0));
    particles[1].SetVelocity(vec2(-1, 0));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(1, 0) == container.GetParticles()[0].GetVelocity());
  }

  SECTION("Two Particles moving away in x directions, no collision, Particle 2") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(1, 0));
    particles[1].SetVelocity(vec2(-1, 0));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(-1, 0) == container.GetParticles()[1].GetVelocity());
  }

  SECTION("Two Particles moving away in y direction, no collision, Particle 1") {
    particles[0].SetPosition(vec2(300, 205));
    particles[1].SetPosition(vec2(300, 200));
    particles[0].SetVelocity(vec2(0, 1));
    particles[1].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(0, 1) == container.GetParticles()[0].GetVelocity());
  }

  SECTION("Two Particles moving away in y direction, no collision, Particle 2") {
    particles[0].SetPosition(vec2(300, 205));
    particles[1].SetPosition(vec2(300, 200));
    particles[0].SetVelocity(vec2(0, 1));
    particles[1].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(0, -1) == container.GetParticles()[1].GetVelocity());
  }
}

TEST_CASE("3 Particle Collisions") {
  GasContainer container = GasContainer(3, 5);
  std::vector<GasParticle> particles = container.GetParticles();
  SECTION("2 Particles in x direction, 1 in y- Particle 1 test x direction") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[2].SetPosition(vec2(202.5, 205));
    particles[0].SetVelocity(vec2(-1, 0));
    particles[1].SetVelocity(vec2(1, 0));
    particles[2].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(1.2f == Approx(container.GetParticles()[0].GetVelocity().x));
  }

  SECTION("2 Particles in x direction, 1 in y- Particle 1 test y direction") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[2].SetPosition(vec2(202.5, 205));
    particles[0].SetVelocity(vec2(-1, 0));
    particles[1].SetVelocity(vec2(1, 0));
    particles[2].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(-0.4f == Approx(container.GetParticles()[0].GetVelocity().y));
  }

  SECTION("2 Particles in x direction, 1 in y- Particle 2 test x direction") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[2].SetPosition(vec2(202.5, 205));
    particles[0].SetVelocity(vec2(-1, 0));
    particles[1].SetVelocity(vec2(1, 0));
    particles[2].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(-1.08f == Approx(container.GetParticles()[1].GetVelocity().x));
  }

  SECTION("Two Particles in x direction, 1 in y- Particle 2 test y direction") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[2].SetPosition(vec2(202.5, 205));
    particles[0].SetVelocity(vec2(-1, 0));
    particles[1].SetVelocity(vec2(1, 0));
    particles[2].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(-0.16f == Approx(container.GetParticles()[1].GetVelocity().y));
  }

  SECTION("Two Particles in x direction, 1 in y- Particle 3 test x direction") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[2].SetPosition(vec2(202.5, 205));
    particles[0].SetVelocity(vec2(-1, 0));
    particles[1].SetVelocity(vec2(1, 0));
    particles[2].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(-0.12f == Approx(container.GetParticles()[2].GetVelocity().x));
  }

  SECTION("Two Particles in x direction, 1 in y- Particle 3 test y direction") {
    particles[0].SetPosition(vec2(205, 200));
    particles[1].SetPosition(vec2(200, 200));
    particles[2].SetPosition(vec2(202.5, 205));
    particles[0].SetVelocity(vec2(-1, 0));
    particles[1].SetVelocity(vec2(1, 0));
    particles[2].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(-0.44f == Approx(container.GetParticles()[2].GetVelocity().y));
  }
}

TEST_CASE("Standard movement tests") {
  GasContainer container = GasContainer(1, 5);
  std::vector<GasParticle> particles = container.GetParticles();

  SECTION("Moving positive x direction") {
    particles[0].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(1, 0));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(201, 200) == container.GetParticles()[0].GetPosition());
  }

  SECTION("Moving negative x direction") {
    particles[0].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(-1, 0));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(199, 200) == container.GetParticles()[0].GetPosition());
  }

  SECTION("Moving positive y direction") {
    particles[0].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(0, 1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(200, 201) == container.GetParticles()[0].GetPosition());
  }

  SECTION("Moving negative y direction") {
    particles[0].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(0, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(200, 199) == container.GetParticles()[0].GetPosition());
  }

  SECTION("Moving positive x, positive y direction") {
    particles[0].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(1, 1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(201, 201) == container.GetParticles()[0].GetPosition());
  }

  SECTION("Moving positive x, negative y direction") {
    particles[0].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(1, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(201, 199) == container.GetParticles()[0].GetPosition());
  }

  SECTION("Moving negative x, positive y direction") {
    particles[0].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(-1, 1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(199, 201) == container.GetParticles()[0].GetPosition());
  }

  SECTION("Moving negative x, negative y direction") {
    particles[0].SetPosition(vec2(200, 200));
    particles[0].SetVelocity(vec2(-1, -1));
    container.SetParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(199, 199) == container.GetParticles()[0].GetPosition());
  }
}

/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/
