import os


# Base class to generate an autocoded params.h and autocode.o
class CodeGeneration:
    # File objects to write to
    params_h = None
    autocode_c = None

    # Initialize by opening files
    def __init__(self, output_dir=-1):
        if output_dir == -1:
            output_dir = os.path.join(os.getcwd(), 'output')

        # Make output directory if needed
        try:
            os.mkdir(output_dir)
        except FileExistsError:
            pass

        self.params_h = open(os.path.join(output_dir, 'params.h'), 'w')
        self.autocode_c = open(os.path.join(output_dir, 'autocode.cpp'), 'w')

    # By closing files
    def __del__(self):
        self.params_h.close()
        self.autocode_c.close()

    def generate(self, system):
        self.generate_params(system)
        self.generate_autocode(system)

    def generate_params(self, system):
        self.params_h.write('/*\n')
        self.params_h.write(' * Common FSW parameters, autogenerated by Python\n')
        self.params_h.write(' */\n\n')
        self.params_h.write('#ifndef PARAMS_H\n')
        self.params_h.write('#define PARAMS_H\n\n')
        self.params_h.write('#include "datatypes.h"\n\n')
        self.params_h.write('#include <cmath>\n\n')
        self.params_h.write('enum SystemType {SYS_ROVER, SYS_PLANE, SYS_ROCKET, SYS_HELICOPTER};\n')

        self.params_h.write('const double mass = {};\n'.format(system.mass))
        self.params_h.write('const double dimensions[3] = {{ {}, {}, {} }};\n\n'.format(
            system.dimensions[0], system.dimensions[1], system.dimensions[2]))
        self.params_h.write('const SystemType fsw_system = ')

        if system.type == 'rover':
            self.params_h.write('SYS_ROVER;\n\n')
        elif system.type == 'plane':
            self.params_h.write('SYS_PLANE;\n\n')
        elif system.type == 'rocket':
            self.params_h.write('SYS_ROCKET;\n\n')
        elif system.type == 'helicopter':
            self.params_h.write('SYS_HELICOPTER;\n\n')

        if system.software.jpl_quaternion is True:
            self.params_h.write('#define JPL_QUATERNION\n\n')

        self.params_h.write('#define AUTONAV_ENABLE {}\n'.format(str(system.software.autonav_enable).lower()))
        self.params_h.write('#define IMU_ENABLE {}\n'.format(str(system.software.imu_enable).lower()))
        self.params_h.write('#define KALMAN_ENABLE {}\n'.format(str(system.software.kalman_enable).lower()))
        self.params_h.write('#define SENSOR_ENABLE {}\n\n'.format(str(system.software.sensor_enable).lower()))

        self.params_h.write('#define POS_MAX_ERROR ' + system.software.pi_calculation + '\n')
        self.params_h.write('#define SYS_PI ' + system.software.pi_calculation + '\n')
        self.params_h.write('#define CLOCK_TICKS_PER_SEC ' + str(system.software.cycles_hz) + '\n\n')

        self.params_h.write('#define ATT_MAX_ROLL_ANGLE ' + system.software.max_roll + '\n')
        self.params_h.write('#define ATT_MAX_PITCH_ANGLE ' + system.software.max_pitch + '\n')
        self.params_h.write('#define ATT_MAX_YAW_ANGLE ' + system.software.max_yaw + '\n\n')

        self.params_h.write('#define ATT_MAX_ROTATION_RATE ' + system.software.max_rotation + '\n')
        self.params_h.write('#define ATT_MAX_CLIMB_RATE ' + system.software.max_climb + '\n\n')

        self.params_h.write('#define MAX_SPEED {}\n\n'.format(system.max_speed))

        if system.type == 'helicopter':
            self.params_h.write('#define SYS_IS_HELICOPTER\n\n')
            self.params_h.write('#define NUM_PROPS {}\n'.format(len(system.rotor_locations)))

            self.params_h.write('const double PROPELLERS[NUM_PROPS][3] = {')
            for i in range(len(system.rotor_locations)):
                self.params_h.write('{ {}, {}, {} }'.format(system.rotor_locations[i][0],
                                                            system.rotor_locations[i][1],
                                                            system.rotor_locations[i][2]))
                if i != (len(system.rotor_locations) - 1):
                    self.params_h.write(', ')
            self.params_h.write('};\n')

            self.params_h.write('const double PROP_THRUSTS[NUM_PROPS] = {')
            for i in range(len(system.rotor_locations)):
                self.params_h.write('{}'.format(system.rotor_locations[i][3]))
                if i != (len(system.rotor_locations) - 1):
                    self.params_h.write(', ')
            self.params_h.write('};\n\n')

        elif system.type == 'plane':
            self.params_h.write('#define SYS_IS_PLANE\n\n')
            self.params_h.write('#define NUM_ENGINES {}\n'.format(len(system.engine_locations)))

            self.params_h.write('const double engines[NUM_ENGINES][3] = {')
            for i in range(len(system.engine_locations)):
                self.params_h.write('{ {}, {}, {} }'.format(system.engine_locations[i][0],
                                                            system.engine_locations[i][1],
                                                            system.engine_locations[i][2]))
                if i != (len(system.engine_locations) - 1):
                    self.params_h.write(', ')
            self.params_h.write('};\n')

            self.params_h.write('#define STALL_SPEED {}\n'.format(system.stall_speed))

        elif system.type == 'rover':
            self.params_h.write('#define SYS_IS_ROVER\n\n')
            self.params_h.write('#define NUM_MOTORS {}\n'.format(len(system.motor_locations)))

            self.params_h.write('const double motors[NUM_MOTORS][3] = {')
            for i in range(len(system.motor_locations)):
                self.params_h.write('{ {}, {}, {} }'.format(system.motor_locations[i][0],
                                                            system.motor_locations[i][1],
                                                            system.motor_locations[i][2]))
                if i != (len(system.motor_locations) - 1):
                    self.params_h.write(', ')
            self.params_h.write('};\n')

            self.params_h.write('const double motor_max_speeds[NUM_MOTORS] = {')
            for i in range(len(system.motor_locations)):
                self.params_h.write('{}'.format(system.motor_locations[i][3]))
                if i != (len(system.motor_locations) - 1):
                    self.params_h.write(', ')
            self.params_h.write('};\n\n')

        elif system.type == 'rocket':
            self.params_h.write('#define SYS_IS_ROCKET\n\n')
            self.params_h.write('const double i_sp = {};\n'.format(system.i_sp))
            self.params_h.write('const double max_fuel = {};\n'.format(system.fuel_load))
            self.params_h.write('const double mass_flow_rate = {};\n\n'.format(system.mass_flow))

        self.params_h.write('#endif\n')

    def generate_autocode(self, system):
        self.autocode_c.write('#include "autocode.h"\n\n')

        self.autocode_c.write('#include "params.h"\n')
        self.autocode_c.write('#include <cmath>\n')
        self.autocode_c.write('#include <iostream>\n\n')

        self.autocode_c.write('using namespace std;\n\n')

        self.autocode_c.write('// Constants for use with the S-curve functions\n')
        self.autocode_c.write('double pos_autocode_s_curve_constant_x_1 = {};\n'.format(system.software.c_1_init))
        self.autocode_c.write('double pos_autocode_s_curve_constant_x_2 = {};\n'.format(system.software.c_2_init))
        self.autocode_c.write('double pos_autocode_s_curve_constant_y_1 = {};\n'.format(system.software.c_1_init))
        self.autocode_c.write('double pos_autocode_s_curve_constant_y_2 = {};\n'.format(system.software.c_2_init))
        self.autocode_c.write('double pos_autocode_s_curve_constant_z_1 = {};\n'.format(system.software.c_1_init))
        self.autocode_c.write('double pos_autocode_s_curve_constant_z_2 = {};\n\n'.format(system.software.c_2_init))

        self.autocode_c.write('__attribute__((noinline)) double curve_fit_calc(double v_0, double v_1) {\n')
        self.autocode_c.write(system.software.curve_fit_calc)
        self.autocode_c.write('}\n\n')
        self.autocode_c.write('void seq_autocode_fit_s_curve(std::deque<SeqWaypoint> target) {\n')
        self.autocode_c.write( '  Vec3D v_0, v_1;\n')
        self.autocode_c.write( '  if (target.size() == 0) {\n')
        self.autocode_c.write( '    return;\n')
        self.autocode_c.write( '  } else if (target.size() > 1) {\n')
        self.autocode_c.write( '    v_0 = target[0].position;\n')
        self.autocode_c.write( '    v_1 = target[1].position;\n')
        self.autocode_c.write( '  } else if (target.size() == 1) {\n')
        self.autocode_c.write( '    v_0 = target[0].position;\n')
        self.autocode_c.write( '    v_1 = v_0;\n')
        self.autocode_c.write( '  }\n\n')
        for var in ['x', 'y', 'z']:
            # Replace a and x with required variables
            self.autocode_c.write('  pos_autocode_s_curve_constant_' + var + '_1 = ')
            self.autocode_c.write('curve_fit_calc(v_0.{}'.format(var) + ',v_1.{}'.format(var)+');\n')

            self.autocode_c.write('  pos_autocode_s_curve_constant_' + var + '_2 = ')
            self.autocode_c.write('curve_fit_calc(v_0.{}'.format(var) + ',v_1.{}'.format(var)+');\n')
        self.autocode_c.write('}\n\n')
        
        self.autocode_c.write('__attribute__((noinline)) double s_curve_calc(double x_0, double c_1, double c_2) {\n')
        self.autocode_c.write(system.software.s_curve_calc)
        self.autocode_c.write('}\n\n')

        self.autocode_c.write('Vec3D pos_autocode_s_curve_derivative(Vec3D curr,\n'
                              '                                      SeqWaypoint target) {\n')
        self.autocode_c.write('  Vec3D ret;\n\n')
        for var in ['x', 'y', 'z']:
            self.autocode_c.write(' ret.' + var + '= ')
            self.autocode_c.write('s_curve_calc(curr.{}'.format(var)+ ', pos_autocode_s_curve_constant_{}_1'.format(var))
            self.autocode_c.write(', pos_autocode_s_curve_constant_{}_2'.format(var)+');\n')
        self.autocode_c.write('  normalize(ret);\n\n')
        self.autocode_c.write('  return ret;\n')
        self.autocode_c.write('}\n\n')

        self.autocode_c.write('double pos_autocode_get_max_speed() {\n')
        self.autocode_c.write(system.software.max_speed_calc)
        self.autocode_c.write('}\n\n')

        self.autocode_c.write('Vec3D att_autocode_calculate_lean_angle'
                              '(PosOutputData input_waypoint) {\n')
        self.autocode_c.write(system.software.lean_angle_calc)
        self.autocode_c.write('}\n\n')

        # Use default servo autocoding for movement, useful for testing later
        self.autocode_c.write('void servo_autocode_servo_move(PosOutputData input_waypoint) {\n')
        self.autocode_c.write('  cout << "servo movement to (" <<\n'
                              '     input_waypoint.position.x << ", " <<\n'
                              '     input_waypoint.position.y << ", " <<\n'
                              '     input_waypoint.position.z <<\n'
                              '     ")" << endl;\n')
        self.autocode_c.write('}\n')
