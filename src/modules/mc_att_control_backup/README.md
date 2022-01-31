# Adding a module that runs in the work queue to PX4 

An custom module is located under src/modules folder where a subfolder with the module's name is created.

## Contents of the subfolder

A module contains several files as show here:

```
ls -l mc_att_control_backup/

-rw-rw-r-- 1 anton anton  1829 Jan 30 22:07 CMakeLists.txt
-rw-rw-r-- 1 anton anton   138 Jan 30 22:06 Kconfig
-rw-rw-r-- 1 anton anton 10794 Jan 30 22:19 mc_att_control_backup.cpp
-rw-rw-r-- 1 anton anton  3291 Jan 30 22:14 mc_att_control_backup.h
-rw-rw-r-- 1 anton anton  1149 Jan 30 22:02 README.md

```

## Add module to the build configuration

```
Modify the following file:
boards/px4/sitl/default.px4board

Add a line that includes the module. 
Here is an example of the inclusion of a new module withh a name mc_att_control_backup:
CONFIG_MODULES_MC_ATT_CONTROL_BACKUP=y

Modify the following file:
Tools/kconfig/cmake_kconfig_lut.txt

Add the following line:
mc_att_control_backup,CONFIG_MODULES_MC_ATT_CONTROL_BACKUP=y
```

## How to run manually

```
To start the sample application:
From px4's command shell type:

pxh> mc_att_control_backup start

To stop the module type:

pxh> mc_att_control_backup stop
```

## How to run automatically on PX4 startup

```
Edit the following file:
ROMFS/px4fmu_common/init.d/rc.mc_apps
Add a line that starts the module, e.g.:
mc_att_control_backup start
```