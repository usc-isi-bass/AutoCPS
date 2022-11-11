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
import multiprocessing

from physical_systems import Helicopter, Plane, Rocket, Rover, PhysicalSystem
from code_generation import CodeGeneration

parser = argparse.ArgumentParser(
    description='Generate all possible random FSWs.')
parser.add_argument("config_file", help="configuration file in JSON format")
parser.add_argument("--config_limit", type=int, help="Place a limit on the number of configurations to generate")
parser.add_argument("--workers", default=1, type=int, help="The number of processes to use when building.")


class AutocoderWorker:
    config_entry = dict()
    build_number = -1

    def __init__(self, config_entry, build_number):
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
        report = AutocoderWorkerReport(tempdir)

        with open(os.path.join(output_temp_dir, 'CMakePresets.json')) as preset_file:
            cmake_presets = json.load(preset_file)

            for preset in cmake_presets['configurePresets']:
                print('[{}] Building CMake preset {}...'.format(self.build_number, preset['name']))
                build_dir = os.path.join(tempdir,
                                         'build-{}'.format(preset['name']))
                os.mkdir(build_dir)

                p = subprocess.run([
                    'cmake', '-S{}'.format(os.path.join(tempdir, 'fsw')),
                    '--preset={}'.format(preset['name'])
                ],
                               stdout=subprocess.DEVNULL,
                               stderr=subprocess.PIPE,
                               cwd=build_dir)
                if p.returncode != 0:
                    report.set_cmake_err(p.stderr)

                p = subprocess.run(['make'],
                               stdout=subprocess.DEVNULL,
                               stderr=subprocess.PIPE,
                               cwd=build_dir)
                if p.returncode != 0:
                    report.set_make_err(p.stderr)

        print('[{}] Projects built in {} !'.format(self.build_number, tempdir))

        return report
class AutocoderWorkerReport:

    def __init__(self, dir_used):
        self.dir_used = dir_used
        self.cmake_err = None
        self.make_err = None

    def set_cmake_err(self, err):
        self.cmake_err = err

    def set_make_err(self, err):
        self.make_err = err


def run_worker(args):
    config_entry, config_id = args
    worker = AutocoderWorker(config_entry, config_id)
    return worker.run()


# Run autocoder for every combination of config elements
def main():
    args = parser.parse_args()
    config_limit = args.config_limit
    nworkers = args.workers

    build_config = {}
    with open(args.config_file) as config_file:
        build_config = json.load(config_file)

    # Create all possible permutations of configuration entries
    configs = []
    for config_id, config_entry in enumerate((dict(zip(build_config['software'].keys(), values))
                         for values in itertools.product(
                             *build_config['software'].values()))):
        if config_limit is not None and config_id >= config_limit:
            break
        configs.append((config_entry, config_id))

    reports = []
    num_configs = len(configs)
    with multiprocessing.Pool(nworkers) as pool:
        for i, dir_used in enumerate(pool.imap_unordered(run_worker, configs)):
            print("COMPLETED: {}/{}".format(i + 1, num_configs))
            reports.append(dir_used)

    err_reports = []
    print("Build directories:")
    for report in reports:
        print(report.dir_used)
        if report.cmake_err is not None or report.make_err is not None:
            err_reports.append(report)
    if len(err_reports) > 0:
        print("Build errors: ({})".format(len(err_reports)))
        for report in err_reports:
            print("DIR: {}".format(report.dir_used))
            print("  cmake: {}".format(report.cmake_err))
            print("  make: {}".format(report.make_err))



if __name__ == "__main__":
    main()
