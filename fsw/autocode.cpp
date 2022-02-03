#include "autocode.h"

#include "params.h"
#include <cmath>
#include <iostream>

using namespace std;

// Constants for use with the S-curve functions
double pos_autocode_s_curve_constant_x_1 = -1;
double pos_autocode_s_curve_constant_x_2 = -1;
double pos_autocode_s_curve_constant_y_1 = -1;
double pos_autocode_s_curve_constant_y_2 = -1;
double pos_autocode_s_curve_constant_z_1 = -1;
double pos_autocode_s_curve_constant_z_2 = -1;

void seq_autocode_fit_s_curve(std::deque<SeqWaypoint> target) {
  Vec3D v_0, v_1;
  if (target.size() == 0) {
    return;
  } else if (target.size() > 1) {
    v_0 = target[0].position;
    v_1 = target[1].position;
  } else if (target.size() == 1) {
    v_0 = target[0].position;
    v_1 = v_0;
  }

  pos_autocode_s_curve_constant_x_1 = (1.0/100.0)*v_0.x + (1.0/100.0)*v_1.x;
  pos_autocode_s_curve_constant_x_2 = (1.0/100.0)*v_0.x + (1.0/100.0)*v_1.x;
  pos_autocode_s_curve_constant_y_1 = (1.0/100.0)*v_0.y + (1.0/100.0)*v_1.y;
  pos_autocode_s_curve_constant_y_2 = (1.0/100.0)*v_0.y + (1.0/100.0)*v_1.y;
  pos_autocode_s_curve_constant_z_1 = (1.0/100.0)*v_0.z + (1.0/100.0)*v_1.z;
  pos_autocode_s_curve_constant_z_2 = (1.0/100.0)*v_0.z + (1.0/100.0)*v_1.z;
}

Vec3D pos_autocode_s_curve_derivative(Vec3D curr,
                                      SeqWaypoint target) {
  Vec3D ret;

  ret.x = 0;
  ret.y = 0;
  ret.z = 0;

  normalize(ret);

  return ret;
}

double pos_autocode_get_max_speed() {
  double max_speed = 0;
}

Vec3D att_autocode_calculate_lean_angle(PosOutputData input_waypoint) {
  Vec3D direction_euler = quat2vec(input_waypoint.rotation);
  return direction_euler;
}

void servo_autocode_servo_move(PosOutputData input_waypoint) {
  cout << "servo movement to (" <<
     input_waypoint.position.x << ", " <<
     input_waypoint.position.y << ", " <<
     input_waypoint.position.z <<
     ")" << endl;
}
