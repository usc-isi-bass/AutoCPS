#!/usr/bin/env python3
import argparse
import os


from physical_systems import PhysicalSystem

parser = argparse.ArgumentParser(description='Generate a C project with a'
                                 'random FSW.')
parser.add_argument('--type', nargs=1, dest='vehicle_type', default=['rover'],
                    help='vehicle type (default=rover)')


# Run autocoder CLI
def main():
    args = parser.parse_args()

    # Generate physical system
    physical_system = PhysicalSystem(args.vehicle_type[0])
    physical_system.generate_dimensions()

    print(physical_system.dimensions)


if __name__ == "__main__":
    main()
