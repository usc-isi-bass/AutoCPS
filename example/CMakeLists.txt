project(FakeFSW)

include_directories("../cspice/include")
find_library(CSPICE NAMES cspice.a PATHS "../cspice/lib")
find_library(CSUPPORT NAMES csupport.a PATHS "../cspice/lib")