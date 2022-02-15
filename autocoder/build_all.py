#!/usr/bin/env python3

### Build all possible FSWs given a set of inputs

import argparse
import tempfile
import os
import shutil
import sys

from physical_systems import Helicopter, Plane, Rocket, Rover, PhysicalSystem
from software_systems import SoftwareSystem
from code_generation import CodeGeneration


parser = argparse.ArgumentParser(description='Generate all possible random FSWs.')

# Run autocoder for every combination of array elements
def main():
    args = parser.parse_args()

    # Create tempdir and copy base FSW code
    tempdir = tempfile.mkdtemp(prefix='autocps_fsw')
    shutil.copytree('fsw', os.path.join(tempdir, 'fsw')) 

    # Generate physical system
    physical_system = Rover()

    physical_system.generate_dimensions()
    physical_system.generate_software_system()

    autocode = CodeGeneration()
    autocode.generate(physical_system)

    print('System dimensions: {}'.format(physical_system.dimensions))

    print('\nSystem mass: {}'.format(physical_system.mass))

    print('\nS-curve function: {}'.format(physical_system.software.sigmoid))

    print('\nFitter function: {}'.format(physical_system.software.curve_fitter))


if __name__ == "__main__":
    main()
