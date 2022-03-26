# Flight Software Autocoder

This autocoder is designed as a Python library so it can be easily integrated
into other projects and provides fine tuning that would be cumbersome to do with
a command line. We also provide a simple CLI interface for the autocoder with a
much smaller space of possible generated code, which can be run with
`autocoder.py`. To generate every FSW within a problem space given a config
file, use the `build_all.py` file.

## Requirements

`sympy` is used for some mathematics, but aside from that any relatively modern
Python 3 should be enough.

## `build_all.py`

`build_all.py` uses the `fsw/CMakePresets.json` file and the `build_config.json`
file to generate different implementations of the FSW. The `build_config.json`
file lists out different available settings for the FSW, which can be modified
as needed. More compiler presets can also be added in the `CMakePresets.json`
file, and `build_all.py` will automatically run them as needed.

The script will generate one root directory for each semantically different
file, which will include the following files:

*`config.json` - Corresponding attributes used to generate the code. This has
the same layout as the `build_config.json` file, but will contain the
array element used to generate the code for each entry

*`fsw` - source files including autocoded bits for the FSW

*`build-*` - build directories containing binaries for given compiler preset

