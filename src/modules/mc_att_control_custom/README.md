# Adding a custom module to PX4 

An custom module is located under src/modules folder where a subfolder with the module's name is created.

## Contents of the subfolder

A module contains several files as show here:

```
ls -l src/modules/mc_att_control_custom/

-rw-rw-r-- 1 anton anton  2184 Feb 21 08:59 CMakeLists.txt
-rw-rw-r-- 1 anton anton   137 Feb 20 16:58 Kconfig
-rw-rw-r-- 1 anton anton 12094 Feb 21 09:11 mc_att_control_custom.cpp
-rw-rw-r-- 1 anton anton  3421 Feb 21 09:11 mc_att_control_custom.h
-rw-rw-r-- 1 anton anton  8027 Feb 21 08:53 mc_att_state_control.cpp
-rw-rw-r-- 1 anton anton  2656 Feb 21 08:53 mc_att_state_control.hpp
-rw-rw-r-- 1 anton anton  1048 Feb 20 17:02 README.md
```

## Add module to the build configuration

```
Modify the following file:
boards/px4/sitl/default.px4board

Add a line that includes the module. 
Here is an example of the inclusion of a new module with a name mc_att_control_custom:
CONFIG_MODULES_MC_ATT_CONTROL_CUSTOM=y
```

## How to build

make px4_sitl

cp build/px4_sitl_default/src/modules/mc_att_control_custom/modules__mc_att_control_custom.px4mod  build/px4_sitl_default/tmp/rootfs/mc_att_control_custom.px4mod

## How to run manually

```
To start the sample application:
From px4's command shell type:

pxh> dyn ./mc_att_control_custom.px4mod start

To stop the module type:

pxh> dyn ./mc_att_control_custom.px4mod stop
```