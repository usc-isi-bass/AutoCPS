#!/usr/bin/env python3

### Sample autocoder CLI

import argparse
import os

from physical_systems import Helicopter, Plane, Rocket, Rover
from software_systems import SoftwareSystem
from code_generation import CodeGeneration

parser = argparse.ArgumentParser(description='Generate a C project with a'
                                 'random FSW.')
parser.add_argument('--type', nargs=1, dest='vehicle_type', default=['rover'],
                    help='vehicle type (default=rover)')

# Run autocoder CLI
def main():
    args = parser.parse_args()

    # Generate physical system
    physical_system = Helicopter()
    physical_system.generate_dimensions()
    physical_system.generate_software_system()

    autocode = CodeGeneration()
    autocode.generate(physical_system)

    print(physical_system.dimensions)


if __name__ == "__main__":
    main()
