# This .py contains all the information about the physical object needed for
# generating the controller software

# Octants are organized in [x, y, z] form, with each variable being either -1
# or 1. For example, the following describes one half of the space where z=1:
#
#  [-1, 1, 1] | [ 1, 1, 1]
# ------------+------------
#  [-1,-1, 1] | [ 1,-1, 1]

import random
from decimal import Decimal

from software_systems import SoftwareSystem

# Add dimensional limits for each vehicle, in meters
dim_limits = {
    # Set max size of a rover to dimensions of Perseverance
    "rover": [2.9, 2.7, 2.2],
    # Set max size of a plane to a Boeing 747
    "plane": [76.3, 68.4, 19.4],
    # Set max size of a helicopter to a CH-47
    "helicopter": [30.2, 3.8, 5.7],
    # Set max size of a rocket to a Saturn V
    "rocket": [10.1, 10.1, 363.0]
}

# Mass limits will be porportional to dimensions
density_limits = {
    # Rover denser than 150kg/m^3 would be weird
    # Mars rovers are at around 116.1kg/m^3
    "rover": 150,
    # TODO: plane density
    "plane": lambda x, y, z: x * y * z,
    # TODO: helicopter density
    "helicopter": lambda x, y, z: x * y * z,
    # TODO: rocket density
    "rocket": lambda x, y, z: x * y * z
}


# Base class for all systems
class PhysicalSystem:
    # The system is approximately a rectangular prisim
    dimensions = [Decimal(), Decimal(), Decimal()]

    # Auto-generate mass from dimensions?
    mass = Decimal()

    # List of locations for sensors, add with add_sensor method
    sensor_locations = []

    # Type of system this is
    type = 'system'

    # Configuration for software components
    software = SoftwareSystem(type)

    # Max system speed
    max_speed = Decimal()

    # Constructor
    def __init__(self, system_type='system'):
        self.type = system_type
        software = SoftwareSystem(self.type, sigmoid=1)

    # Randomly generate dimensions based on limits
    def generate_dimensions(self, lower_limit=[0.0, 0.0, 0.0],
                            upper_limit=[100.0, 100.0, 100.0]):
        x = Decimal(random.uniform(upper_limit[0], lower_limit[0]))
        y = Decimal(random.uniform(upper_limit[1], lower_limit[1]))
        z = Decimal(random.uniform(upper_limit[2], lower_limit[2]))
        self.dimensions = [x, y, z]

    # Choose to add a sensor in a random octant of the space
    def add_sensor(self, octant=[0, 0, 0]):
        new_location = [Decimal(), Decimal(), Decimal()]
        self.sensor_locations.push(new_location)

    # Generate software system
    def generate_software_system(self):
        self.software.generate_lean_angles(self.max_speed)
        self.software.generate_max_speed(self.max_speed)
        self.software.generate_s_curve_nav()
        self.software.generate_curve_fitter()


# Class with rover-specific attributes
class Rover(PhysicalSystem):
    type = 'rover'

    # Only control surface for rovers are motors
    motor_locations = []

    # Add a new motor in one of the octants
    def add_motor(self, octant=[0, 0, 0]):
        x = Decimal()
        y = Decimal()
        z = Decimal()
        speed = Decimal()
        self.motor_locations.append([x, y, z, speed])


# TODO: Class with helicopter-specific attributes
class Helicopter(PhysicalSystem):
    type = 'helicopter'

    rotor_locations = []  # Only control surface for helicopters are rotors

    # Add a new rotor in one of the octants
    def add_rotor(self, octant=[0, 0, 0]):
        x = Decimal()
        y = Decimal()
        z = Decimal()
        thrust = Decimal()
        self.rotor_locations.append([x, y, z, thrust])


# TODO: Class with plane-specific attributes
class Plane(PhysicalSystem):
    type = 'plane'

    engine_locations = []
    stall_speed = Decimal()  # Stall speed in level flight

    # Add a new engine in one of the octants
    def add_rotor(self, octant=[0, 0, 0]):
        x = Decimal()
        y = Decimal()
        z = Decimal()
        self.engine_locations.append([x, y, z])


# TODO: Class with rocket-specific attributes
class Rocket(PhysicalSystem):
    type = 'rocket'

    i_sp = Decimal()       # Specific impulse
    fuel_load = Decimal()  # Max propellant
    mass_flow = Decimal()  # Mass flow rate out of nozzle
