#include "autocode.h"

#include "params.h"
#include <cmath>
#include <iostream>

using namespace std;

// Constants for use with the S-curve functions
double pos_autocode_s_curve_constant_1;
double pos_autocode_s_curve_constant_2;
double pos_autocode_s_curve_constant_3;

void seq_autocode_fit_s_curve(std::queue<SeqWaypoint> target) {
  // TODO: examine curve fitting methods
  pos_autocode_s_curve_constant_1 = 3.25f;
  pos_autocode_s_curve_constant_2 = 2.5f;
  pos_autocode_s_curve_constant_3 = 1.0f;
}

Vec3D pos_autocode_s_curve_derivative(Vec3D curr, SeqWaypoint target) {
  Vec3D ret;

  // Do calculations
  ret.x = pos_autocode_s_curve_constant_1 * pos_autocode_s_curve_constant_2 * exp(
          -1.0 * pos_autocode_s_curve_constant_1 * (curr.x - pos_autocode_s_curve_constant_3)) /
         pow(exp(-1.0 * pos_autocode_s_curve_constant_1 * (curr.x - pos_autocode_s_curve_constant_3)) +
            1, 2);
  ret.y = pos_autocode_s_curve_constant_1 * pos_autocode_s_curve_constant_2 * exp(
          -1.0 * pos_autocode_s_curve_constant_1 * (curr.y - pos_autocode_s_curve_constant_3)) /
         pow(exp(-1.0 * pos_autocode_s_curve_constant_1 * (curr.y - pos_autocode_s_curve_constant_3)) +
            1, 2);
  ret.z = pos_autocode_s_curve_constant_1 * pos_autocode_s_curve_constant_2 * exp(
          -1.0 * pos_autocode_s_curve_constant_1 * (curr.z - pos_autocode_s_curve_constant_3)) /
         pow(exp(-1.0 * pos_autocode_s_curve_constant_1 * (curr.z - pos_autocode_s_curve_constant_3)) +
            1, 2);

  normalize(ret);

  return ret;
}

double pos_autocode_get_max_speed() {
  return 125.0;
}

Vec3D att_autocode_calculate_lean_angle(PosOutputData input_waypoint) {
  Vec3D direction_euler = quat2vec(input_waypoint.rotation);

  // Make sure none of the waypoints are above the maximum climb rate
  if (direction_euler.x >= ATT_MAX_ROLL_ANGLE)
    direction_euler.x = ATT_MAX_ROLL_ANGLE;
  if (direction_euler.y >= ATT_MAX_PITCH_ANGLE)
    direction_euler.y = ATT_MAX_PITCH_ANGLE;
  if (direction_euler.z >= ATT_MAX_YAW_ANGLE)
    direction_euler.z = ATT_MAX_YAW_ANGLE;

  return direction_euler;
}

void servo_autocode_servo_move(PosOutputData input_waypoint) {
  cout << "servo movement to (" << input_waypoint.position.x << ", ";
  cout << input_waypoint.position.y << ", " << input_waypoint.position.z;
  cout << ")" << endl;
}