# FakeFSW

Template of the FSW that fsw-autocoder will modify

## Base architecture

We divide the flight software into 10 modules that must be present on every
vehicle controller no matter the type of physical system it is. Each module can
be specifically adapted to their system, though all have some core functions
that can be reused.

```text
+-----------------------+
|                       |
|   +---------+    +----v----+
|   | seq     +----> autonav +--------------------------+
|   +----+----+    +---------+                          |
|        |                                              |
|        |                        +----------+    +-----v----+   +----------+
|        +--------------+---------> position +----> attitude +---> servo    |
|                       |         +----^-----+    +----------+   +----------+
+-----------------------+              |
|                       |              +--------+
|                       |              |        |
|   +---------+    +----+----+    +----+----+   |
|   | imu     +----> kalman  +----> ivp     |   |
|   +---------+    +----^----+    +----^----+   |
|                       |              |        |
|   +---------+         |              |        |
+---| sensor  +---------+--------------+--------+
    +---------+
```

Specifics on each module are discussed below.

### seq

The `seq` module stores sequences of actions to be done. This can reflect an
autopilot inputting new waypoints, or a controller sending in new directional
data to the system.

This code shouldn't change between implementations, since expressing waypoints
are more or less fixed and wouldn't be a significant data point.

### imu

The `imu` module recieves data from the inertial measurement unit or the GPS and
other related sensors. It then converts that data into direction and position
vectors. These vectors will then be sent to the `kalman` module described below.

While there may be difference communication methods between various IMUs, the
resultant vector would still be the same. Thus for our purposes this module will
only vary based on the number of sensors and their locations, but how the data
is recieved will remain the same. This should be a stubbed module for our use
case.

### sensor

The `sensor` module recieves data from sensors that don't directly provide
direction and position information, such as a timer or an antenna. These may not
need the Kalman Filter, so some of this data can make it to `ivp` without going
through `kalman`.

This module is similar to the IMU module in that the data sent in may vary based
on the location and type of sensors within the device, but communication methods
should not. This should be a stubbed module for our use case.

### kalman

The `kalman` module will provide a Kalman filter to even out the data from
`sensor` in case any of the sensors fail. The design of this module can also
differ based on the model used.

**Primary variations:**

* Initial state estimate
* Initial state covariance estimate

### autonav

The `autonav` module will contain optional automated additions to the input
sequence. This may include stabilization of a helicopter or plane, or obstacle
avoidance from a rover. The equations here are much more involved, and may also
include data from the `kalman` and `sensor` modules.

The design of this module will vary by the type of system being generated, or
could even be left unused. A general layout for a helicopter or plane stablizer
would look something like this:

```text
+---------+
| sensor  +---------------------------+
+---------+                           |
                                      |
+---------+   +---------------+   +---v---+   +---------------+   +----------+
| kalman  +---> curr_position +---> drift +---> correction    +---> position |
+---------+   +---------------+   +-------+   +----^----------+   +----------+
                                                   |
+---------+                                        |
| seq     +----------------------------------------+
+---------+
```

Drift calculation can vary in terms of the amount of error allowed, as well as
the .

A similar design for a rover would replace the drift calculation with an
obstacle calculation, resulting in something like this:

```text
+---------+
| sensor  +---------------------------+
+---------+                           |
                                      |
+--------+    +---------------+   +---v-------+   +------------+   +----------+
| kalman +----> curr_position +---> obstacles +---> correction +---> position |
+--------+    +---------------+   +-----------+   +----^-------+   +----------+
                                                       |
+---------+                                            |
| seq     +--------------------------------------------+
+---------+
```

The only major step that should be varied is the correction equation. This takes
as input the obstacles or the drift, as well as the next waypoint that needs to
be met. It will then present an offset to `position` which will take this
adjustment into account during the calculation.

**Primary variations:**

* *TODO: find stuff here*

### ivp

Often, the data from the sensors are in the frame of reference of the sensor and
not that of the entire system. The `ivp` module will use inertial vector
propagation to convert input vectors into the correct reference frame as needed.

Since there are only so many ways to convert a vector from one frame to another,
this can also be fixed between the different versions.

### position

The `position` module unifies all inputs from the controller (seq) as well as
the input data from the ivp and kalman modules. It uses this data to select the
next waypoint to move to.

The physical system will have different limits to the space of possible
waypoints that could be chosen. For example, a plane needs a minimum thrust to
ensure that the plane won't stall, and a rover can't go through very steep
hills. These limits can be written as part of the configuration file and checked
with inlined functions.

**Primary variations:**

* Different S-curve functions to do navigation with
* Different heuristics to choose the waypoints from (e.g. must we hit the
waypoints or just pass by them?)
* Limits on the behavior of the physical system

### attitude

The `attitude` module gets inputs from `position` and `autonav`. It uses this
data to control the next direction and heading for the physical system. This is
the most significant module for variations that can be added.

**Primary variations:**

* Limits on the available angles of rotation / roll-pitch-yaw (extension of the
same limits in `position`)

### servo

The `servo` module contains code to interface with the control surfaces of the
physical system. This requires knowledge of the design of the physical system.
Communication to actual servos from this module should be stubbed for our use
case.

**Primary variations:**

* Different sets/locations of servos/hydraulics/motors
* Each servo/hydraulics/motors providing a different amount + scaling of force
