// FSW stub that lets simulator interface with software 

#include "fsw_stub.h"

using namespace std;

// Stubbed function to generate data for the IMU
IMUInputData imu_stub_data_recieve_sensors() {
  IMUInputData data;
  Vec3D zero;

  // Set every field to zero
  zero.x = 0;
  zero.y = 0;
  zero.z = 0;
  data.rotational = zero;
  data.linear = zero;
  data.gps_satellite_a = zero;
  data.gps_satellite_b = zero;
  data.gps_satellite_c = zero;
  data.gps_distance_a = 0;
  data.gps_distance_b = 0;
  data.gps_distance_c = 0;

  return data;
}

// Stubbed function to send data to the IMU
void imu_stub_data_send(IMUInputData input_data, shared_ptr<AXIStream> input_stream) {
  AXIToken input_token;
  Vec3D input_vec3d;

  input_vec3d = input_data.linear;
  input_token.input_vec3d(input_vec3d);
  input_stream->push(input_token);

  input_vec3d = input_data.rotational;
  input_token.input_vec3d(input_vec3d);
  input_stream->push(input_token);

  input_vec3d = input_data.gps_satellite_a;
  input_token.input_vec3d(input_vec3d);
  input_stream->push(input_token);

  input_vec3d = input_data.gps_satellite_b;
  input_token.input_vec3d(input_vec3d);
  input_stream->push(input_token);

  input_vec3d = input_data.gps_satellite_c;
  input_token.input_vec3d(input_vec3d);
  input_stream->push(input_token);

  input_token.input_double(input_data.gps_distance_a);
  input_stream->push(input_token);

  input_token.input_double(input_data.gps_distance_b);
  input_stream->push(input_token);

  input_token.input_double(input_data.gps_distance_c);
  input_stream->push(input_token);
}
