#!/usr/bin/env python3

### Build all possible FSWs given a set of inputs

import argparse
import tempfile
import os
import shutil
import subprocess
import sys

from physical_systems import Helicopter, Plane, Rocket, Rover, PhysicalSystem
from software_systems import SoftwareSystem
from code_generation import CodeGeneration

# TODO: more compiler settings
compile_config = dict(os.environ)
compile_config['CC'] = 'clang'
compile_config['CXX'] = 'clang++'

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

    print('Building CMake projects...\n')
    os.makedirs(os.path.join(tempdir, 'build-clang'))
    os.makedirs(os.path.join(tempdir, 'build-no-opt'))
    os.makedirs(os.path.join(tempdir, 'build-gcc'))

    subprocess.run([
        'cmake', '-S{}'.format(os.path.join(tempdir, 'fsw')),
        '--preset=clang-opt'
    ],
                   cwd=os.path.join(tempdir, 'build-clang'))
    subprocess.run([
        'cmake', '-S{}'.format(os.path.join(tempdir, 'fsw')),
        '--preset=clang-no-opt'
    ],
                   cwd=os.path.join(tempdir, 'build-no-opt'))
    subprocess.run([
        'cmake', '-S{}'.format(os.path.join(tempdir, 'fsw')),
        '--preset=gcc-opt'
    ],
                   cwd=os.path.join(tempdir, 'build-gcc'))

    subprocess.run(['make'], cwd=os.path.join(tempdir, 'build-clang'))
    subprocess.run(['make'], cwd=os.path.join(tempdir, 'build-no-opt'))
    subprocess.run(['make'], cwd=os.path.join(tempdir, 'build-gcc'))


if __name__ == "__main__":
    main()
