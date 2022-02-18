#!/usr/bin/env python3

# Build all possible FSWs given a set of inputs

import argparse
import itertools
import json
import tempfile
import os
import shutil
import subprocess
import sympy

from physical_systems import Helicopter, Plane, Rocket, Rover, PhysicalSystem
from code_generation import CodeGeneration

parser = argparse.ArgumentParser(
    description='Generate all possible random FSWs.')
parser.add_argument("config_file", help="configuration file in JSON format")


# Run autocoder for one configuration
def autocoder(config_entry):
    # Create tempdir and copy base FSW code
    tempdir = tempfile.mkdtemp(prefix='autocps_fsw.')
    shutil.copytree('fsw', os.path.join(tempdir, 'fsw'))

    print('Building FSW in {} ...\n'.format(tempdir))

    with open(os.path.join(tempdir, 'config.json'), 'w') as config_file:
        config_file.write(json.dumps(config_entry, indent=2))

    print(config_entry)

    # Generate rover configs
    physical_system = Rover()
    physical_system.generate_dimensions()
    physical_system.generate_software_system()

    # Overwrite with config entry
    physical_system.software.cycles_hz = config_entry['cycles_hz']
    physical_system.software.jpl_quaternion = config_entry['jpl_quaternion']
    physical_system.software.sigmoid = sympy.simplify(config_entry['sigmoids'])
    physical_system.software.curve_fitter = sympy.simplify(config_entry['curve_fitters'])
    physical_system.software.c_1_init = config_entry['c_1_init']
    physical_system.software.c_2_init = config_entry['c_2_init']
    physical_system.software.pi_calculation = config_entry['pi_calculation']
    physical_system.software.autonav_enable = config_entry['autonav_enable']
    physical_system.software.imu_enable = config_entry['imu_enable']
    physical_system.software.kalman_enable = config_entry['kalman_enable']
    physical_system.software.sensor_enable = config_entry['sensor_enable']

    # Generate code
    autocode = CodeGeneration()
    autocode.generate(physical_system)
    del autocode

    # Copy autocode over
    shutil.copy(os.path.join('output', 'autocode.cpp'),
                os.path.join(tempdir, 'fsw'))
    shutil.copy(os.path.join('output', 'params.h'),
                os.path.join(tempdir, 'fsw'))

    shutil.rmtree('output')

    print('Building CMake projects...\n')

    with open(os.path.join(tempdir, 'fsw',
                           'CMakePresets.json')) as preset_file:
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

    return tempdir


# Run autocoder for every combination of config elements
def main():
    args = parser.parse_args()

    build_config = {}
    with open(args.config_file) as config_file:
        build_config = json.load(config_file)

    # Create all possible permutations of configuration entries
    dirs_used = []
    for config_entry in (dict(zip(build_config['software'].keys(), values))
                         for values in itertools.product(
                             *build_config['software'].values())):
        dirs_used.append(autocoder(config_entry))

    # Print out all generated FSW directories
    print(dirs_used)


if __name__ == "__main__":
    main()
