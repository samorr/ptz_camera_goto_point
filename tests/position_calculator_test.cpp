#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "position_calculator.h"

using namespace ::testing;

namespace {

const tpxai::CameraIntrinsics dahua_intrinsics{
    cv::Matx33d{
        2338.9152623521627,  0.,                  1297.4678987212778,
        0.,                  2338.5344212108994,  743.3445529777781,
        0.,                  0.,                 1.
    },
    {
      0.03413359728013275,
      0.20648704610948337,
      -0.0006930691652865927,
      -0.0020291504344734992
    }
  };

constexpr float very_big_eps = 1.;

TEST(PositionCalculator, principal_point) {
  Eigen::Vector3f result = tpxai::CalculateAbsolutePosition({1297, 743}, dahua_intrinsics.K, {0, 0, 0});
  EXPECT_THAT(result[0], FloatNear(0, 0.05));
  EXPECT_THAT(result[1], FloatNear(0, 0.05));
  EXPECT_THAT(result[2], FloatNear(0, 0.05));
}

TEST(PositionCalculator, up_and_left_when_current_position_is_zero) {
  // http://192.168.1.102/cgi-bin/ptz.cgi?action=start&channel=1&code=PositionABS&arg1=4.5&arg2=-6&arg3=0
  const Eigen::Vector3f result = tpxai::CalculateAbsolutePosition({1104, 485}, dahua_intrinsics.K, {0, 0, 0});
  const Eigen::Vector3f expected_xyz_euler_angles_in_degrees{-6, 4.5, 0};
  EXPECT_THAT(result[0], FloatNear(expected_xyz_euler_angles_in_degrees[0], very_big_eps));
  EXPECT_THAT(result[1], FloatNear(expected_xyz_euler_angles_in_degrees[1], very_big_eps));
  EXPECT_THAT(result[2], FloatNear(expected_xyz_euler_angles_in_degrees[2], very_big_eps));

}

TEST(PositionCalculator, up_and_right_when_current_position_is_zero) {
  // http://192.168.1.102/cgi-bin/ptz.cgi?action=start&channel=1&code=PositionABS&arg1=335&arg2=-5&arg3=0
  const Eigen::Vector3f result = tpxai::CalculateAbsolutePosition({2406, 511}, dahua_intrinsics.K, {0, 0, 0});
  const Eigen::Vector3f expected_xyz_euler_angles_in_degrees{-5, 335, 0};
  EXPECT_THAT(result[0], FloatNear(expected_xyz_euler_angles_in_degrees[0], very_big_eps));
  EXPECT_THAT(result[1], FloatNear(expected_xyz_euler_angles_in_degrees[1], very_big_eps));
  EXPECT_THAT(result[2], FloatNear(expected_xyz_euler_angles_in_degrees[2], very_big_eps));
}

TEST(PositionCalculator, down_and_right_when_current_position_is_zero) {
  // http://192.168.1.102/cgi-bin/ptz.cgi?action=start&channel=1&code=PositionABS&arg1=332.3&arg2=4.5&arg3=0
  const Eigen::Vector3f result = tpxai::CalculateAbsolutePosition({2560, 954}, dahua_intrinsics.K, {0, 0, 0});
  const Eigen::Vector3f expected_xyz_euler_angles_in_degrees{4.5, 332.3, 0};
  EXPECT_THAT(result[0], FloatNear(expected_xyz_euler_angles_in_degrees[0], very_big_eps));
  EXPECT_THAT(result[1], FloatNear(expected_xyz_euler_angles_in_degrees[1], very_big_eps));
  EXPECT_THAT(result[2], FloatNear(expected_xyz_euler_angles_in_degrees[2], very_big_eps));
}

TEST(PositionCalculator, down_and_left_when_current_position_is_zero) {
  // http://192.168.1.102/cgi-bin/ptz.cgi?action=start&channel=1&code=PositionABS&arg1=12&arg2=10&arg3=0
  const Eigen::Vector3f result = tpxai::CalculateAbsolutePosition({790, 1139}, dahua_intrinsics.K, {0, 0, 0});
  const Eigen::Vector3f expected_xyz_euler_angles_in_degrees{10, 12, 0};
  EXPECT_THAT(result[0], FloatNear(expected_xyz_euler_angles_in_degrees[0], very_big_eps));
  EXPECT_THAT(result[1], FloatNear(expected_xyz_euler_angles_in_degrees[1], very_big_eps));
  EXPECT_THAT(result[2], FloatNear(expected_xyz_euler_angles_in_degrees[2], very_big_eps));
}

} // anonymous namespace
