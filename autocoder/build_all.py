#!/usr/bin/env python3

# Build all possible FSWs given a set of inputs

import argparse
import itertools
import json
import os
import shutil
import subprocess
import sympy
import tempfile
import threading

from physical_systems import Helicopter, Plane, Rocket, Rover, PhysicalSystem
from code_generation import CodeGeneration

parser = argparse.ArgumentParser(
    description='Generate all possible random FSWs.')
parser.add_argument("config_file", help="configuration file in JSON format")
dirs_used = []


class AutocoderThread(threading.Thread):
    config_entry = dict()
    build_number = -1

    def __init__(self, config_entry, build_number):
        threading.Thread.__init__(self)
        self.config_entry = config_entry
        self.build_number = build_number

    # Run autocoder for one configuration
    def run(self):
        # Create tempdir and copy base FSW code
        tempdir = tempfile.mkdtemp(prefix='autocps_fsw.')
        shutil.copytree('fsw', os.path.join(tempdir, 'fsw'))

        print('[{}] Building FSW in {} ...'.format(self.build_number, tempdir))

        with open(os.path.join(tempdir, 'config.json'), 'w') as config_file:
            config_file.write(json.dumps(self.config_entry, indent=2))

        # Generate rover configs
        physical_system = Rover()
        physical_system.generate_dimensions()
        physical_system.generate_software_system()

        # Overwrite with config entry
        physical_system.software.cycles_hz = self.config_entry['cycles_hz']
        physical_system.software.jpl_quaternion = self.config_entry['jpl_quaternion']
        physical_system.software.sigmoid = sympy.simplify(self.config_entry['sigmoids'])
        physical_system.software.curve_fitter = sympy.simplify(
            self.config_entry['curve_fitters'])
        physical_system.software.c_1_init = self.config_entry['c_1_init']
        physical_system.software.c_2_init = self.config_entry['c_2_init']
        physical_system.software.pi_calculation = self.config_entry['pi_calculation']
        physical_system.software.autonav_enable = self.config_entry['autonav_enable']
        physical_system.software.imu_enable = self.config_entry['imu_enable']
        physical_system.software.kalman_enable = self.config_entry['kalman_enable']
        physical_system.software.sensor_enable = self.config_entry['sensor_enable']

        # Generate code
        output_temp_dir = os.path.join(tempdir, 'fsw')
        autocode = CodeGeneration(output_dir=output_temp_dir)
        autocode.generate(physical_system)
        del autocode

        print('[{}] Building CMake projects...'.format(self.build_number))

        with open(os.path.join(output_temp_dir, 'CMakePresets.json')) as preset_file:
            cmake_presets = json.load(preset_file)

            for preset in cmake_presets['configurePresets']:
                print('[{}] Building CMake preset {}...'.format(self.build_number, preset['name']))
                build_dir = os.path.join(tempdir,
                                         'build-{}'.format(preset['name']))
                os.mkdir(build_dir)

                subprocess.run([
                    'cmake', '-S{}'.format(os.path.join(tempdir, 'fsw')),
                    '--preset={}'.format(preset['name'])
                ],
                               stdout=subprocess.DEVNULL,
                               stderr=subprocess.DEVNULL,
                               cwd=build_dir)

                subprocess.run(['make'],
                               stdout=subprocess.DEVNULL,
                               stderr=subprocess.DEVNULL,
                               cwd=build_dir)

        print('[{}] Projects built in {} !'.format(self.build_number, tempdir))

        dirs_used.append(tempdir)


# Run autocoder for every combination of config elements
def main():
    args = parser.parse_args()

    build_config = {}
    with open(args.config_file) as config_file:
        build_config = json.load(config_file)

    # Create all possible permutations of configuration entries
    threads = []
    config_id = -1
    for config_entry in (dict(zip(build_config['software'].keys(), values))
                         for values in itertools.product(
                             *build_config['software'].values())):
        config_id += 1
        threads.append(AutocoderThread(config_entry, config_id))

    for t in threads:
        t.start()

    for t in threads:
        t.join()

    # Print out all generated FSW directories
    print(dirs_used)


if __name__ == "__main__":
    main()
