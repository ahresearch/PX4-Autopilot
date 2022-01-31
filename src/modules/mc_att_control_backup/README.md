# Adding a custom module to PX4 

An custom module is located under src/modules folder where a subfolder with the module's name is created.

## Contents of the subfolder

A module contains several files as show here:

```
ls -l src/modules/custommodule/

-rw-rw-r-- 1 anton anton  1802 Jan 27 08:31 CMakeLists.txt
-rw-rw-r-- 1 anton anton 10467 Jan 27 08:48 custommodule.cpp
-rw-rw-r-- 1 anton anton  3180 Jan 27 08:05 custommodule.h
-rw-rw-r-- 1 anton anton   111 Jan 27 08:31 Kconfig
-rw-rw-r-- 1 anton anton  2499 Jan 27 11:48 README.md
```

## Add module to the build configuration

```
Modify the following file:
boards/px4/sitl/default.px4board

Add a line that includes the module. 
Here is an example of the inclusion of a new module withh a name custommodule:
CONFIG_MODULES_CUSTOMMODULE=y
```

## How to run manually

```
To start the sample application:
From px4's command shell type:

pxh> custommodule start

To stop the module type:

pxh> custommodule stop
```

## How to run automatically on PX4 startup

```
Edit the following file:
ROMFS/px4fmu_common/init.d-posix/rcS
Add a line that starts the module, e.g.:
custommodule start
```