#include "imu.h"

std::shared_ptr<AXIStream> imu_input_st, imu_output_st;

Vec3D imu_current_position;

// Recieve data from AXI stream
inline IMUInputData imu_receive_axi_stream() {
  IMUInputData input_data;
  AXIToken input;

  // Recieve linear velocity
  input = imu_input_st->get();
  input_data.linear = input.output_vec3d();

  // Recieve rotational velocity
  input = imu_input_st->get();
  input_data.rotational = input.output_vec3d();

  // Recieve GPS satellite locations
  input = imu_input_st->get();
  input_data.gps_satellite_a = input.output_vec3d();
  input = imu_input_st->get();
  input_data.gps_satellite_b = input.output_vec3d();
  input = imu_input_st->get();
  input_data.gps_satellite_c = input.output_vec3d();

  // Recieve GPS satellite distances
  input = imu_input_st->get();
  input_data.gps_distance_a = input.output_double();
  input = imu_input_st->get();
  input_data.gps_distance_b = input.output_double();
  input = imu_input_st->get();
  input_data.gps_distance_c = input.output_double();

  return input_data;
}

// Send data through AXI Stream
inline void imu_send_axi_stream(const IMUOutputData output_data) {
  AXIToken output_token;

  // Send linear acceleration
  output_token.input_quart(output_data.linear_accel);
  imu_output_st->push(output_token);

  // Send rotational acceleration
  output_token.input_quart(output_data.linear_accel);
  imu_output_st->push(output_token);

  // Send location
  output_token.input_vec3d(output_data.location);
  imu_output_st->push(output_token);

  // Send orientation
  output_token.input_quart(output_data.orientation);
  imu_output_st->push(output_token);
}

// Find new location with GPS
inline Vec3D imu_calculate_new_location_gps(const IMUInputData input_data) {

}

// Find new location with inertial navigation
inline Vec3D imu_calculate_new_location_inertial(const IMUInputData input_data) {

}

// Find new location with linear acceleration
inline Vec3D imu_calculate_new_linear_accel(const IMUInputData input_data) {

}

// Find new location with angular acceleration
inline Vec3D imu_calculate_new_angular_accel(const IMUInputData input_data) {
  
}

// Init IMU initial location (only used for inertial navigation)
void imu_init_location(double x, double y, double z) {
  imu_current_position.x = x;
  imu_current_position.y = y;
  imu_current_position.z = z;
}

// Main loop of IMU unit, continuously runs when called by startup script
void imu_main_loop(std::shared_ptr<AXIStream> input_st,
                   std::shared_ptr<AXIStream> output_st) {
  IMUOutputData output;
  imu_input_st = input_st;
  imu_output_st = output_st;

  // Recieve data from the IMU
  IMUInputData input_data = imu_receive_axi_stream();

  // Calculate new linear info
  Vec3D new_linear_accel = imu_calculate_new_linear_accel(input_data);
  Vec3D new_angular_accel = imu_calculate_new_angular_accel(input_data);
  Vec3D new_location = imu_calculate_new_location_gps(input_data);

  // Save it to output data
  output.linear_accel = convert_to_quarternion(new_linear_accel);
  output.angular_accel = convert_to_quarternion(new_angular_accel);
  output.location = new_location;

  // Send it to output stream
  imu_send_axi_stream(output);
}
