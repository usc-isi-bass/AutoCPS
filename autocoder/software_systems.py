# This .py contains all the information about the flight controller needed for
# autocoding the FSW controller

import random
from decimal import Decimal
from sympy import *

# A set of sigmoid functions to choose from
x, a, b = symbols('x a b')
sigmoids = [(b + exp(-1 * x)) ** (-1 * a), 
            a * tanh(x) + b,
            a * atan(x) + b,
            x / (1 + abs(x) ** a) ** (-1 * b)]


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

    # Sigmoid function to use
    sigmoid = Object()

    c_1_init = Object()
    c_2_init = Object()
    c_3_init = Object()

    s_curve_calc = ''
    curve_fit_calc = ''
    lean_angle_calc = ''
    max_speed_calc = ''

    # Constructor and assigning a sigmoid curve
    def __init__(self, system_type, sigmoid=-1):
        type = system_type
        if sigmoid == -1:
            this.sigmoid = random.choice(sigmoids)
        else:
            this.sigmoid = sigmoid

    # Generate a calculation for lean angles
    def generate_lean_angles(self):
        lean_angle_calc += '  Vec3D direction_euler = quat2vec(input_waypoint.rotation);\n'
        lean_angle_calc += ''

        # Basic limit checking
        lean_angle_calc += '  if (direction_euler.x >= ATT_MAX_ROLL_ANGLE) direction_euler.x = ATT_MAX_ROLL_ANGLE;\n'
        lean_angle_calc += '  if (direction_euler.y >= ATT_MAX_PITCH_ANGLE) direction_euler.y = ATT_MAX_PITCH_ANGLE;\n'
        lean_angle_calc += '  if (direction_euler.z >= ATT_MAX_YAW_ANGLE) direction_euler.z = ATT_MAX_YAW_ANGLE;\n\n'

        lean_angle_calc += '  return direction_euler;\n'

    # Generate a calculation for max speed
    def generate_max_speed(self, max_speed):
        max_speed_calc += '  double max_speed = {};\n'.format(max_speed)

        # Check for stall speed if plane
        if system_type == 'plane':
            max_speed_calc += '  double stall_speed = STALL_SPEED / sqrt(cos(direction_euler.x));\n'
            max_speed_calc += '  if (stall_speed > max_speed) return stall_speed;\n'

    def generate_s_curve_nav(self):
        derv = ccode(diff(sigmoid, x))

        for var in ['x', 'y', 'z']:
            s_curve_calc += 'ret.' + var + ' = '

            # Replace a and x with required variables
            to_add = str(derv).replace('x', var)

            to_add = str(derv).replace('a', 'pos_autocode_s_curve_constant_{}_1'.format(var))
            to_add = str(derv).replace('b', 'pos_autocode_s_curve_constant_{}_2'.format(var))

            s_curve_calc += to_add + ';\n'

    def generate_curve_fitter(self):
        pass
