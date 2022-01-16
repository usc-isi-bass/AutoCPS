# This .py contains all the information about the flight controller needed for
# autocoding the FSW controller

import random
from decimal import Decimal

# Base class for all systems
class SoftwareSystem:
  # Number of FSW cycles per loop, assuming ~120Hz
  cycles_hz = 120

  # Definition for Pi
  pi_calculation = 'acos(-1.0)'

  # Whether to use JPL quaternion standard
  jpl_quaternion = True

