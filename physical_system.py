# This class contains all the information about the physical object needed for
# generating the controller software

import random
from decimal import Decimal


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
    def add_sensor(self, octant=[0,0]):
        new_location = [Decimal(), Decimal(), Decimal()]
        self.sensor_locations.push(new_location)
