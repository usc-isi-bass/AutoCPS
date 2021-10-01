# This class contains all the information about the physical object needed for
# generating the controller software

import random
from decimal import Decimal

# Add dimension limits for each vehicle
dim_limits = {
    # Set max size of a rover to dimensions of Perseverance
    "rover": [2.9, 2.7, 2.2],
    # Set max size of a plane to a Boeing 747-8
    "plane": [76.3, 68.4, 19.4],
    # Set max size of a helicopter to a CH-47
    "helicopter": [30.2, 3.8, 5.7],
    # Set max size of a missile to a Saturn V
    "missile": [10.1, 10.1, 363.0],
    # Set max size of a submarine to a Seawolf-class submarine
    "submarine": [138.0, 10.9, 12.1]
}

# Mass limits will be porportional to dimensions
mass_limits = {
    # Rover denser than 10kg/cm^3 would be weird
    "rover": lambda x, y, z: x * y * z * 10,
    # TODO: plane density
    "plane": lambda x, y, z: x * y * z,
    # TODO: helicopter density
    "helicopter": lambda x, y, z: x * y * z,
    # TODO: missile density
    "missile": lambda x, y, z: x * y * z,
    # Submarine cannot be denser than water
    "submarine": lambda x, y, z: x * y * z
}


# Base class for all systems
class PhysicalSystem:
    # The system is approximately a rectangular prisim
    dimensions = [Decimal(), Decimal(), Decimal()]

    # Auto-generate mass from dimensions?
    mass = Decimal()

    # List of locations for sensors, add with add_sensor method
    sensor_locations = []

    # Default type is rover, we can change to different types
    type = 'rover'

    # Constructor
    def PhysicalSystem(self, system_type='rover'):
        self.type = system_type

    # Randomly generate dimensions based on limits
    def generate_dimensions(self, lower_limit=[0.0, 0.0, 0.0],
                            upper_limit=[100.0, 100.0, 100.0]):
        x = Decimal(random.uniform(upper_limit[0], lower_limit[0]))
        y = Decimal(random.uniform(upper_limit[1], lower_limit[1]))
        z = Decimal(random.uniform(upper_limit[2], lower_limit[2]))
        self.dimensions = [x, y, z]

    # Choose to add a sensor in a random octant of the space
    def add_sensor(self, octant=[0, 0]):
        new_location = [Decimal(), Decimal(), Decimal()]
        self.sensor_locations.push(new_location)


# Class with rover-specific attributes
class Rover(PhysicalSystem):
    pass


# Class with plane-specific attributes
class Plane(PhysicalSystem):
    pass


# Class with helicopter-specific attributes
class Helicopter(PhysicalSystem):
    pass


# Class with missile-specific attributes
class Missile(PhysicalSystem):
    pass


# Class with submarine-specific attributes
class Submarine(PhysicalSystem):
    pass
