#include "imu.h"
#include "params.h"

std::shared_ptr<AXIStream> imu_input_st, imu_output_st;

Vec3D imu_current_position_linear, imu_current_velocity_linear;
Quarternion imu_current_position_angular, imu_current_velocity_angular;

// Recieve data from AXI stream
inline IMUInputData imu_receive_axi_stream() {
  IMUInputData input_data;
  AXIToken input;

  // Recieve sensor location
  input = imu_input_st->get();
  input_data.sensor_location = input.output_vec3d();

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

  // Send velocities
  output_token.input_quart(output_data.linear_velocity);
  imu_output_st->push(output_token);
  output_token.input_quart(output_data.angular_velocity);
  imu_output_st->push(output_token);

  // Send accelerations
  output_token.input_quart(output_data.linear_accel);
  imu_output_st->push(output_token);
  output_token.input_quart(output_data.angular_accel);
  imu_output_st->push(output_token);

  // Send location
  output_token.input_vec3d(output_data.location);
  imu_output_st->push(output_token);

  // Send orientation
  output_token.input_quart(output_data.orientation);
  imu_output_st->push(output_token);
}

// Find new location with GPS
inline Vec3D imu_calculate_new_location_gps(const Vec3D input_vel) {
  
}

// Find new location with inertial navigation
inline Vec3D imu_calculate_new_location_inertial(const Vec3D input_vel) {


  imu_current_position_linear = input_vel;
}

// Find new location with linear acceleration
inline Vec3D imu_calculate_new_linear_vel(const Vec3D input_accel) {
  // Add delta-t times translational velocity to imu_current_velocity

  imu_current_velocity_linear = input_accel;
}

// Find new location with angular acceleration
inline Vec3D imu_calculate_new_angular_vel(const Vec3D input_accel) {
  // Add delta-t times rotational velocity to imu_current_velocity
  

  imu_current_velocity_linear = input_accel; 
}

// Init IMU initial location (only used for inertial navigation)
void imu_init_location(Vec3D position, Quarternion rotation) {
  imu_current_position_linear = position;

  imu_current_velocity_linear.x = 0;
  imu_current_velocity_linear.y = 0;
  imu_current_velocity_linear.z = 0;

  imu_current_position_angular = rotation;
}

// Main loop of IMU unit, continuously runs when called by startup script
void imu_main_loop(std::shared_ptr<AXIStream> input_st,
                   std::shared_ptr<AXIStream> output_st) {
  IMUOutputData output;
  IMUInputData input_data;
  Vec3D new_location, new_linear_velocity, new_angular_velocity;
  imu_input_st = input_st;
  imu_output_st = output_st;

  // Recieve data from the IMU
  input_data = imu_receive_axi_stream();

  // Calculate new linear info
  new_linear_velocity = imu_calculate_new_linear_vel(input_data.linear);
  new_angular_velocity = imu_calculate_new_angular_vel(input_data.rotational);

#ifdef IMU_USES_GPS
  new_location = imu_calculate_new_location_gps(input_data);
#else
  new_location = imu_calculate_new_location_inertial(input_data.linear);
#endif

  // Save it to output data
  output.linear_velocity = convert_to_quarternion(new_linear_velocity);
  output.angular_velocity = convert_to_quarternion(new_angular_velocity);
  output.linear_accel = convert_to_quarternion(input_data.linear);
  output.angular_accel = convert_to_quarternion(input_data.rotational);
  output.location = new_location;

  // Send it to output stream
  imu_send_axi_stream(output);
}
