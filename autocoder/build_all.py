#!/usr/bin/env python3

# Build all possible FSWs given a set of inputs

import argparse
import json
import tempfile
import os
import shutil
import subprocess

from physical_systems import Helicopter, Plane, Rocket, Rover, PhysicalSystem
from code_generation import CodeGeneration

parser = argparse.ArgumentParser(
    description='Generate all possible random FSWs.')


# Run autocoder for every combination of array elements
def main():
    args = parser.parse_args()

    # Create tempdir and copy base FSW code
    tempdir = tempfile.mkdtemp(prefix='autocps_fsw.')
    shutil.copytree('fsw', os.path.join(tempdir, 'fsw'))

    print('Building FSW in {}...\n'.format(tempdir))

    # Generate physical system
    physical_system = Rover()

    physical_system.generate_dimensions()
    physical_system.generate_software_system()

    autocode = CodeGeneration()
    autocode.generate(physical_system)
    del autocode

    print('System dimensions: {}\n'.format(physical_system.dimensions))

    print('System mass: {}\n'.format(physical_system.mass))

    print('S-curve function: {}\n'.format(physical_system.software.sigmoid))

    print('Fitter function: {}\n'.format(
        physical_system.software.curve_fitter))

    shutil.copy(os.path.join('output', 'autocode.cpp'),
                os.path.join(tempdir, 'fsw'))
    shutil.copy(os.path.join('output', 'params.h'),
                os.path.join(tempdir, 'fsw'))

    shutil.rmtree('output')

    print('Building CMake projects...\n')

    with open(os.path.join(tempdir, 'fsw', 'CMakePresets.json')) as preset_file:
        cmake_presets = json.load(preset_file)

        for preset in cmake_presets['configurePresets']:
            print('Building CMake preset {}...\n'.format(preset['name']))
            build_dir = os.path.join(tempdir,
                                     'build-{}'.format(preset['name']))
            os.mkdir(build_dir)

            subprocess.run([
                'cmake', '-S{}'.format(os.path.join(tempdir, 'fsw')),
                '--preset={}'.format(preset['name'])
            ],
                           cwd=build_dir)

            subprocess.run(['make'], cwd=build_dir)

    print('\n\nProjects built!\n')


if __name__ == "__main__":
    main()
