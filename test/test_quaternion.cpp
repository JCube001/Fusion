#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "quaternion.h"

using Catch::Matchers::WithinRel;

TEST_CASE("The default constructor produces the quaternion identity", "[quaternion]") {
    const Quaternion q;

    REQUIRE(q.w == 1.0f);
    REQUIRE(q.x == 0.0f);
    REQUIRE(q.y == 0.0f);
    REQUIRE(q.z == 0.0f);
}

TEST_CASE("The copy constructor copies all component values", "[quaternion]") {
    const Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion b(a);

    REQUIRE(b.w == 1.0f);
    REQUIRE(b.x == 2.0f);
    REQUIRE(b.y == 3.0f);
    REQUIRE(b.z == 4.0f);
}

TEST_CASE("The value constructor initializes all component values", "[quaternion]") {
    const Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);

    REQUIRE(q.w == 1.0f);
    REQUIRE(q.x == 2.0f);
    REQUIRE(q.y == 3.0f);
    REQUIRE(q.z == 4.0f);
}

TEST_CASE("The conjugate negates the vector component", "[quaternion]") {
    const auto q = Quaternion(1.0f, 2.0f, 3.0f, 4.0f).conjugate();

    REQUIRE(q.w == 1.0f);
    REQUIRE(q.x == -2.0f);
    REQUIRE(q.y == -3.0f);
    REQUIRE(q.z == -4.0f);
}

TEST_CASE("Converting to axis-angle produces an equivalent representation of rotation", "[quaternion]") {
    const Quaternion q(0.707107f, 0.0f, 0.0f, 0.707107f);
    float x, y, z, angle;

    q.convertToAxisAngle(x, y, z, angle);

    REQUIRE(x == 0.0f);
    REQUIRE(y == 0.0f);
    REQUIRE_THAT(z, WithinRel(1.0f));
    REQUIRE_THAT(angle, WithinRel(1.57079633f));
}

TEST_CASE("Converting to Euler angles produces an equivalent representation of rotation", "[quaternion]") {
    const Quaternion q(0.707107f, 0.0f, 0.0f, 0.707107f);
    float roll, pitch, yaw;
    
    q.convertToEulerAngles(roll, pitch, yaw);

    REQUIRE(roll == 0.0f);
    REQUIRE(pitch == 0.0f);
    REQUIRE_THAT(yaw, WithinRel(1.57079633f));
}

TEST_CASE("Dot product multiplication produces the correct scalar result", "[quaternion]") {
    const Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion b(2.0f, 2.0f, 2.0f, 2.0f);
    const auto r = a.dot(b);

    REQUIRE(r == 20.0f);
}

TEST_CASE("The inverse is the conjugate divided by the norm squared", "[quaternion]") {
    const auto q = Quaternion(1.0f, 2.0f, 3.0f, 4.0f).inverse();

    REQUIRE_THAT(q.w, WithinRel(0.03333333f));
    REQUIRE_THAT(q.x, WithinRel(-0.06666667f));
    REQUIRE_THAT(q.y, WithinRel(-0.1f));
    REQUIRE_THAT(q.z, WithinRel(-0.13333333f));
}

TEST_CASE("The norm is the square root of all of the components squared and added together", "[quaternion]") {
    const auto r = Quaternion(1.0f, 2.0f, 3.0f, 4.0f).norm();

    REQUIRE_THAT(r, WithinRel(5.47722558f));
}

TEST_CASE("Normalizing produces a unit quaternion", "[quaternion]") {
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);

    SECTION("The mutable call modifies the quaternion in-place") {
        q.normalize();

        REQUIRE_THAT(q.w, WithinRel(0.18257419f));
        REQUIRE_THAT(q.x, WithinRel(0.36514837f));
        REQUIRE_THAT(q.y, WithinRel(0.54772255f));
        REQUIRE_THAT(q.z, WithinRel(0.73029674f));
    }

    SECTION("The immutable call produces a new quaternion") {
        const auto r = q.normalized();

        REQUIRE_THAT(r.w, WithinRel(0.18257419f));
        REQUIRE_THAT(r.x, WithinRel(0.36514837f));
        REQUIRE_THAT(r.y, WithinRel(0.54772255f));
        REQUIRE_THAT(r.z, WithinRel(0.73029674f));
    }
}

TEST_CASE("Assignment assigns the same value of its components", "[quaternion]") {
    const Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion b = a;

    REQUIRE(b.w == 1.0f);
    REQUIRE(b.x == 2.0f);
    REQUIRE(b.y == 3.0f);
    REQUIRE(b.z == 4.0f);
}

TEST_CASE("Compound addition adds the components on the right to the left in-place", "[quaternion]") {
    Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion b(1.0f, 1.0f, 1.0f, 1.0f);

    a += b;

    REQUIRE(a.w == 2.0f);
    REQUIRE(a.x == 3.0f);
    REQUIRE(a.y == 4.0f);
    REQUIRE(a.z == 5.0f);
}

TEST_CASE("Compound subtraction subtracts the components on the right from the left in-place", "[quaternion]") {
    Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion b(1.0f, 1.0f, 1.0f, 1.0f);

    a -= b;

    REQUIRE(a.w == 0.0f);
    REQUIRE(a.x == 1.0f);
    REQUIRE(a.y == 2.0f);
    REQUIRE(a.z == 3.0f);
}

TEST_CASE("Compound scalar multiplication multiplies each component by the scalar", "[quaternion]") {
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    const float s = 2.0f;

    q *= s;

    REQUIRE(q.w == 2.0f);
    REQUIRE(q.x == 4.0f);
    REQUIRE(q.y == 6.0f);
    REQUIRE(q.z == 8.0f);
}

TEST_CASE("Compound cross product multiplication produces a new rotation", "[quaternion]") {
    Quaternion a(0.707107f, 0.0f, 0.0f, 0.707107f);
    const Quaternion b(0.707107f, 0.0f, 0.707107f, 0.0f);

    a *= b;

    REQUIRE_THAT(a.w, WithinRel(0.5f));
    REQUIRE_THAT(a.x, WithinRel(-0.5f));
    REQUIRE_THAT(a.y, WithinRel(0.5f));
    REQUIRE_THAT(a.z, WithinRel(0.5f));
}

TEST_CASE("Compound scalar division divides each component by the scalar", "[quaternion]") {
    Quaternion q(2.0f, 4.0f, 6.0f, 8.0f);
    const float s = 2.0f;

    q /= s;

    REQUIRE(q.w == 1.0f);
    REQUIRE(q.x == 2.0f);
    REQUIRE(q.y == 3.0f);
    REQUIRE(q.z == 4.0f);
}
