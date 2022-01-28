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



## Setting up to develop with Visual Studio Code

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


## Setting up to develop with Eclipse

```
Select the following from the menus:

File/Import/C++/Existing Code as Makefile Project

Point to the top folder of PX4

The project should be able to build and produce the px4 executable and all other executables.

Jumping to defintions should work fine.

```