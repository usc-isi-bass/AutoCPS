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
    # Generic systems are arbitraily large
    "system": [],
    # Set max size of a rover to dimensions of Perseverance
    "rover": [2.9, 2.7, 2.2],
    # Set max size of a plane to a Boeing 747
    "plane": [76.3, 68.4, 19.4],
    # Set max size of a helicopter to a CH-47
    "helicopter": [30.2, 3.8, 5.7],
    # Set max size of a rocket to a Saturn V
    "rocket": [10.1, 10.1, 363.0],
    # Set max size of a submarine to an Ohio-class
    "submarine": [170, 13, 10.8]
}

# Mass limits will be porportional to dimensions
density_limits = {
    # Generic systems are arbitraily large
    "system": [],
    # Mars rovers are at around 116.1kg/m^3
    "rover": 125,
    # MTOW density of a Boeing 747-8 is at about 13.1kg/m^3
    "plane": 15,
    # MTOW density of a CH-47 is around 37.5kg/m^3
    "helicopter": 40,
    # Density of a fully loaded Saturn V is at 80.1kg/m^3
    "rocket": 85,
    # Density of a submerged Ohio-class is at 785.6kg/m^3
    "submarine": 800
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
        self.software = SoftwareSystem(self.type, sigmoid=1)

    # Randomly generate dimensions based on limits
    def generate_dimensions(self, dim=[-1.0, -1.0, -1.0], mass=-1):
        if dim[0] <= 0 or dim[1] <= 0 or dim[2] <= 0:
            x = Decimal(random.uniform(0, dim_limits[self.type][0]))
            y = Decimal(random.uniform(0, dim_limits[self.type][1]))
            z = Decimal(random.uniform(0, dim_limits[self.type][2]))
            self.dimensions = [x, y, z]
        else:
            self.dimensions = dim

        # Limit checking for dimensions
        if self.dimensions[0] > dim_limits[self.type][0]:
            self.dimensions[0] = dim_limits[self.type][0]
        if self.dimensions[1] > dim_limits[self.type][1]:
            self.dimensions[1] = dim_limits[self.type][1]
        if self.dimensions[2] > dim_limits[self.type][2]:
            self.dimensions[2] = dim_limits[self.type][2]

        vol = self.dimensions[0] * self.dimensions[1] * self.dimensions[2]

        # Volume * random density
        if mass == -1:
            density = Decimal(random.uniform(0, density_limits[self.type]))
            self.mass = density * vol
        elif mass > density_limits[self.type] * vol:
            self.mass = density_limits[self.type] * vol
        else:
            self.mass = mass

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
    # Only control surface for rovers are motors
    motor_locations = []

    def __init__(self):
        super().__init__(system_type='rover')

    # Add a new motor in one of the octants
    def add_motor(self, octant=[0, 0, 0]):
        x = Decimal()
        y = Decimal()
        z = Decimal()
        speed = Decimal()
        self.motor_locations.append([x, y, z, speed])


# Class with helicopter-specific attributes
class Helicopter(PhysicalSystem):
    rotor_locations = []  # Only control surface for helicopters are rotors

    def __init__(self):
        super().__init__(system_type='helicopter')

    # Add a new rotor in one of the octants
    def add_rotor(self, octant=[0, 0, 0]):
        x = Decimal()
        y = Decimal()
        z = Decimal()
        thrust = Decimal()
        self.rotor_locations.append([x, y, z, thrust])


# Class with plane-specific attributes
class Plane(PhysicalSystem):
    engine_locations = []
    stall_speed = Decimal()  # Stall speed in level flight

    def __init__(self):
        super().__init__(system_type='plane')

    # Add a new engine in one of the octants
    def add_rotor(self, octant=[0, 0, 0]):
        x = Decimal()
        y = Decimal()
        z = Decimal()
        self.engine_locations.append([x, y, z])


# Class with rocket-specific attributes
class Rocket(PhysicalSystem):
    i_sp = Decimal()       # Specific impulse
    fuel_load = Decimal()  # Max propellant
    mass_flow = Decimal()  # Mass flow rate out of nozzle

    def __init__(self):
        super().__init__(system_type='rocket')


# Class with submarine-specific attributes
class Submarine(PhysicalSystem):
    # TODO: implement

    def __init__(self):
        super().__init__(system_type='submarine')
