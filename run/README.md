# Running and Debugging PX4

## Running PX4 from the command line

### Running with jmavsim

```
make px4_sitl jmavsim
```

### Running with gazebo

```
make px4_sitl gazebo
``` 

### Running without make

```
/home/anton/projects/PX4-Autopilot/Tools/sitl_run.sh /home/anton/projects/PX4-Autopilot/build/px4_sitl_default/bin/px4 none jmavsim none none /home/anton/projects/PX4-Autopilot /home/anton/projects/PX4-Autopilot/build/px4_sitl_default
```

### Running PX4 and simulator separately

```
Run jmavsim in one window:
./Tools/jmavsim_run.sh -l

Run PX4 in another window:
make px4_sitl none

```


### Running PX4 from the command line

```

Run jmavsim in one window:
./Tools/jmavsim_run.sh -l


Run PX4 in another window or in an IDE:
export PX4_SIM_MODEL=iris        # Can be placed in .bashrc
/home/anton/projects/PX4-Autopilot/build/px4_sitl_default/bin/px4 /home/anton/projects/PX4-Autopilot/build/px4_sitl_default/etc -s etc/init.d-posix/rcS -t /home/anton/projects/PX4-Autopilot/test_data

```

## Setting up development with Visual Studio Code

```
Go to the main folder of PX4
There needs to be a .vscode folder with the right .json files for working with C++
Have the C/C++ extensions installed in VS Code
From the that folder type:
```
<em>code  .</em>

```
One should be able to browse through the code and jump to defintions, etc.

```


## Setting up development with Eclipse

```
Select the following from the menus:

File/Import/C++/Existing Code as Makefile Project

Point to the top folder of PX4

The project should be able to build and produce the px4 executable and all other executables.

Jumping to defintions should work fine.

```


## Setting up development with QTCreator

```
Go to menu:

File/Open File or Project

Select the CMakeLists.txt

Press configure project and build the code.

There will be a folder created from the build called build-PX4-Autopilot-Desktop-Debug alongside PX4-Autopilot

Change the build directory:
Go to Projects/Build and select a folder that is under the main folder of PX4:
PX4-Autopilot/build/px4_sitl_default

Go to Projects/Run and select :

Executable:
/home/anton/projects/PX4-Autopilot/build/px4_sitl_default/bin/px4

Command Line Parameters:
/home/anton/projects/PX4-Autopilot/build/px4_sitl_default/etc -s etc/init.d-posix/rcS -t /home/anton/projects/PX4-Autopilot/test_data

Working directory:
PX4-Autopilot

Check the checkbox:
Run in terminal

Go to Run/Run Environment
Add the following environment variable for QTCreator's run environment:
PX4_SIM_MODEL iris

Run jmavsim in one window:
./Tools/jmavsim_run.sh -l

Run QGroundcontrol in a separate window

Run px4 in the IDE. A new terminal window will pop up.

```