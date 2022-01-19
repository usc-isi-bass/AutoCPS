# This .py contains all the information about the flight controller needed for
# autocoding the FSW controller

import random
from decimal import Decimal
from sympy import *

# Base class for all systems
class SoftwareSystem:
    # Type of system this is
    type = 'system'

    # Number of FSW cycles per loop, assuming ~120Hz
    cycles_hz = 120

    # Definition for Pi
    pi_calculation = 'acos(-1.0)'

    # Whether to use JPL quaternion standard
    jpl_quaternion = True

    # SymPy base for derivatives and stuff
    c_1, c_2, c_3 = symbols('c_1 c_2 c_3')

    c_1_init = ''
    c_2_init = ''
    c_3_init = ''

    s_curve_calc = ''
    lean_angle_calc = ''
    max_speed_calc = ''

    # Create 
    def __init__(self, system_type):
        type = system_type

    # Generate a calculation for lean angles
    def generate_lean_angles(self):
        lean_angle_calc += '  Vec3D direction_euler = quat2vec(input_waypoint.rotation);\n'
        lean_angle_calc += ''

        # Basic limit checking
        lean_angle_calc += '  if (direction_euler.x >= ATT_MAX_ROLL_ANGLE) direction_euler.x = ATT_MAX_ROLL_ANGLE;\n'
        lean_angle_calc += '  if (direction_euler.y >= ATT_MAX_PITCH_ANGLE) direction_euler.y = ATT_MAX_PITCH_ANGLE;\n'
        lean_angle_calc += '  if (direction_euler.z >= ATT_MAX_YAW_ANGLE) direction_euler.z = ATT_MAX_YAW_ANGLE;\n'

    # Generate a calculation for max speed
    def generate_max_speed(self, max_speed):
        max_speed_calc += '  double max_speed = {};\n'.format(max_speed)

        # Check for stall speed if plane
        if system_type == 'plane':
            max_speed_calc += '  double stall_speed = STALL_SPEED / sqrt(cos(direction_euler.x));\n'
            max_speed_calc += '  if (stall_speed > max_speed) return stall_speed;\n'

    def generate_kalman_filter(self):
        pass
