#!/usr/bin/env python3

### Sample autocoder CLI

import argparse
import os

from physical_systems import Helicopter, Plane, Rocket, Rover, PhysicalSystem
from software_systems import SoftwareSystem
from code_generation import CodeGeneration

parser = argparse.ArgumentParser(description='Generate a C project with a'
                                 'random FSW.')
parser.add_argument('--type', nargs='?', dest='vehicle_type', default='rover',
                    help='vehicle type (default=rover)')

# Run autocoder CLI
def main():
    args = parser.parse_args()

    # Generate physical system
    physical_system = PhysicalSystem()

    if args.vehicle_type == 'rover':
        physical_system = Rover()
    elif args.vehicle_type == 'helicopter':
        physical_system = Helicopter()
    elif args.vehicle_type == 'plane':
        physical_system = Plane()
    elif args.vehicle_type == 'rocket':
        physical_system = Rocket()

    physical_system.generate_dimensions()
    physical_system.generate_software_system()

    autocode = CodeGeneration()
    autocode.generate(physical_system)

    print('System dimensions:')
    print(physical_system.dimensions)

    print('System mass:')
    print(physical_system.mass)


if __name__ == "__main__":
    main()
