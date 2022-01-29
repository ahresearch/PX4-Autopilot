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
Start VS Code

File/Open Folder

Select the PX-Autopilot folder

The code will be automatically build

Go to Run/Open Configuration
This will open launch.json


Insert "miDebuggerArgs": "~/.gdbinit",
right after "MIMode": "gdb",
Do this for all targets in launch.json

The file ~/.gdbinit should contain the following:
handle SIGCONT nostop noprint nopass 

Go to Run and Debug on the left side bar and select it.
Select the Launch configuration to run or debug

Place any breakpoints

Go to Run/Start Debugging to begin debugging

```


## Setting up development with Eclipse

```
Select the following from the menus:

File/Import/C++/Existing Code as Makefile Project

Point to the top folder of PX4

The project should be able to build and produce the px4 executable and all other executables.

Jumping to defintions should work fine.

Go to Run Configurations for the project.

Set Command Line Parameters Tab:
/home/anton/projects/PX4-Autopilot/build/px4_sitl_default/etc -s etc/init.d-posix/rcS -t /home/anton/projects/PX4-Autopilot/test_data

Add the following environment variable in the Environment Tab:
PX4_SIM_MODEL iris

Select Apply

Run jmavsim in one window:
./Tools/jmavsim_run.sh -l

Run QGroundcontrol in a separate window

Go to Run menu and select:

Run as Local C/C++ Application

or

Debug as Local C/C++ Application

In order to skip the SIGCONT signals add the following to 

~/.gdbinit

handle SIGCONT nostop noprint nopass

Add ~/.gdbinit in the following place:
Run/Debugger Configurations/Debugger Tab/GDB command line

Alternatively if you do not have .gdbinit need to set the parameters every time gdb is run.
Once the debugger starts go to the Debugger Console tab and add the following parameters:

(gdb) handle SIGCONT nostop noprint nopass

Select Resume as many times as necessary if the debugger keeps stopping at exceptions

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

Debug px4 in the IDE.

```